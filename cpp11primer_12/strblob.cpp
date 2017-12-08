#include "strblob.h"


StrBlob::StrBlob():
    data(std::make_shared<std::vector<std::string>>())
{
}

StrBlob::StrBlob(std::initializer_list<std::string> il):
    data(std::make_shared<std::vector<std::string>>(il))
{
}

bool StrBlob::check(size_type i, const std::string &msg) const
{
    if(i >= data->size())
        throw std::out_of_range(msg);
}

std::string& StrBlob::front()
{
    check(0, "front on empty StrBolb");
    return data->front();
}

std::string& StrBlob::back()
{
    check(0, "back on empty StrBolb");
    return data->back();
}

void StrBlob::pop_back()
{
    check(0, "pop_back on empty StrBolb");
    return data->pop_back();
}


/// ----------------
///   StrBlobPtr
///
std::shared_ptr<std::vector<std::string>>
StrBlobPtr::check(std::size_t i, const std::string &msg) const
{
    auto ret = wptr.lock();
    if(!ret)
        throw std::runtime_error("unbound StrBlobPtr");
    if( i >= ret->size())
        throw std::out_of_range(msg);
    return ret;
}

std::string& StrBlobPtr::deref() const
{
    auto p = check(curr, "dereference past end");
    return (*p)[curr];
}

StrBlobPtr& StrBlobPtr::inc()
{
    check(curr,"increment past end of strblobptr");
    ++curr;
    return *this;
}

