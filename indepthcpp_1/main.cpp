#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <algorithm>
#include "template_compile.h"
#include "iterator.h"
#include "impl.h"
#include "range.h"

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

void do_cout(int i)
{
    std::cout<< i <<std::endl;
}

void chapter1_4()
{
    // for 循环 for_eacho
    std::vector<int> arr{1,2,3,4,5,6,7};
    std::for_each(arr.begin(), arr.end(), do_cout);
    for( auto n : arr)
        std::cout<< n << std::endl;

    //std::pair
    std::map<std::string, int> mm =
    {
        {"1", 1}, {"2", 2}, {"3", 3}
    };

    for( auto ite = mm.begin(); ite != mm.end(); ++ite)
    {
        std::cout << ite->first << " -> " << ite->second << std::endl;
    }

    for( auto& val : mm)
    {
        std::cout<< val.first << " -> " << val.second << std::endl;
    }
}

void test_range(void)
{
    using namespace detail_range;
    std::cout<< "range(15):";
    for(int i : range(15))
    {
        std::cout << " " << i;
    }
    std::cout << std::endl;

    std::cout<< "range(2,6):";
    for(int i : range(2,6))
    {
        std::cout << " " << i;
    }
    std::cout << std::endl;

    const int x = 2, y = 6, z = 3;
    std::cout << "range(2, 6, 6):";
    for(auto i : range(x, y, z))
    {
        std::cout << " " << i;
    }
    std::cout<< std::endl;

    std::cout << "range(-2, -6, -3):";
    for(auto i : range(-2, -6, -3))
    {
        std::cout << " " << i;
    }
    std::cout<< std::endl;

    std::cout << "range(10.5,15.5):";
    for(auto i : range(10.5,15.5))
    {
        std::cout << " " << i;
    }
    std::cout<< std::endl;

    std::cout << "range(35,27,-1):";
    for(auto i : range(35,27,-1))
    {
        std::cout << " " << i;
    }
    std::cout<< std::endl;

    std::cout << "range(2,8,0.5):";
    for(auto i : range(2,8,0.5))
    {
        std::cout << " " << i;
    }
    std::cout<< std::endl;

    std::cout << "range(8,7,-0.1):";
    for(auto i : range(8,7,-0.1))
    {
        std::cout << " " << i;
    }
    std::cout<< std::endl;

    std::cout << "range('a', 'z'):";
    for(auto i : range('a', 'z'))
    {
        std::cout << " " << i;
    }
    std::cout<< std::endl;


}

int main()
{
    //chapter1_1();
    //chapter1_4();
    test_range();
    return 0;
}
