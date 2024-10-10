#include "EventLoop.h"
#include <sys/eventfd.h>
#include <unistd.h>
#include "Logger.h"
#include "Poller.h"
#include <errno.h>
#include <fcntl.h>
#include "Channel.h"

/*防止一个线程创建多个eventloop __thread是线程局部变量，每个线程只有一个*/ 
__thread EventLoop *t_loopInisThread = nullptr;

//定义poller IO复用接口的默认超时时间 10s
const int kPollTimeMs = 10000;

/*创建wakeupfd 通知睡觉的eventloop 有新的用户channel */
/*创建wakeupfd，用来notify唤醒subReactor处理新来的channe1*/
int createEventfd()
{   
    /**
     * EFD_CLOEXEC：FD_CLOEXEC，简单说就是fork子进程时不继承，对于多线程的程序设上这个值不会有错的。
     * EFD_NONBLOCK：文件会被设置成O_NONBLOCK，一般要设置。
    */
    int evtfd = ::eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC); //调用系统函数，用于线程间通信，唤醒subReactor处理新来的channel
    if (evtfd < 0)
    {
        LOG_FATAL("eventfd error: %d \n", errno);
    }
    return evtfd;
}

EventLoop::EventLoop()
    :looping_(false)
    ,quit_(false)
    ,callingPendingFunctors_(false)
    ,threadId_(CurrentThread::tid())
    ,poller_(Poller::newDefaultPoller(this))
    ,wakeupFd_(createEventfd())
    ,wakeupChannel_(new Channel(this, wakeupFd_))
    ,currentActiveChannel_(nullptr)
{
    LOG_DEBUG("eventloop created %p in thread %d \n",this, threadId_);
    if (t_loopInisThread)
    {
        LOG_FATAL("Anther eventloop %p exists in this thread %d \n",this, threadId_);
    }
    else
    {
        t_loopInisThread = this;
    }

    //设置waleupfd的事件类型 以及方式事件后的回调操作. 去唤醒subloop
    wakeupChannel_->setReadCallback(std::bind(&EventLoop::handleRead, this)); //相当于 setReadCallback(handleRead) 把当前this的handleRead()事件作为回调函数。

    //每一个eventloop 都将监听wakeupchannel的epollin读事件了
    wakeupChannel_->enableReading();

}
EventLoop::~EventLoop()
{
    wakeupChannel_->disableAll();
    wakeupChannel_->remove();
    ::close(wakeupFd_);
    t_loopInisThread = nullptr;

}


// 开启时间循环
void EventLoop::loop()
{
    looping_ = true;
    quit_ = false;
    LOG_INFO("eventloop %p start looping \n", this);

    while(!quit_)
    {
        activeChannels_.clear();
        //监听两类fd， 一种是wakeupfd 一种是clientfd
        pollReturnTime_ = poller_->poll(kPollTimeMs, &activeChannels_);
        for (Channel *channel : activeChannels_)
        {
            // poller监听哪些channel发生事件了， 上报给eventloop，通知channel自己处理
            channel->handleEvent(pollReturnTime_);
        }
        /**
         * IO线程 mainloop-》accept新用户连接 ，返回fd然后打包成 channel（fd）
         * 已连接的分给subloop
         * mainloop 事先注册一个回调cb （需要subloop处理）
         * wakeup subloop后，执行下面方法， 执行之前mainloop注册的回调操作
         */
        doPendingFunctors(); //执行当前eventloop需要处理的回调操作
    }
    LOG_INFO("eventloop %p stop looping \n", this);
    
}
//退出时间循环
void EventLoop::quit()
{
    quit_ = true;
    // 比如在subloop(worker)中调用main(IO)的quit.不能把别人给干掉
    // 如果是在其他线程，调用wakeuplo唤醒op所在线程
    if (!isInLoopThread())
    {
        wakeup();
    }
}

void EventLoop::runInLoop(Functor cb)
{
    if (isInLoopThread()) //当前loop线程中执行callback
    {
        cb();
    }
    else //在其他线程中执行callback,唤醒loop所在线程执行cb。
    {
        queueInLoop(cb);
    }
}

void EventLoop::queueInLoop(Functor cb)
{
    {
        std::unique_lock<std::mutex> lock(mutex_);
        pendingFunctors_.emplace_back(cb); //push_back是拷贝构造。这个是直接构造
    }
    if (!isInLoopThread() || callingPendingFunctors_) //正在执行回调,没有阻塞到loop上
    {
        wakeup();
    }
}

void EventLoop::handleRead()
{
    uint64_t one = 1;
    int n = read(wakeupFd_, &one, sizeof(one));
    if (n!= sizeof(one))
    {
        LOG_ERROR("eventloop::handleread() read %d bytes instead of 8", n);
    }
}

//用来唤醒loop所在的线程
void EventLoop::wakeup()
{
    uint64_t one = 1;
    ssize_t n = ::write(wakeupFd_, &one, sizeof(one));
    if (n != sizeof(one))
    {
        LOG_ERROR("eventloop::wakeup() writes %ld bytes instead of 8", n);
    }
    LOG_DEBUG("eventloop %p wakeup fd %d", this, wakeupFd_);
}

void EventLoop::updateChannel(Channel *channel)
{
    poller_->updateChannel(channel);
}

void EventLoop::removeChannel(Channel *channel)
{
    poller_->removeChannel(channel);
}
bool EventLoop::hasChannel(Channel *channel)
{
    return poller_->hasChannel(channel);
}
void EventLoop::doPendingFunctors()
{
    std::vector<Functor> functors;
    callingPendingFunctors_ = true;
    {
        std::unique_lock<std::mutex> lock(mutex_);
        functors.swap(pendingFunctors_); // 把pendingfunctors_的内容拷贝到functors中
    }
    for (const Functor &functor : functors)
    {
        functor(); //执行当前loop需要处理的回调操作
    }
}