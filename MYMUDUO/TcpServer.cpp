#include "TcpServer.h"
#include "Logger.h"
#include "TcpConnection.h"
#include <strings.h>
#include <functional>

EventLoop* CheckLoopNotNull(EventLoop *loop)
{
    if (loop == nullptr)
    {
        LOG_FATAL("%s:%s:%d mainLoop is null!\n", __FILE__, __FUNCTION__, __LINE__);
    }
    return loop;
}
TcpServer::TcpServer(EventLoop *loop,
                     const InetAddress &listenAddr,
                     const std::string &nameArg,
                     Option option)
                :loop_(CheckLoopNotNull(loop))
                ,ipPort_(listenAddr.toIpPort())
                ,name_(nameArg)
                ,acceptor_(new Acceptor(loop, listenAddr, option == kReusePort))
                ,threadPool_(new EventLoopThreadPool(loop, name_))
                ,connectionCallback_()
                ,messageCallback_()
                ,nextConnId_(1)
                ,started_(0)
{
    //当有新用户连接时，会执行 newConnection回调函数
    acceptor_->setNewConnectionCallback(std::bind(&TcpServer::newConnection, this, std::placeholders::_1, std::placeholders::_2)); //当前对象的newConnetion方法，两个参数位置

}

//设置subloop的个数
void TcpServer::setThreadNum(int numThreads)
{
    threadPool_->setThreadNum(numThreads);
}

//开始服务器监听。loop.loop(),开始epool——wait了 
void TcpServer::start()
{
    if (started_++ == 0) //防止一个TcpServer对象被start多次，（第一次start 成功后 还是0满足判断，第二次就started_=1）
    {
        threadPool_->start(threadInitCallback_); //启动底层线程池
        loop_->runInLoop(std::bind(&Acceptor::listen, acceptor_.get())); //get获取裸指针，要指定是哪个accpetor_来执行listen
    }
}

// 有一个新的客户端的连接，acceptor会执行这个回调操作
void TcpServer::newConnection(int sockfd, const InetAddress &peerAddr)
{
    // 轮询算法，选择一个subLoop， 来管理channel
    EventLoop *ioLoop = threadPool_->getNextLoop();
    char buf[64] = {0};
    snprintf(buf, sizeof buf, "-%s#%d", ipPort_.c_str(), nextConnId_);
    ++nextConnId_;
    std::string connName = name_ + buf;
    LOG_INFO("TcpServer::newConnection [%s] - new connection [%s] from %s\n", name_.c_str(), connName.c_str(), peerAddr.toIpPort().c_str());

    // 通过socketfd 获取其绑定的本机的IP地址和端口信息
    sockaddr_in local;
    ::bzero(&local, sizeof local); // bzero是memset的别名， 清零
    socklen_t addrlen = sizeof local;
    if (::getsockname(sockfd, (sockaddr *)&local, &addrlen) < 0)
    {
        LOG_ERROR("sockets::getLocalAddr");
    }
    InetAddress localAddr(local);

    // 根据连接成功的sockfd，创建TcpConnection连接对象
    TcpConnectionPtr conn(new TcpConnection(ioLoop, connName, sockfd, localAddr, peerAddr));
    connections_[connName] = conn;
    // 下面的回调是用户设置给TcpServer的， TcpServer设置给Tcpconnection的，再设置给Channel，channel注册给 poller， polller 在通知channel调用回调
    conn->setConnectionCallback(connectionCallback_);
    conn->setMessageCallback(messageCallback_);
    conn->setWriteCompleteCallback(writeCompleteCallback_);
    //设置了如何关闭连接的回调， conn-> shutdowm
    conn->setCloseCallback(
        std::bind(&TcpServer::removeConnection, this, std::placeholders::_1)); 
    // 直接调用 TcpConnection::connectEstablished()，把连接注册到poller上
    ioLoop->runInLoop(std::bind(&TcpConnection::connectionEstablished, conn));

}

void TcpServer::removeConnection(const TcpConnectionPtr &conn)
{
    loop_->runInLoop(std::bind(&TcpServer::removeConnectionInLoop, this, conn));
}
void TcpServer::removeConnectionInLoop(const TcpConnectionPtr &conn)
{
    LOG_INFO("TcpServer::removeConnectionInLoop [%s] - connection %s\n", name_.c_str(), conn->name().c_str());

    size_t n = connections_.erase(conn->name());
    EventLoop *ioLoop = conn->getLoop(); // 拿到连接的loop
    ioLoop->queueInLoop(std::bind(&TcpConnection::connectionDestroyed, conn));
}

TcpServer::~TcpServer()
{
    for (auto &item : connections_)
    {
        TcpConnectionPtr conn(item.second); // 这个局部的sharptr智能指针对象。出右括号，可以自动释放new出来的TcpConnection对象资源了
        item.second.reset();
        conn->getLoop()->runInLoop(std::bind(&TcpConnection::connectionDestroyed, conn));
    }
}