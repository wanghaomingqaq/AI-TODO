#pragma once
#include <vector>
#include <stddef.h>
#include <string>
#include <algorithm>
#include <unistd.h>
/*网络库底层的缓冲区*/
/**
 * 缓冲区
 * +-----------------------+<--------------+-----------------------------+
 * |prependableBytes()     |readableBytes()|     writableBytes()          |
 * |                       |               |                             |
 * |                       |               |                             |
 * +-----------------------+----------------+-----------------------------+
 * |                       |               |                             |
 * kCheapPrepend       readIndex_       writeIndex_                    size                            |
 * +-----------------------+<--------------+-----------------------------+
 */
class Buffer
{
public:
    static const size_t kCheapPrepend = 8;
    static const size_t kInitialSize = 1024;
    explicit Buffer(size_t initialSize = kInitialSize)
    : buffer_(kCheapPrepend + initialSize),
      readIndex_(kCheapPrepend),
      writeIndex_(kCheapPrepend)
    {}

    size_t readableBytes() const {return writeIndex_ - readIndex_;}
    size_t writableBytes() const {return buffer_.size() - writeIndex_;}
    size_t prependableBytes() const {return readIndex_;}

    const char* peek() const //peek：偷窥 看一下
    {
        return begin() + readIndex_; //返回缓冲区的可读数据的起始地址
    }

    // 查找buffer中是否有"\r\n", 解析http请求行用到
    const char* findCRLF() const
    {
        const char* crlf = std::search(peek(), beginWrite(), kCRLF, kCRLF+2);
        return crlf == beginWrite() ? NULL : crlf;
    }
    // 一直取到end位置. 在解析请求行的时候从buffer中读取一行后要移动指针便于读取下一行
    void retrieveUntil(const char* end)
    {
        retrieve(end - peek());
    }
    void retrieve(size_t len)
    {
        if (len < readableBytes())
        {
            readIndex_ += len; //只读取了len个字节，还剩下readIndex_ += len 到 writeIndex_没读。
            return;   
        }
        retrieveAll();
    }
    void retrieveAll()
    {
        readIndex_ = writeIndex_ = kCheapPrepend;
    }

    //onMessage有数据来了，是一个buffer，这时候会调用retrieve，转成string
    //把onMessage上报的buffer数据，转成string数据
    std::string retrieveAllAsString()
    {
        return retrieveAsString(readableBytes()); //应用可读取的长度。
    }
    std::string retrieveAsString(size_t len)
    {
        //result读出了readableBytes的数据， peek开始读了 len
        std::string result(peek(), len); //peek返回的是可读数据的起始地址，声明字符result, result初始化，len是可读的长度
        retrieve(len); // 上面把缓冲区中可读数据，已经读取出来了，这里要对缓冲区做复位操作
        return result;
    }

    //缓冲区可写 buffer.size() - writeIndex_. 不够的话，扩容
    void ensureWritableBytes(size_t len)
    {
        if (writableBytes() < len)
        {
            makeSpace(len); //扩容函数
        }
    }

    //添加数据， 把【data,data+len】添加到缓冲区中
    void append(const char *data, size_t len)
    {
        ensureWritableBytes(len);
        std::copy(data, data + len, beginWrite()); //把data的数据拷贝到buffer_中，从writeIndex_开始，len个字节
        writeIndex_ += len;
    }

    void append(const std::string& str)
    {
        append(str.data(), str.size());
    }
    char* beginWrite(){ return begin() + writeIndex_; }
    const char* beginWrite() const { return begin() + writeIndex_; }

    //从fd上读取数据
    ssize_t readFd(int fd, int *saveErrno);

    ssize_t writeFd(int fd, int *saveErrno);

private:
    char* begin()
    {
        return &*buffer_.begin(); // 调用迭代器的*运算符，返回迭代器所指向的元素，然后取地址，（vector的首地址）
    }
    const char* begin() const { return &*buffer_.begin(); }

    void makeSpace(size_t len)
    {
        if (writableBytes() + prependableBytes() < len + kCheapPrepend)
        {
            buffer_.resize(writeIndex_ + len);
            return;
        }
        //往前挪，把可读的空位往前挪
        size_t readable = readableBytes();
        // 读写指针挪到头部。 把readIndex_和 writeIndex_ 之间的数据，挪到kCheapPrepend开始的位置。
        std::copy(begin() + readIndex_, begin() + writeIndex_, begin() + kCheapPrepend); 
        readIndex_ = kCheapPrepend;
        writeIndex_ = readIndex_ + readable;
    }
    std::vector<char> buffer_;
    size_t readIndex_;
    size_t writeIndex_;
    static const char kCRLF[];  // 存储"\r\n"
};