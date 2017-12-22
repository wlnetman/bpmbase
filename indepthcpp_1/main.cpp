#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <type_traits>
#include <utility>
#include "template_compile.h"
#include "iterator.h"
#include "impl.h"
#include "range.h"
#include <tuple>

using std::cout;
using std::endl;
using std::tuple;
using std::vector;
using std::string;
using std::get;
using std::make_tuple;

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

namespace FooNew {
void func()
{

}

struct Foo
{
    void operator()(void)
    {
        std::cout<< "Foo operator()" << std::endl;
    }
};
struct Bar
{
    using fr_t = void(*)(void);
    static void func(void)
    {
        std::cout<< "static Bar func()" << std::endl;
    }
    operator fr_t(void)
    {
        std::cout<< "Foo fr_t" << std::endl;
        return func;
    }
};
struct A
{
    int a_;
    void mem_func(void)
    {
        std::cout<< "A mem_func" << std::endl;
    }
};
}

void chapter1_5()
{
    using namespace FooNew;
    // function 和bind
    void(* func_ptr)(void) = &func;
    func_ptr();

    FooNew::Foo foo;
    foo();

    FooNew::Bar bar;
    bar();

    void (FooNew::A::*mem_func_ptr)(void)
            = &FooNew::A::mem_func;
    int FooNew::A::*mem_obj_ptr
            = &FooNew::A::a_;
    FooNew::A aa;
    (aa.*mem_func_ptr)();
    aa.*mem_obj_ptr = 123;
}

namespace FooFunction {

// name space FooFunction begin
void func(void)
{
    std::cout<< __FUNCTION__ <<std::endl;
}
class Foo
{
public:
    static int foo_func(int a)
    {
        std::cout<< __FUNCTION__ << "(" << a << ") ->: ";
        return a;
    }
};
class Bar
{
public:
    int operator()(int a)
    {
        std::cout<< __FUNCTION__ << "(" << a << ")->: ";
        return a;
    }
};
class A
{
    std::function<void()> callback_;

public:
    A(const std::function<void()>& f)
        : callback_(f)
    {}
    void notify(void)
    {
        callback_();
    }
};
class FooCallback
{
public:
    void operator()(void)
    {
        std::cout<< __FUNCTION__ << std::endl;
    }
};

void call_when_even(int x, const std::function<void(int)>& f)
{
    if(!(x & 1))
    {
        f(x);
    }
}

void output(int x)
{
    std::cout<< x << " ";
}

void output2(int x, int y)
{
    std::cout<< x << " " << y << std::endl;
}

void output_add_2(int x)
{
    std::cout<< x + 2 << " ";
}


} // name space FooFunction

void chapter1_5_2()
{
    using namespace FooFunction;
    std::function<void(void)> fr1 = FooFunction::func;
    fr1();

    std::function<int(int)> fr2 = FooFunction::Foo::foo_func;
    std::cout<< fr2(123) << std::endl;

    FooFunction::Bar bar;
    fr2 = bar;
    std::cout<< fr2(123) << std::endl;
}

void chapter1_5_3()
{
    using namespace FooFunction;
    FooFunction::FooCallback foo;
    FooFunction::A aa(foo);
    aa.notify();

    {
        for(int i = 0; i < 10; ++i)
        {
            FooFunction::call_when_even(i, output);
        }
        std::cout<< std::endl;
    }

    {
        auto fr = std::bind(output_add_2, std::placeholders::_1);
        for( int i = 0; i < 10; ++i)
        {
            call_when_even(i, fr);
        }
        std::cout<< std::endl;
    }
    // 占位符
    {
        std::bind(FooFunction::output2, 1, 2)();
        std::bind(FooFunction::output2, std::placeholders::_1, 2)(1);
        std::bind(FooFunction::output2, 2, std::placeholders::_1)(1);
        // error
        //std::bind(output, std::placeholders::_2)(1);
        std::bind(FooFunction::output2, 2, std::placeholders::_2)(1,2);
        // skip
        std::bind(FooFunction::output2, std::placeholders::_1
                  ,std::placeholders::_2)(1, 2);
        std::bind(FooFunction::output2, std::placeholders::_2,
                  std::placeholders::_1)(1, 2);
    }
}

//lambda
//[capture](params) opt -> ret type {body};
class A_lambda
{
public:
    int i_ = 0;
    void func_lambda(int x, int y)
    {
        //error: C4573: the usage of 'A_lambda::i_' requires the compiler to capture 'this'
        //but the current default capture mode does not allow it
        //auto x1 = [] { return i_; };
        auto x2 = [=] { return i_ + x + y; };
        auto x3 = [&] { return i_ + x + y; };
        auto x4 = [this] { return i_; };
        //error: C3493: 'x' cannot be implicitly captured because no default capture
        //mode has been specified
        //auto x5 = [this] { return i_+ x + y;};
        auto x6 = [this, x, y] { return i_ + x + y; };
        auto x7 = [this] { return i_++; };
    }
};

void chapter1_6()
{
    int a = 0, b = 1;
    //error: C3493: 'a' cannot be implicitly captured
    //because no default capture mode has been specified
    //auto f1 = []{ return a; };
    auto f2 = [&] { return a++; };
    auto f3 = [=] { return a; };
    //error: C3491: 'a': a by copy capture cannot be modified
    //in a non-mutable lambda
    //auto f4 = [=] { return a++; };
    // error: C3493: 'b' cannot be implicitly captured because
    //no default capture mode has been specified
    //auto f5 = [a] { return a + b; };
    auto f6 = [a, &b] {return a + (b++); };
    auto f7 = [=, &b] { return a + (b++); };
}

class CountEvent
{
    int& count_;
public:
    CountEvent(int& count)
        : count_(count)
    {}
    void operator()(int val)
    {
        if(!(val & 1))
        {
            ++ count_;
        }
    }
};

void chapter1_6_2()
{
    std::vector<int> v = {1, 2, 3, 4, 5, 6};
    int event_count = 0;
    std::for_each(v.begin(), v.end(), CountEvent(event_count));
    std::cout<< "Event is " << event_count << std::endl;

    // lambda
    std::for_each(v.begin(), v.end(), [&event_count](int val)
    {
        if(! (val & 1))
          {
              ++event_count;
          }
    });

    std::cout<< "Event is " << event_count << std::endl;

}

void chapter1_7()
{
    // tupe 元组
    //std::tuple<const char*, int> tp = std::make_tuple<sendPack, nSecondSize>;
    int x = 1;
    int y = 2;
    std::string s = "Fuck";
    auto tp = std::tie(x, s, y);
    std::tie(std::ignore, std::ignore, y) = tp;
    // vc 里面get调用tuple方法有问题
    //error: C2039: 'get': is not a member of 'std::tuple<int &,std::string &,int &>'
    //const char* data = get<0>(tp);
    std::cout<< get<0>(tp) << std::endl;
    //int len = get<1>(tp);
    std::cout<< get<1>(tp) << std::endl;
    //std::cout<< data << "len = " << len << std::endl;

    std::map<int, std::string> m;
    m.emplace(std::piecewise_construct,
              std::forward_as_tuple(10),
              std::forward_as_tuple(20, 'a'));
   std::tuple<int, std::string, float> t1(10, "Test", 3.14);
   int n = 7;
   auto t2 = std::tuple_cat(t1, std::make_pair("Foo", "bar"), t1,
                            std::tie(n));
   n = 10;
   std::cout<< std::get<0>(t2)
            << std::get<1>(t2)
            << std::get<2>(t2)
            << std::endl;
}

int main()
{
    //chapter1_1();
    //chapter1_4();
    //test_range();
    //chapter1_5();
    //chapter1_5_2();
    //chapter1_5_3();
    //chapter1_6();
    //chapter1_6_2();
    chapter1_7();
    return 0;
}
