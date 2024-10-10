#pragma once
/**
 * 用户使用muduo库编写服务器程序。
 * 
 */
#include "EventLoop.h"
#include "Acceptor.h"
#include "InetAddress.h"
#include "EventLoopThreadPool.h"
#include "TcpConnection.h"
#include "Callbacks.h"
#include "noncopyable.h"
#include <memory>
#include <string>
#include <functional>
#include <atomic>
#include <unordered_map>
class TcpServer : noncopyable
{
public:
    using ThreadInitCallback = std::function<void(EventLoop*)>;
    enum Option
    {
        kNoReusePort,
        kReusePort,
    }; //端口是否可重用
    TcpServer(EventLoop *loop, const InetAddress &listenAddr, const std::string &nameArg, Option option = kNoReusePort);
    ~TcpServer();
    void setThreadInitCallback(const ThreadInitCallback &cb){ threadInitCallback_ = cb; }
    void setConnectionCallback(const ConnectionCallback &cb) {connectionCallback_ = cb; }
    void setMessageCallback(const MessageCallback &cb) { messageCallback_ = cb; }
    void setWriteCompleteCallback(const WriteCompleteCallback &cb) { writeCompleteCallback_ = cb; }

    //设置subloop的个数
    void setThreadNum(int numThreads);
    void start(); //开始服务器监听。
    EventLoop* getLoop() const { return loop_; }
    const std::string name() { return name_; }

    const std::string ipPort() { return ipPort_; }

private:
    void newConnection(int sockfd, const InetAddress &peerAddr);
    void removeConnection(const TcpConnectionPtr &conn);
    void removeConnectionInLoop(const TcpConnectionPtr &conn);

    using ConnectionMap = std::unordered_map<std::string, TcpConnectionPtr>;
    EventLoop *loop_;

    const std::string ipPort_;
    const std::string name_;

    std::unique_ptr<Acceptor> acceptor_; // 运行在mainloop，任务是监听新连接事件

    std::shared_ptr<EventLoopThreadPool> threadPool_; // one loop per thread

    ConnectionCallback connectionCallback_; //有新连接时的回调
    MessageCallback messageCallback_; //有读写消息时的回调
    WriteCompleteCallback writeCompleteCallback_; //消息发送完成以后的回调
 
    ThreadInitCallback threadInitCallback_; //loop线程初始化的回调

    std::atomic_int started_;
    int nextConnId_;
    ConnectionMap connections_; // 保存所有的连接
};