#pragma  once
class   noncopyable
{
    public:
    noncopyable(const noncopyable&)=delete;//拷贝构造
    noncopyable& operator=(const  noncopyable&)=delete;//赋值
    protected:
    noncopyable() =default;
    ~noncopyable()=default;
};