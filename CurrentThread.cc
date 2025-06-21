#include"CurrentThread.h"
#include<unistd.h>
#include<sys/syscall.h>

namespace   CurrentThread
{
     __thread  int t_cachedTid=0;

     void   cacheTid()
     {
        if(t_cachedTid==0)
        {
            //通过linux系统调用获取当前线程tid值
            //如果当前线程还没有缓存它的 tid（线程 ID），就调用 syscall 获取。
            t_cachedTid=static_cast<pid_t>(::syscall(SYS_gettid));
        }
     }
}



