#pragma once
#include "noncopyable.h"
#include <functional>
#include <thread>
#include <memory>
#include <string>
#include <atomic>
#include <unistd.h>

class Thread : noncopyable
{
public:
    using ThreadFunc = std::function<void()>;
    
    explicit Thread(ThreadFunc func, const std::string &name = std::string());
    ~Thread();
    void start();
    void join();
    bool started() const { return started_; }
    pid_t tid() const {return tid_; }
    const std::string& name() const { return name_; }

    static int numCreated() { return numCreated_; }
private:
    void setDefaultName();
    bool started_;
    bool joined_;
    std::shared_ptr<std::thread> thread_; //如果裸指针，创建时，就开始线程，析构时，结束线程，这样会造成线程泄漏
    pid_t tid_;
    ThreadFunc func_;
    std::string name_;
    static std::atomic_int numCreated_;
};