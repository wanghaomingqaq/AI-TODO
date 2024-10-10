#pragma once
#include "noncopyable.h"
#include <vector>
#include <unordered_map>
#include "Timestamp.h"
class Channel;
class EventLoop;
//muoduo种多路事件分发器的核心 IO复用木块

class Poller : noncopyable
{
public:
    using ChannelList = std::vector<Channel*>;

    Poller(EventLoop *loop);
    virtual ~Poller() = default; // 虚析构， 
    //保留统一的接口 给所有IO复用。
    virtual Timestamp poll(int timeoutMs, ChannelList *activeChannels) = 0; //epoll_ctl
    virtual void updateChannel(Channel *channel) = 0; // epoll_wait
    virtual void removeChannel(Channel *channel) = 0; // epoll_del
    //判断channel是否在当前poller种
    bool hasChannel(Channel* channel) const;
    //eventloop可以通过该接口获取默认的 io复用具体实现
    static Poller* newDefaultPoller(EventLoop *loop);
protected:
    //map的key: sockfd value: sockfd所属的channel通道类型
    using ChannelMap = std::unordered_map<int,Channel*>;
    ChannelMap channels_;
private:
    EventLoop *ownerLoop_; //定义Poller所属的事件循环 EventLoop
};