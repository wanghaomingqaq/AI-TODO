#include "Socket.h"
#include <unistd.h>
#include "Logger.h"
#include "InetAddress.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/tcp.h>
#include <string.h> //memset, bzero

Socket::~Socket()
{
    ::close(sockfd_);
}

void Socket::bindAddress(const InetAddress &localaddr)
{
    if (::bind(sockfd_, (sockaddr*)localaddr.getSockAddr(),sizeof(sockaddr_in)) != 0)
    {
        LOG_FATAL("bind sockfd:%d fail", sockfd_);
    }
}
void Socket::listen()
{
    if (::listen(sockfd_, 1024) != 0) //全局作用用，防止和局部冲突
    {
        LOG_FATAL("listen sockfd:%d fail", sockfd_);
    }
}

/**
 * 返回新连接的fd
 * 绑定地址
 */
int Socket::accept(InetAddress *peeraddr)
{
    sockaddr_in addr;
    socklen_t len = sizeof(addr);
    bzero(&addr, sizeof(addr));
    int connfd = ::accept4(sockfd_, (sockaddr*)&addr, &len,SOCK_NONBLOCK | SOCK_CLOEXEC);
    if (connfd >= 0)
    {
        peeraddr->setSockAddr(addr);
    }
    return connfd;
}
void Socket::shutdownWrite()
{
    if(::shutdown(sockfd_, SHUT_WR) < 0)
    {
        LOG_ERROR("shutdownWrite error");
    }
}
/*是否启用了TCP_NODELAY on:禁用Nagle算法（实时性高，立即发送） off:启用Nagle算法*/
void Socket::setTcpNoDelay(bool on)
{
    int optval = on ? 1 : 0;
    ::setsockopt(sockfd_, IPPROTO_TCP, TCP_NODELAY, &optval, sizeof optval);
}
void Socket::setReuseAddr(bool on)
{
    int optval = on ? 1 : 0;
    ::setsockopt(sockfd_, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof optval);
}
void Socket::setReusePort(bool on)
{
    int optval = on ? 1 : 0;
    ::setsockopt(sockfd_, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof optval);
}
void Socket::setKeepAlive(bool on)
{
    int optval = on ? 1 : 0;
    ::setsockopt(sockfd_, SOL_SOCKET, SO_KEEPALIVE, &optval, sizeof optval);
}