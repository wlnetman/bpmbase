#ifndef HASPTR_H
#define HASPTR_H

#include <string>

class HasPtr
{
    friend void swap(HasPtr &lhs, HasPtr &rhs);
public:
    HasPtr() = default;
    HasPtr(const std::string &s = std::string()):
        ps(new std::string(s)), i(0), use(new std::size_t(1)) { }
    ///~HasPtr(){delete ps;};
    HasPtr(const HasPtr &p):
        ps(new std::string(*p.ps)), i(p.i), use(p.use) { ++*use;}
    HasPtr& operator=(const HasPtr &);
    ~HasPtr();
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
