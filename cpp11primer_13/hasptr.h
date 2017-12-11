#ifndef HASPTR_H
#define HASPTR_H

#include <string>

class HasPtr
{
    friend void swap(HasPtr &lhs, HasPtr &rhs);
public:
    //HasPtr() = default;
    HasPtr(const std::string &s = std::string()):
        ps(new std::string(s)), i(0), use(new std::size_t(1)) { }
    ///~HasPtr(){delete ps;};
    HasPtr(const HasPtr &p):
        ps(new std::string(*p.ps)), i(p.i), use(p.use) { ++*use;}

    HasPtr& operator=(HasPtr hp);
    HasPtr& operator=(HasPtr &);
    HasPtr& operator=(const HasPtr&);
    ~HasPtr();

    // 13.6, 拷贝并交换复制
    // 增加移动构造函数
    HasPtr(HasPtr &&p) noexcept : ps(p.ps), i(p.i) { p.ps = 0;}

private:
    std::string *ps;
    int i;
    std::size_t *use;
};

inline
void swap(HasPtr &lhs, HasPtr &rhs)
{
    using std::swap;
    swap(lhs.ps, rhs.ps);
    swap(lhs.i, rhs.i);
}

#endif // HASPTR_H
