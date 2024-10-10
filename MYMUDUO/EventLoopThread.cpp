#include "EventLoopThread.h"
#include "EventLoop.h"
#include <memory>
EventLoopThread::EventLoopThread(const ThreadInitCallback& cb,const std::string& name)
    :loop_(nullptr),
    exiting_(false),
    thread_(std::bind(&EventLoopThread::threadFunc,this),name),
    mutex_(),
    cond_(),
    callback_(cb)
{

}
EventLoopThread::~EventLoopThread()
{
        exiting_ = true;
        if (loop_ != nullptr)
        {
            loop_->quit();
            thread_.join();
        }
}

EventLoop* EventLoopThread::startLoop()
{
    thread_.start(); //启动底层新线程，执行的是threadFunc()函数
    EventLoop* loop = nullptr;
    {
        std::unique_lock<std::mutex> lock(mutex_);
        while (loop_ == nullptr)
        {
            cond_.wait(lock); //收到 notify_one()信号后，继续执行 
        }
        loop = loop_;
   }
   return loop;
}

void EventLoopThread::threadFunc()
{
    EventLoop loop; // 创建一个独立的EventLoop， 和上面的线程是一一对应的， one loop per thread

    if (callback_)
    {
        callback_(&loop);
    }
    {
        std::unique_lock<std::mutex> lock(mutex_);
        loop_ = &loop;
        cond_.notify_one();
    }
    loop.loop(); // =>poller.poll
    std::unique_lock<std::mutex> lock(mutex_);
    loop_ = nullptr ;

}
