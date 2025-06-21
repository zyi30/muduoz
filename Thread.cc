#include"Thread.h"
#include"CurrentThread.h"
#include<semaphore.h>

 std::atomic_int Thread::numCreated_{0};
 //线程数量

Thread::Thread(ThreadFunc  func,const  std::string &name)
:started_(false)
,joined_(false)
,tid_(0)
,func_(std::move(func))
,name_(name)
    //explicit 关键字用于 构造函数或转换函数前，其作用是：禁止编译器执行隐式类型转换，只能显式调用。
    {
        setDefaultName();
    }




    Thread::~Thread()
    {
        if(started_&&!joined_)
        {
            thread_->detach();//thread类提供的设置分离线程的方法
            //detach() 的作用是：将线程与当前对象分离，让线程在后台自行运行，运行结束后自动释放资源。
            //否则，程序结束时如果有未 join() 的线程，会导致崩溃（std::terminate() 被调用）。
        }
    }
   

    void Thread::start()//一个Thread对象，记录的就是一个新线程的详细信息
    {
        started_=true;
        sem_t sem;
        sem_init(&sem,false,0);//第二个参数为 false（或 0），表示它是线程间共享的信号量（不是多进程）。
        thread_=std::shared_ptr<std::thread>(new std::thread([&](){
/**
 * shared_ptr两种方式
std::shared_ptr<std::thread>()	     创建空智能指针，指向 nullptr
std::shared_ptr<std::thread>(new std::thread(...))	✅	传裸指针，指向一个新线程对象
C++11 起，std::thread 的构造函数接受 任何可调用对象（函数、lambda、函数对象、std::bind、成员函数等）：
为什么new：因为要在堆上分配内存
 */

            tid_= CurrentThread::tid();//获取线程tid值
            sem_post(&sem);//通知主线程，线程 ID 设置完毕，sem_post() 是对信号量加 1
            //主线程在后面 sem_wait() 中等待这个信号。
            //意思是：“我新线程 tid 设置好了，主线程你可以继续执行了”。
            func_();//开启一个新线程，专门执行该线程函数
        }));
        //这里必须等待上面新创建的线程的tid
        sem_wait(&sem);
    }

    void   Thread::join()
    {
        joined_=true;
        thread_->join();
    }

   void   Thread::setDefaultName()
   {
      int num=++numCreated_;
      if(name_.empty())
      {
        char buf[32]={0};
        snprintf(buf,sizeof  buf,"Thread%d",num);
        name_=buf;
      }
   }