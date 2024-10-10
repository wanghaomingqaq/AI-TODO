#pragma once
#include "noncopyable.h"
#include <functional>
#include <vector>
#include <atomic>
#include "Timestamp.h"
#include <memory>
#include <mutex>
#include "CurrentThread.h"

class Channel;
class Poller;
/*时间循环类 主要包括 Channel 和 Poller （epoll的抽象）*/
/**
 * 是一个worker线程，每一组channel都在自己的eventloop线程中执行。
 */
class EventLoop : noncopyable
{
public:
    using Functor = std::function<void()>; //定义回调类型

    EventLoop();
    ~EventLoop();
    // 开启时间循环
    void loop();
    //退出时间循环
    void quit();

    Timestamp poolReturnTime() const { return pollReturnTime_; }
    // 在当前loop中执行cb 
    void runInLoop(Functor cb);
    // 把事件放入队列中， 唤醒loop所在的线程，执行cb
    void queueInLoop(Functor cb);

    void wakeup(); //mainreactor唤醒subreactor
    void updateChannel(Channel *channel);
    void removeChannel(Channel *channel);
    bool hasChannel(Channel *channel);
    // 判断EventLoop对象是否在自己的线程里面
    bool isInLoopThread() const { return threadId_ == CurrentThread::tid(); }
private:
    void handleRead();
    void doPendingFunctors();

    using ChannelList = std::vector<Channel*>; //首先包括所有的channel
    std::atomic_bool looping_; //是否处于loop_
    std::atomic_bool quit_; //标志退出loop循环
    const pid_t threadId_; //记录当前loop所在线程的id，判断是否在当前线程里。
    Timestamp pollReturnTime_; //poller返回发生事件的channels的时间点
    std::unique_ptr<Poller> poller_;
    /**
     * 重点！ mainloop通过轮询算法选择一个subloop，通过该成员（wakeupFd_）唤醒subloop处理channel。
     * 调用底层 eventfd() 可以使用线程间通信。wakeupFd_ 是一个fd，通过eventfd()创建的，可以作为事件发生器。
     */
    int wakeupFd_; //当mainloop获取一个新用户 的channel 通过轮询算法选择一个subloop，通过该成员唤醒subloop处理channel。
    std::unique_ptr<Channel> wakeupChannel_; // 包含wakeupFd_的channel

    ChannelList activeChannels_;
    Channel *currentActiveChannel_; //可以不用

    std::atomic_bool callingPendingFunctors_; //标识当前loop是否有需要执行的回调操作
    std::vector<Functor> pendingFunctors_; //存储loop需要执行的所有的回调操作
    std::mutex mutex_; //保护上面vector的线程安全
};