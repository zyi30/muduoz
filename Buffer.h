#pragma  once
//网络库底层的缓冲器类型定义
#include<vector>
#include <cstddef>  // 推荐，C++ 风格(size_t)
#include<string>
#include<algorithm>
class   Buffer
{
public:
        static   const  size_t   KCheapPrepend=8;
        static   const    size_t   KInitialSize=1024;

        explicit  Buffer(size_t  initialSize=KInitialSize):
        buffer_(KCheapPrepend+initialSize),
        readerIndex_(KCheapPrepend),
        writeIndex_(KCheapPrepend)
        {

        }

        size_t   readableBytes()const//可读的数据
        {
            return   writeIndex_-readerIndex_;
        }
        size_t   writeableBytes()const
        {
            return   buffer_.size()-writeIndex_;
        }
        size_t    prependableBytes()const{
            return  readerIndex_;
        }//0 ~ readerIndex_ 之间的区域，就是已经读过的数据，但我们没有释放掉；
        //这个区域可以被拿来做 prepend 用，因此被称为“prependable” 区。

        //返回缓冲区中可读数据的起始地址
        const  char*peek()const{
            return  begin()+readerIndex_;
        }

        void  retrieve(size_t    len)
        {
                if(len<readableBytes())//	把 readerIndex_ 移 len 字节，表示消费(发送）了这部分数据
                {
                        readerIndex_+=len;//应用只读取了可读缓冲区数据的一部分len,还剩下   readerIndex_+=len         -》    writeindex_
                }
                else//len>=readableBytes
                {
                    retrieveAll();//	表示读完（发送完）所有数据，直接调用 retrieveAll() 来重置索引
                }
        }

        void  retrieveAll()//	表示读完所有数据，直接调用 retrieveAll() 来重置索引
        {
                readerIndex_=writeIndex_=KCheapPrepend;
        }

        //onMessage函数上报的Buffer数据，转成string类型的数据返回
        std::string    retrieveAllAsString()
        {
                return   retrieveAsString(readableBytes());//应用可读取数据的长度
        }

        std::string   retrieveAsString(size_t  len)
        {
                std::string  result(peek(),len);
                retrieve(len);//上面一句把缓冲区所有可读数据，已经读取出来，现在这一句要对缓冲区进行复位操作（表示读完所有数据，直接调用 retrieveAll() 来重置索引）
                return   result;
        }


        
        void  ensureWriteableBytes(size_t  len)
        {
                if(writeableBytes()<len)
                {
                    //扩容
                    makeSpace(len);
                }
             
        }

          void   append(const char*data,size_t len)//将一段长度为 len 的内存数据（由 data 指向）追加写入到当前 buffer 的可写区域末尾。
        {
            ensureWriteableBytes(len);
            std::copy(data,data+len,beginwrite());//使用 std::copy() 将传入的 data 数据拷贝 len 字节到 buffer 的写指针位置。
            //把 [first, last) 范围内的元素 复制到从 result 开始的目标区域中。
            writeIndex_+=len;
        }

        ssize_t   readFD(int fd,int*saveErrno);//从fd上读取数据
        ssize_t   writeFD(int fd,int*saveErrno);//通过fd发送数据
private:
        /**
         * &*buffer_.begin()：先解引用得到 char&，再取地址，结果是 char*，即指向第一个元素的裸指针。
它本质上就是获取 buffer_ 内部底层数组的起始地址（即 char* 指针），和 &buffer_[0] 是等价的（假设 buffer_ 非空）。
         */
        char   *begin()
        {
            return &*buffer_.begin();
        }
        const char*  begin()const
        {
          return &*buffer_.begin();
        }

        void   makeSpace(size_t  len)//确保 有足够空间写入 len 字节的数据
        {
            if(writeableBytes()+prependableBytes()<len+KCheapPrepend)//当前 buffer 空闲空间（可写空间 + 可移动头部空间）是否足以容纳 len 字节的数据 + 预留头部空间（KCheapPrepend）？
            {
                buffer_.resize(writeIndex_+len);//resize() 会让 buffer 的容量扩展到：当前写入位置 + 要写入的字节数
            }
            else
            {
                 size_t readable=readableBytes();
                    std::copy(begin()+readerIndex_,begin()+writeIndex_,begin()+KCheapPrepend);
                    readerIndex_=KCheapPrepend;
                    writeIndex_=readerIndex_+readable;//复用前部已读空间
            }
        }
      

        char*beginwrite()
        {
            return  begin()+writeIndex_;
        }

         const   char*beginwrite()const
        {
            return  begin()+writeIndex_;
        }// 第一个 const：修饰返回值
        //第二个 const：修饰成员函数,承诺不会修改当前对象的任何成员变量


        std::vector<char>buffer_;
        size_t   readerIndex_;
        size_t   writeIndex_;
};