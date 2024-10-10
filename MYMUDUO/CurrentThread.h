#pragma once
#include <unistd.h>
#include <sys/syscall.h>
/**
 * __thread 修饰的变量会在每个线程中拥有独立的副本，
 * 即每个线程都有自己的 t_cachedTid 变量。这里声明
 * 为 extern 是为了在其他文件中（如实现文件）定义该
 * 变量的实际存储
*/
namespace CurrentThread
{
    extern __thread int t_cachedTid;
    void cacheTid();
    inline int tid()
    {
        if (__builtin_expect(t_cachedTid == 0, 0)) //编译器优化 期待==0 
        {
            cacheTid();
        }
        return t_cachedTid;
    }
} // namespace CurrentThread
