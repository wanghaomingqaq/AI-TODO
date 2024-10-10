#pragma once
#include "noncopyable.h"
#include <functional>
#include "Timestamp.h"
#include <memory>
/* channel理解为通道 封装了sockfd 和其感兴趣的event，如EPOLLIN EPOLLOUT事件
还绑定了poller返回的具体事件
*/
class EventLoop; //只是使用了类型，所以只用了一个前置说明。 源文件在用具体的头文件

class Channel : noncopyable
{
public:
    using EventCallback = std::function<void()>;
    using ReadEventCallback = std::function<void(Timestamp)>;
    Channel(EventLoop *loop, int fd);
    ~Channel();
    //fd得到poller通知后 处理事件的，调用相应的回调方法。
    void handleEvent(Timestamp receiveTime);

    //设置回调函数对象
    void setReadCallback(ReadEventCallback cb) {readCallback_ = std::move(cb); }
    void setWriteCallback(EventCallback cb) {writeCallback_ = std::move(cb); }
    void setCloseCallback(EventCallback cb) {closeCallback_ = std::move(cb); }
    void setErrorCallback(EventCallback cb) {errorCallback_ = std::move(cb); }

    //防止当channel被手动remove掉，channel还在执行回调操作。
    void tie(const std::shared_ptr<void>&);

    int fd() const {return fd_; }
    int events() const {return events_; }
    void set_revents(int revt) { revents_ = revt; }

    //设置fd相应的事件状态 update调用epoll——ctr 注册事件
    // |= 位运算(或运算) 结果赋值给 左边events_ 这个操作实质上是将 kReadEvent 代表的事件标志添加到 events_ 中
    void enableReading() {events_ |= kReadEvent; update(); } 
    // &| 与运算 注销事件
    void disableReading() {events_ &= ~kReadEvent; update(); } 
    void enableWriting() {events_ |= kWriteEvent; update(); } 
    void disableWriting() {events_ &= ~kWriteEvent; update(); }
    void disableAll() {events_ = kNoneEvent; update(); }

    //返回fd当前的事件状态
    bool isNoneEvent() const {return events_ == kNoneEvent;}
    bool isWriting() const {return events_ & kWriteEvent;}
    bool isReading() const {return events_ & kReadEvent; }

    int index() {return index_; }
    void set_index(int idx) {index_ = idx; }

    // one loop for thread
    EventLoop* owerLoop() {return loop_; }
    void remove();
private:
    void update();
    void handleEventWithGuard(Timestamp receiveTime);
    /*对什么事件感兴趣*/
    static const int kNoneEvent;
    static const int kReadEvent;
    static const int kWriteEvent;


    EventLoop *loop_; //事件循环
    const int fd_; //poller监听的对象
    int events_; // 注册fd感兴趣的事件
    int revents_; //poller返回的具体发生的事件
    int index_; 
    //观察者 
    std::weak_ptr<void> tie_;
    bool tied_;

    //因为channel通道里面能够获知fd最终发生的具体事件revents，所以它负责调用具体事件的回调操作
    ReadEventCallback readCallback_;
    EventCallback writeCallback_;
    EventCallback closeCallback_;
    EventCallback errorCallback_;
};