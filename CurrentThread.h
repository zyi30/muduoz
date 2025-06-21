#pragma once
#include<sys/syscall.h>
#include<unistd.h>

//用于 高效地获取当前线程 ID（TID）。我们一行一行解释。
/*
这段代码的主要作用是：
获取当前线程的线程 ID（TID）。
为了效率，不每次都系统调用 syscall(__NR_gettid)，而是用一个线程局部变量 t_cachedTid 缓存住。
保证每个线程自己的 t_cachedTid 是独立的。
*/

namespace   CurrentThread
{
    /*
    __thread 是 GCC 提供的 线程局部存储（Thread-Local Storage, TLS） 关键字：
意思是：每个线程都有自己独立的一份变量 t_cachedTid，互不干扰。
所以不同线程调用 tid()，每个线程都会单独缓存自己的 TID。
    */
    extern  __thread  int t_cachedTid;//extern 在 C++ 中的作用是：声明一个变量是在别的源文件里定义的，这里只是“引用”它，不分配内存、不初始化。


    void   cacheTid();//来把当前线程的 TID 存入 t_cachedTid。

    inline  int  tid()
    {
        if(__builtin_expect(t_cachedTid==0,0))//__builtin_expect(条件, 期望值)

        {
            cacheTid();
        }
        return  t_cachedTid;//拿到当前线程的 ID，但只调用一次系统调用，以后就直接返回缓存值，性能更高。
    }
}
