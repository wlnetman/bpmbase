#ifndef STRBLOB_H
#define STRBLOB_H

#include <string>
#include <memory>
#include <vector>

class StrBlobPtr;
class StrBlob{
    friend class StrBlobPtr;
    //StrBlobPtr begin() { return StrBlobPtr(*this); }
    //StrBlobPtr end()
    //{ auto ret = StrBlobPtr(*this, data->size());
//        return ret;}

public:
    typedef std::vector<std::string>::size_type size_type;
    StrBlob();
    StrBlob(std::initializer_list<std::string> il);
    size_type size() const { return data->size();}
    bool empty() const { return data->empty();}
    void push_back(const std::string &t) { data->push_back(t);}
    void pop_back();

    std::string& front();
    std::string& back();

private:
    std::shared_ptr<std::vector<std::string>> data;
    bool check(size_type i, const std::string &msg) const;
};


class StrBlobPtr{
    friend class StrBlob;
public:
    StrBlobPtr():curr(0){}
    // 报错提示不能访问私有成员 wptr
    StrBlobPtr(StrBlob &a, std::size_t sz = 0):
        wptr(a.data), curr(sz){}
    std::string& deref() const;
    StrBlobPtr& inc();

private:
    std::shared_ptr<std::vector<std::string>>
        check(std::size_t, const std::string&) const;
    std::weak_ptr<std::vector<std::string>> wptr;
    std::size_t curr;
};

#endif // STRBLOB_H
