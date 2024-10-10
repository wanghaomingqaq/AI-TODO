#include "EPollPoller.h"
#include "Logger.h"
#include "Channel.h"
#include <errno.h>
#include "string.h"
#include "Timestamp.h"
 #include <unistd.h> // close
/*当前epoll 和 channel状态 channel是否添加到epoll*/
const int kNew = -1; //channel的成员index就是-1 kNew表示channel为添加到poller种
const int kAdded = 1;
const int kDeleted = 2;
EPollPoller::EPollPoller(EventLoop *loop)
    :Poller(loop) //通过基类的构造 初始化从基类继承的
    ,epollfd_(::epoll_create1(EPOLL_CLOEXEC)) //设置一个关闭flag，
    ,events_(kInitEventListSize) // vector<epoll_event>
{
    if (epollfd_ < 0)
    {
        LOG_FATAL("epoll create error: %d \n",errno);
    }
}

EPollPoller::~EPollPoller()
{
    ::close(epollfd_);
}

Timestamp EPollPoller::poll(int timeoutMs, ChannelList *activeChannels)
{
    //实际应该用 LOG_DEBUG更合理 %u无符号整数
    LOG_INFO("func=%s => fd total count: %lu \n",__FUNCTION__, channels_.size());
    //&*events_begin()获得 vector的首地址
    int  numEvents = ::epoll_wait(epollfd_, &*events_.begin(),static_cast<int>(events_.size()),timeoutMs);
    int saveErrno = errno;
    Timestamp now(Timestamp::now());
    
    if (numEvents > 0)
    {
        LOG_INFO("%d events happened\n", numEvents);
        fillActiveChannels(numEvents, activeChannels);
        if (numEvents == events_.size())
        {
            events_.resize(events_.size()*2);
        }
    }
    else if (numEvents == 0)
    {
        LOG_DEBUG("func %s timeout!",__FUNCTION__);
    }
    else
    {
        // EINTR外部中断
        if (saveErrno != EINTR)
        {
            errno = saveErrno;
            LOG_ERROR("EpollPoller::poll() error");
        }
    }
    return now;

}

//channel udpate remove ==> eventloop 的 updatechannel ==》 poller 的 updatechannel
/**
 *              EventLoop
 * channelList            poller
 *               channelMap <fd, channel*> (向poller注册过的channel)
*/
void EPollPoller::updateChannel(Channel *channel)
{
    const int index = channel->index();
    LOG_INFO("func=%s => fd=%d events=%d index=%d \n", __FUNCTION__, channel->fd(),channel->events(),index);
    if (index == kNew || index == kDeleted)
    {
        if (index == kNew)
        {
            int fd = channel->fd();
            channels_[fd] = channel;
        }
        
        channel->set_index(kAdded);
        update(EPOLL_CTL_ADD, channel);
    }
    else
    {
        int fd = channel->fd();
        if (channel->isNoneEvent())
        {
            update(EPOLL_CTL_DEL, channel);
            channel->set_index(kDeleted);
        }
        else
        {
            update(EPOLL_CTL_MOD, channel);
        }
    }
}

void EPollPoller::removeChannel(Channel *channel)
{
    LOG_INFO("func=%s => fd=%d \n", __FUNCTION__, channel->fd());
    int fd = channel->fd();
    channels_.erase(fd);

    int index = channel->index();
    if (index == kAdded)
    {
        update(EPOLL_CTL_DEL, channel);
    }
    channel->set_index(kNew);
}

void EPollPoller::fillActiveChannels(int numEvents, ChannelList *activeChannels) const
{
    for(int i=0;i < numEvents; ++i)
    {
        Channel *channel = static_cast<Channel*>(events_[i].data.ptr);
        channel->set_revents(events_[i].events);
        activeChannels->push_back(channel); //Eventloop就拿到了它的poller给他返回的所有发生事件的channel列表了
    }
}

void EPollPoller::update(int operation, Channel *channel)
{
    epoll_event event;
    memset(&event, 0, sizeof(event));

    int fd = channel->fd();

    event.events = channel->events();
    event.data.fd = fd;
    event.data.ptr = channel; //携带fd绑定的参数
    if (::epoll_ctl(epollfd_, operation, fd, &event) < 0)
    {
        if (operation == EPOLL_CTL_DEL)
        {
            LOG_ERROR("epoll ctl del error: %d", errno);
        }
        else
        {
            LOG_FATAL("epoll_ctl add/mod eerror: %d", errno);
        }
    }
}