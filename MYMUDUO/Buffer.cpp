#include "Buffer.h"
#include <errno.h>
#include <sys/uio.h>
/**
*从fd上读取数据 LT模式（没读完，会不断上报）
*Buffer缓冲区是有大小。但是从fd上读数据的时候，不一定能一次读完，不知道tcp最终的数据大小，
*struct iovec {
*    void   *iov_base;  开始地址
*    size_t  iov_len;  区域长度 
* };
*/
const char Buffer::kCRLF[] = "\r\n";
ssize_t Buffer::readFd(int fd, int* saveErrno)
{
    char extraBuf[65536] = {0}; // 64K, 栈上的内存空间
    struct iovec vec[2]; //uio.h 里的结构体，
    const size_t writable = writableBytes(); //buffer的可写空间
    vec[0].iov_base = begin() + writeIndex_;
    vec[0].iov_len = writable;

    vec[1].iov_base = extraBuf;
    vec[1].iov_len = sizeof extraBuf;

    const int iovcnt = (writable < sizeof extraBuf) ? 2 : 1; //缓冲区长度如果小于655536/1204=64K。选择2（第二个空间），否之只需要第一个空间
    const ssize_t n = readv(fd, vec, iovcnt); // 非连续地址块上，写入一个fd读入的数据。
    if (n < 0)
    {
        *saveErrno = errno;
    }
    else if (n <= writable) // buffer的可写空间是足够的
    {
        writeIndex_ += n;
    }
    else // extraBuf也写入了数据
    {
        writeIndex_ = buffer_.size();
        append(extraBuf, n - writable);
    }
    return n;
}

ssize_t Buffer::writeFd(int fd, int *saveErrno)
{
    ssize_t n = ::write(fd, peek(), readableBytes());
    if (n < 0)
    {
        *saveErrno = errno;
    }
    return n;
}