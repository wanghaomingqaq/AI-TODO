#pragma once
#include "noncopyable.h"
#include <functional>
#include <string>
#include <memory>
#include <vector>
class EventLoop;
class EventLoopThread;

class EventLoopThreadPool : noncopyable {
public:
    using ThreadInitCallback = std::function<void(EventLoop*)>;

    EventLoopThreadPool(EventLoop *baseLoop, const std::string &nameArg);
    ~EventLoopThreadPool();

    void setThreadNum(int numThreads) { numThreads_ = numThreads; }

    void start(const ThreadInitCallback &cb = ThreadInitCallback());

    //如果工作在多线程，baseloop会轮询分配channel给subloop。
    EventLoop *getNextLoop();
    std::vector<EventLoop*> getAllLoops();

    bool started() const { return started_; }

    const std::string name() { return name_; }
private:
    EventLoop *baseLoop_; //用户创建的初始loop
    std::string name_;
    bool started_;
    int numThreads_;
    int next_;
    std::vector<std::unique_ptr<EventLoopThread>> threads_; //保存创建的线程
    std::vector<EventLoop*> loops_; //保存创建的loop指针

};