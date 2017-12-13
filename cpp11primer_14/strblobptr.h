#ifndef STRBLOBPTR_H
#define STRBLOBPTR_H

class StrBlob;
class StrBlobPtr{
    friend class StrBlob;
public:
    StrBlobPtr():curr(0){}
    // 报错提示不能访问私有成员 wptr
    StrBlobPtr(StrBlob &a, std::size_t sz = 0):
        wptr(a.data), curr(sz){}
    std::string& deref() const;
    StrBlobPtr& inc();

    // 14.6 定义前置递减运算符
    StrBlobPtr& operator++();
    StrBlobPtr& operator--();
    // 后置 (int)
    StrBlobPtr& operator++(int);
    StrBlobPtr& operator--(int);

    std::string& operator*() const
    { auto p = check(curr, "dereference past end");
        return (*p)[curr];
    }
    std::string* operator->() const
    {
        return & this->operator*();
    }
private:
    std::shared_ptr<std::vector<std::string>>
        check(std::size_t, const std::string&) const;
    std::weak_ptr<std::vector<std::string>> wptr;
    std::size_t curr;
};

#endif // STRBLOBPTR_H
