#include "Thread.h" 
#include "CurrentThread.h"
#include <semaphore.h> //信号量 线程间通信

std::atomic_int Thread::numCreated_(0);
Thread::Thread(ThreadFunc func, const std::string &name)
    :started_(false),
    joined_(false),
    tid_(0),
    func_(std::move(func)),
    name_(name)
{
    setDefaultName();
}
Thread::~Thread()
{
    if (started_ && !joined_) //join是工作线程 与detach是互斥的。
    {
        thread_->detach(); //不是join就设置分离线程。
    }
}
void Thread::start()
{
    started_ = true;
    sem_t sem;
    sem_init(&sem,false, 0); //信号量
    thread_ = std::shared_ptr<std::thread>(new std::thread([&](){
        //获取tid值
        tid_ = CurrentThread::tid();
        sem_post(&sem); //信号量资源+1
        func_(); //开启一个新线程，专门执行f该线程函数。
    }));
    //这里必须等待获取tid值。
    sem_wait(&sem); //（减一操作，减1后<0，说明被占用，阻塞，>=0继续执行）直到sem_post(&sem)资源+1，sem_wait(&sem)采用立即返回，主线程继续执行。

}
void Thread::join()
{
    joined_ = true;
    thread_->join();
}

void Thread::setDefaultName()
{
    int num = ++numCreated_;
    if(name_.empty())
    {
        char buf[32];
        snprintf(buf, sizeof buf, "Thread%d", num);
        name_ = buf;
        // name_ = "Thread" + std::to_string(num); 不行嘛？
   }
}