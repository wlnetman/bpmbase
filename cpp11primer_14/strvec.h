#ifndef STRVEC_H
#define STRVEC_H

#include <iostream>
#include <string>
#include <memory>
#include <utility>
#include <initializer_list>

class StrVec
{
public:
    StrVec():
        elements(nullptr), first_free(nullptr), cap(nullptr) {}
    StrVec(StrVec&&) noexcept;
    StrVec &operator=(const StrVec&);
    StrVec &operator=(StrVec &&rhs) noexcept;
    StrVec &operator=(std::initializer_list<std::string>);
    ~StrVec();

    void push_back(const std::string&);
    void push_back(std::string&&);

    std::size_t size() const {return first_free - elements; }
    std::size_t capacity() const { return cap - elements; }
    std::string *begin() const {return elements; }
    std::string *end() const { return first_free; }

    StrVec getVec(std::istream &);

    // 14.5 下标运算符
    std::string& operator[](std::size_t n)
        { return elements[n]; }
    const std::string& operator[](std::size_t n) const
        { return elements[n]; }

private:
    static std::allocator<std::string> alloc;
    void chk_n_alloc()
        { if (size() == capacity() ) reallocate(); }
    std::pair<std::string*, std::string*> alloc_n_copy
        (const std::string*, const std::string*);
    void free();
    void reallocate();
    std::string *elements;
    std::string *first_free;
    std::string *cap;
};

#endif // STRVEC_H
