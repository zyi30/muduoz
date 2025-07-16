#include"EventLoopThreadPool.h"
#include"EventLoopThread.h"
#include<memory>

    EventLoopThreadPool::EventLoopThreadPool(EventLoop *baseLoop,const std::string &nameArg)
    :baseLoop_(baseLoop),
    name_(nameArg),
    started_(false),
    numThreads_(0),
    next_(0)
    {
    }

    EventLoopThreadPool::~EventLoopThreadPool()
    {
       //不需要关注 loop_是栈上
    }

     
     void  EventLoopThreadPool::start(const  ThreadInitCallback&cb)
     {
        started_=true;
        for(int i=0;i<numThreads_;++i)
        {
             char buf[name_.size()+32];
        snprintf(buf,sizeof buf,"%s%d",name_.c_str(),i);
        EventLoopThread *t=new EventLoopThread(cb,buf);
        //将原始指针 t（EventLoopThread*）封装为 unique_ptr，表示这个线程对象由智能指针接管，不再需要手动 delete。
        //所有权被转移进 vector，生命周期随 threads_ 控制。
        threads_.push_back(std::unique_ptr<EventLoopThread>(t));
        loops_.push_back(t->startLoop());
        }
        //整个服务端只有一个线程，运行着baseLoop 
        if(numThreads_==0&&cb)
        {
            cb(baseLoop_);
        }
     }

     //如果工作在多线程中，baseLoop_默认以轮询方式将channel分配给subloop;
     EventLoop*EventLoopThreadPool::getNextLoop()//这个函数用于在线程池中按顺序选择下一个 EventLoop 来处理新的任务或连接（典型用法：多线程服务器中新连接分发到不同线程）。
     {
        EventLoop*loop=baseLoop_;

        if(!loops_.empty())//通过轮询获取下一个处理事件的loop
        {
            loop =loops_[next_];
            ++next_;
            if(next_>=loops_.size())
            {
                next_=0;
            }
        }
        return  loop;
     }

     std::vector<EventLoop*>EventLoopThreadPool::getAllLoops()
     {
        if(loops_.empty())
        {
            return std::vector<EventLoop*>(1,baseLoop_);      
        }
        else
        {
            return  loops_;
        }
     }

     
