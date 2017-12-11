#include "hasptr.h"

#include <string>

HasPtr& HasPtr::operator=(const HasPtr &rhs)
{
    // 必须保证右侧失败时，左侧正常
    ++*rhs.use;
    if(--*use == 0 ){
        delete ps;
        delete use;
    }

    ps = rhs.ps;
    i  = rhs.i;
    use = rhs.use;
    return *this;
}

HasPtr& HasPtr::operator=(HasPtr &rhs)
{
    swap(*this, rhs);
    return *this;
}

HasPtr& HasPtr::operator=(HasPtr rhs)
{
    swap(*this, rhs);
    return *this;
}

HasPtr::~HasPtr()

{
    if(--*use == 0 ){
        delete ps;
        delete use;
    }
}
