#pragma once

#include "noncopyable.h"

#include "InetAddress.h"
#include "Callbacks.h"
#include "Buffer.h"
#include "Timestamp.h"

#include <memory>
#include <string>
#include <atomic>

class Channel;
class EventLoop;
class Socket;

/**
 * Tcpserver ==> Acceptor ==> 有一个新用户连接通过accpet函数拿到 connfd
 * ==》 TcpConnection 设置回调==> Channel ==> Poller ==> 通知TcpConnection处理事件
 */

// 继承两个基类，可以在类的成员函数中安全的返回指向当前对象的智能指针
class TcpConnection : noncopyable, public std::enable_shared_from_this<TcpConnection>
{
public:
    TcpConnection(EventLoop* loop,
                  const std::string& nameArg,
                  int sockfd,
                  const InetAddress& localAddr,
                  const InetAddress& peerAddr);

    void handleRead(Timestamp receiveTime);
    void handleWrite();
    void handleClose();
    void handleError();
    void shutdown();

    
    void shutdownInLoop();
    void sendInLoop(const void* message, size_t len);
    void sendInLoop(const std::string& message);
    void send(const std::string& buf);
    void send(Buffer *buf);
    ~TcpConnection();

    EventLoop* getLoop() const { return loop_; }
    const std::string& name() const { return name_; }
    const InetAddress& localAddress() {return localAddr_;}
    const InetAddress& peerAddress() {return peerAddr_;}

    bool connected() const { return state_ == kConnected; }


    void setConnectionCallback(ConnectionCallback cb) { connectionCallback_ = cb; }

    void setMessageCallback(MessageCallback cb) { messageCallback_ = cb; }

    void setWriteCompleteCallback(WriteCompleteCallback cb) { writeCompleteCallback_ = cb; }

    void setCloseCallback(CloseCallback cb) { closeCallback_ = cb; }

    void setHighWaterMarkCallback(HighWaterMarkCallback cb, size_t highWaterMark)
    {
        highWaterMarkCallback_ = cb;
        highWaterMark_ = highWaterMark;
    }
    //连接建立 和销毁
    void connectionEstablished();
    void connectionDestroyed();
private:
    enum StateE { kDisconnected, kConnecting, kConnected, kDisconnecting };
    void setState(StateE state) { state_ = state; }
    EventLoop* loop_; //这里绝对不是baseloop（mainloop） 因为 TcpConnection都是在subloop里面管理的
    const std::string name_;
    std::atomic_int state_;
    bool reading_;
    std::unique_ptr<Socket> socket_;
    std::unique_ptr<Channel> channel_;
    const InetAddress localAddr_; //本地地址
    const InetAddress peerAddr_; // 对端地址

    
    ConnectionCallback connectionCallback_; // 有新连接时的回调
    MessageCallback messageCallback_;
    WriteCompleteCallback writeCompleteCallback_;
    HighWaterMarkCallback highWaterMarkCallback_;
    CloseCallback closeCallback_;
    size_t highWaterMark_;


    Buffer inputBuffer_; //接受数据的缓冲区
    Buffer outputBuffer_; //发送数据的缓冲区
};
