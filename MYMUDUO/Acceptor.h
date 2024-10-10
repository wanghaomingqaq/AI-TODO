#pragma once
#include "noncopyable.h"
#include "Socket.h"
#include <functional>
#include "Channel.h"
#include "InetAddress.h"

class EventLoop;

class Acceptor : noncopyable
{
public:
    using NewConnectionCallback = std::function<void(int sockfd, const InetAddress&)>;
    Acceptor(EventLoop *loop, const InetAddress& listenAddr, bool reuseport);
    ~Acceptor();
    void setNewConnectionCallback(const NewConnectionCallback& cb)
    { newConnectionCallback_ = cb; }
    bool listenning() const {return listenning_; }
    void listen();
private:
    void handleRead();
    EventLoop *loop_; // Acceptor 用的就是用户定义的那个 baseloop, mainloop
    Socket acceptSocket_;
    Channel acceptChannel_;
    bool listenning_;
    NewConnectionCallback newConnectionCallback_;
};