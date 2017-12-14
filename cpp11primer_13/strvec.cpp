#include "strvec.h"

//StrVec::StrVec(const StrVec &&s)
//{
//    auto newdata = alloc_n_copy(s.begin(), s.end());
//    elements = newdata.first;
//    first_free = cap = newdata.second;
//}

// 必须初始化才行
std::allocator<std::string> StrVec::alloc;

StrVec::StrVec(StrVec &&s) noexcept
    :elements(s.elements), first_free(s.first_free), cap(s.cap)
{
    s.elements = s.first_free = s.cap = nullptr;
}

StrVec::~StrVec()
{
    free();
}

StrVec &StrVec::operator=(const StrVec &rhs)
{
    auto data = alloc_n_copy(rhs.begin(), rhs.end());
    free();
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}

StrVec &StrVec::operator=(StrVec &&rhs) noexcept
{
    if(this != &rhs){
        free();
        elements = rhs.elements;
        first_free = rhs.first_free;
        cap = rhs.cap;
        rhs.elements = rhs.first_free = rhs.cap = nullptr;
    }
    return *this;
}

void StrVec::push_back(const std::string &s)
{
    chk_n_alloc();
    alloc.construct(first_free++, s);
}
void StrVec::push_back(std::string&& rrhs)
{
    chk_n_alloc();
    alloc.construct(first_free++, std::move(rrhs));
}

std::pair<std::string*, std::string*>
StrVec::alloc_n_copy(const std::string *b, const std::string *e)
{
    auto data = alloc.allocate(e - b);
    return {data, std::uninitialized_copy( b, e, data)};
}

void StrVec::free()
{
    if(elements){
        // 逆序
        for(auto p = first_free; p != elements; )
            alloc.destroy(--p);
        alloc.deallocate(elements, cap - elements);
    }
}

StrVec StrVec::getVec(std::istream &is)
{
    // TODO:
    StrVec ret;
    return ret;
}

// 13.6 移动迭代器
void StrVec::reallocate()
{
    auto newcapacity = size() ? 2 * size() : 1;
    auto first = alloc.allocate(newcapacity);
    auto last = std::uninitialized_copy( make_move_iterator(begin()),
                                         make_move_iterator(end()),
                                         first);
    free();
    elements = first;
    first_free = last;
    cap = elements + newcapacity;
}
