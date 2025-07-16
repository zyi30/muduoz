#include"Buffer.h"
#include<errno.h>
#include <sys/uio.h>
#include<unistd.h>

    //从fd上读取数据,从文件描述符（fd）中读取数据到 Buffer 中，并返回读取的字节数     poller工作在LT模式（不断上报，数据不会丢失）
    //buffer缓冲区有大小，但是从fd上读取数据时，不知道tcp数据最终的大小

    /**
     * readv 写入多个 buffer，是顺序填满，不会并发；
writev 会顺序发送每个 buffer
     */

     /**
      * 从文件描述符 fd 中读取尽可能多的数据，存储到 Buffer 内部的缓冲区里；
使用了 readv，一次读取到两个缓冲区（主 buffer + 额外栈缓冲区），避免频繁扩容和内存复制；
处理读到数据后调整 Buffer 内部状态，保证数据连续。
      */
   ssize_t   Buffer::readFD(int fd,int*saveErrno)//saveErrno 是用来 保存系统调用 readv() 失败时 errno 的值 的一个输出参数指针（int* 类型）。这是一种常见的错误信息传递方式，避免在函数内部直接处理错误，而是把错误代码返回给调用者去处理
   {
        char  extrabuf[65536]={0};//栈上的内存空间,为防止主缓冲区空间不够，额外准备一个大块栈空间暂存多余数据，避免动态扩容开销。

        struct  iovec  vec[2];
        const  size_t  writeable=writeableBytes();//buffer底层缓冲区剩余的可写空间大小
        vec[0].iov_base=begin()+writeIndex_;   //char* + size_t 结果是：指向 buffer 中 可写位置的 char* 指针。
        /**
         * struct iovec {
    void*  iov_base; // 可以接受任何类型的指针
    size_t iov_len;
};
         */
        vec[0].iov_len=writeable;
        vec[1].iov_base=extrabuf;
        vec[1].iov_len=sizeof  extrabuf;

        const  int iovcnt=(writeable<sizeof  extrabuf)?2:1;//如果主缓冲区空间小于64KB，则两个缓冲区都用，否则只用主缓冲区。

        const  ssize_t   n=::readv(fd,vec,iovcnt);//通过 readv 调用，尝试一次读取数据到两个缓冲区；
        if(n<0)
        {
            *saveErrno=errno;
        }
        else  if(n<=writeable)//如果数据完全写入了主缓冲区，则更新写入索引。
        {
            writeIndex_+=n;
        }

        /**
         * 如果有多余数据写入了备用缓冲区，则先将主缓冲区视为满；
再将备用缓冲区的数据追加进主缓冲区，保持数据连续。
         */
        else   //extrabuf里面也写入了数据
        {
            writeIndex_=buffer_.size();
            append(extrabuf,n-writeable);//writeIndex_开始写n-writeable大小的数据
        }
        return  n;
   }

   /**
    * fd：目标 socket，表示将数据写到对端。
peek()：返回当前缓冲区中可读数据的起始地址，通常是 begin() + readIndex_。
readableBytes()：返回当前 Buffer 中可读数据的长度，等于 writeIndex_ - readIndex_。
💡 这表示：从 Buffer 的读指针处开始，尽量把所有待发送数据写到 fd（socket）中。
    */
    ssize_t     Buffer::writeFD(int fd,int*saveErrno)//将 Buffer 中已有的数据写入某个 socket 文件描述符（fd）中
    {
        ssize_t  n=::write(fd,peek(),readableBytes());
        if(n<0)
        {
            *saveErrno=errno;
        }
        return n;
    }