#include "Poller.h"
#include "Channel.h"
Poller::Poller(EventLoop *loop)
    :ownerLoop_(loop)
    {}

bool Poller::hasChannel(Channel* channel) const
{
    auto it = channels_.find(channel->fd());
    return it != channels_.end() && it->second == channel;
}

/*为什么不把 static Poller* newDefaultPoller(EventLoop *loop)的实现写在这 ？
这个里面要实现具体的io多路对象，返回具体的poller对象，需要包含epoller 基类不能引用派生类。（不好）
所以新建了一个 defaultpoller.cpp 专门写
*/