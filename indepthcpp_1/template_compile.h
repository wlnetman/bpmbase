#ifndef TMP_H
#define TMP_H

#include <memory>
#include <vector>

class Foo
{
public:
    static int get(void)
    {
        return 0;
    }
};

class Bar
{
public:
    static const char* get(void)
    {
        return "0";
    }
};

template <class A>
void func(void)
{
    auto val = A::get();
}

#endif // TMP_H
