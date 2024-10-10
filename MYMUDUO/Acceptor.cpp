#include "Acceptor.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>
#include "Logger.h"
static int createNonblocking()
{
    int sockfd = ::socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, 0);
    if (sockfd < 0)
    {
        LOG_FATAL("%s:%s:%d listen socket create err:%d \n",__FILE__, __FUNCTION__, __LINE__, errno);
    }
    return sockfd;
}
Acceptor::Acceptor(EventLoop *loop, const InetAddress &listenAddr, bool reuseport)
    : loop_(loop)
    , acceptSocket_(createNonblocking()) //1. 创建socket
    , acceptChannel_(loop_, acceptSocket_.fd()) //channel需要请求loop和 poller通信
    , listenning_(false)
{
    acceptSocket_.setReuseAddr(true);
    acceptSocket_.setReusePort(true);
    acceptSocket_.bindAddress(listenAddr); //2. 绑定套接字。
    // 有新用户连接，要执行一个回调： confd打包成channel 唤醒 subloop， channel给到subloop后续给他监听，对应一个客户端读写事件。
    // channel监听到事件后，执行回调。
    acceptChannel_.setReadCallback(std::bind(&Acceptor::handleRead, this));
}
Acceptor::~Acceptor()
{
    acceptChannel_.disableAll();
    acceptChannel_.remove();
}

void Acceptor::listen()
{
    listenning_ = true;
    acceptSocket_.listen();
    acceptChannel_.enableReading(); // acceptChannel_=> POller 监听 listenfd_ 有读事件发生了
    
}



//listenfd 有事件发生了，就是有新用户连接了
void Acceptor::handleRead()
{
    InetAddress peerAddr;
    int connfd = acceptSocket_.accept(&peerAddr);
    if (connfd >= 0)
    {
        if (newConnectionCallback_)
        {
            newConnectionCallback_(connfd, peerAddr); //轮询找到subloop，唤醒当前新客户端channel
        }
        else
        { 
            ::close(connfd);
        }
    }
    else
    {
        LOG_ERROR("Acceptor::handleRead");
        if (errno == EMFILE)
        {
            LOG_ERROR("too many open files");
        }
    }
}