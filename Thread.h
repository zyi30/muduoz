#pragma once
#include"noncopyable.h"
#include<functional>
#include<thread>
#include<memory>
#include<string>
#include<atomic>
class  Thread:noncopyable
{
 public:
    using  ThreadFunc=std::function<void()>;
    /**
     * using ThreadFunc = std::function<void()>; 是为了让线程或回调相关的接口 
     * 统一使用灵活的函数包装器，便于传入 lambda、普通函数、bind 对象等。简洁、清晰、现代。
     */
    explicit  Thread(ThreadFunc  func,const  std::string &name=std::string());
    //explicit 关键字用于 构造函数或转换函数前，其作用是：禁止编译器执行隐式类型转换，只能显式调用。




    ~Thread();

    void start();

    void   join();

    bool   started()const{return   started_;}

    pid_t   tid()const{return  tid_;}

    const std::string&name(){return  name_;}

    static   int  numCreated(){return  numCreated_.load();}
    //静态函数，返回当前创建的线程数量
 private:

   void  setDefaultName();
    bool  started_;
    bool  joined_;
    std::shared_ptr<std::thread>thread_;
    pid_t  tid_;
    ThreadFunc  func_;
    std::string  name_;
    static   std::atomic_int numCreated_;//线程数量

};