#include "Channel.h"
#include<sys/epoll.h>
#include "EventLoop.h"
#include "Logger.h"
/*
### `kNoneEvent`
这个常量的值被设置为`0`，表示没有任何事件被监控。这用于清除或初始化文件描述符的事件状态，
意味着`epoll`不会对该文件描述符进行任何类型的监视。

### `kReadEvent`
这个常量是通过组合`EPOLLIN`和`EPOLLPRI`标志设置的。这两个标志是`epoll`系统调用中使用的位掩码，
用于指定不同类型的读取事件：
- `EPOLLIN`：表示对应的文件描述符可读（不会阻塞）。通常，这意味着数据可以从文件描述符中读取。
- `EPOLLPRI`：表示对应的文件描述符有紧急的数据可读（如TCP socket上的带外数据）。
将这两个标志组合在一起，`kReadEvent`可以用来监控标准数据和紧急数据的读取。

### `kWriteEvent`
这个常量设置为`EPOLLOUT`，表示文件描述符可写。当使用`epoll`监控时，
如果设置了这个事件，当文件描述符变为非阻塞状态，即可以进行写操作时，`epoll`会通知应用程序。

*/
const int Channel::kNoneEvent = 0;
const int Channel::kReadEvent = EPOLLIN | EPOLLPRI;
const int Channel::kWriteEvent = EPOLLOUT;

Channel::Channel(EventLoop *loop, int fd)
    : loop_(loop)
    , fd_(fd)
    , events_(0)
    , revents_(0)
    , index_(-1)
    , tied_(false)
    {}

Channel::~Channel(){};

// 什么时候调用过？ 一个TcpConnetion新连接创建的时候 
void Channel::tie(const std::shared_ptr<void>& obj)
{
    tie_ = obj;
    tied_ = true;
}

/* 
当改变channel所表示fd的event事件后，
需要uodate负责在poller里面更改fd相应的事件 epoll_ctl
EventLoop ==> ChannelList Poller

*/
void Channel::update()
{
    //通过channel所属的eventloop调用poller的相应方法，注册fd的events事件
    // add code...
    loop_-> updateChannel(this);
}

void Channel::remove()
{
    //add code...
    loop_-> removeChannel(this);
}

void Channel::handleEvent(Timestamp receiveTime)
{
    if (tied_)
    {
        std::shared_ptr<void> guard = tie_.lock(); //弱指针提升为强指针
        if (guard)
        {
            handleEventWithGuard(receiveTime);
        }
    }
    else
    {
        handleEventWithGuard(receiveTime);
    }
}

/*监听channel发生的具体事件 由channel负责调用具体的回调操作 */
void Channel::handleEventWithGuard(Timestamp receiveTime)
{
    /*
    revents_ & EPOLLHUP：这个条件检查revents_变量（代表了文件描述符的实际事件状态）是否包含EPOLLHUP标志。
        EPOLLHUP通常表示挂断，如对方关闭了socket连接，或者是某种异常终止。这是一个指示连接已经不可用的重要信号。
        !(revents_ & EPOLLIN)：这个条件检查revents_是否不包含EPOLLIN标志。EPOLLIN表示有数据可读。
        EPOLLPRT: 紧急数据
    */
   LOG_INFO("channel handleEvent revnets:%d", revents_);
    if((revents_ & EPOLLHUP) && !(revents_ & EPOLLIN)) // 发生异常
    {
        if (closeCallback_)
        {
            closeCallback_();
        }
    }

    if(revents_ & EPOLLERR)
    {
        if (errorCallback_)
        {
            errorCallback_();
        }
    }

    if (revents_ & (EPOLLIN | EPOLLPRI))
    {
        if(readCallback_)
        {
            readCallback_(receiveTime);
        }
    }
    
    if (revents_ & EPOLLOUT)
    {
        if (writeCallback_)
        {
            writeCallback_();
        }
    }
}