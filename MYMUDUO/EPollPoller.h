#pragma once
#include "Poller.h"
#include <vector>
#include <sys/epoll.h>
#include "Timestamp.h"

/*
1 epoll_create ==》构造函数
2 epoll_ctl add/mod/del
3 epoll_wait ==> 在poll里面
*/
class Channel; //只用了指针声明
class EPollPoller : public Poller
{
public:
    EPollPoller(EventLoop *loop);
    ~EPollPoller() override;

    //重写抽象基类
    Timestamp poll(int timeoutMs, ChannelList *activeChannels) override;
    void updateChannel(Channel *channel) override;
    void removeChannel(Channel *channel) override;
    
private:
    static const int kInitEventListSize = 16;
    //填写活跃连接
    void fillActiveChannels(int numEvents, ChannelList *activeChannels) const;
    //更新channel通道
    void update(int operation, Channel *channel); //epoll——ctl

    using EventList = std::vector<epoll_event>;

    int epollfd_;
    EventList events_;
};