#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include "template_compile.h"

//--------------------------------
// in-depth-cpp11
//     chapter 1  c++11更简 6洁更现代
//
//
//
//      2017-12-20 wlnetman@gmail.com
//--------------------------------


void chapter1_1()
{
    auto x = 5;
    auto pi = new auto(1);
    const auto *y = &x;
    //u = 6;

    {
        int arr[] = {0};
        auto aa = arr;
        //auto rr[110]= arr;
        //Bar<int> bar;
    }

    {
        std::pair<int,int> key{1,1};
        std::unordered_multimap<int, int> result_map;
        //auto range = result_map.equal_range(key);
    }
    {
        func<Foo>();
        func<Bar>();
    }
}

void chapter1_2()
{
    int& func_int_r(void);
    int&& func_int_rr(void);
    int func_int(void);

    const int& func_cint_r(void);
    const int&& func_cint_rr(void);
    const int func_cint(void);

    const Foo func_cfoo(void);

    int x = 0;
    decltype(func_int_r()) a1 =x;
    decltype(func_int_rr()) b1 = 0;
    decltype(func_int()) c1 = 0;

    decltype(func_cint_r()) a2 = x;
    decltype(func_cint_rr()) b2 = 0;
    decltype(func_cint()) c2 = 0;

    decltype(func_cfoo()) ff = Foo();
}

int main()
{
    //chapter1_1();
    chapter1_1();
    return 0;
}
