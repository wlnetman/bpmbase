#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <list>

#include "strblob.h"

//--------------------------------
// c++11 primer v5
//     chapter 12  动态内存
//       内存：栈(函数变量、小)，堆(自由空间、大)
//       shared_ptr weak_ptr unique_ptr
//
//      2017 -12-04 @wlnetman@gmail.com
//--------------------------------

template  <typename Foo, typename T>
std::shared_ptr<Foo> factory(T arg)
{
    return std::make_shared<Foo>(arg);
}

void chapter12_1()
{
    // share_ptr
    std::shared_ptr<std::string> p1;
    std::shared_ptr<std::list<int>> p2;
    if(p1 && p1->empty())
        *p1 = "Dashi";

    std::shared_ptr<int> p3 = std::make_shared<int>(42);
    std::shared_ptr<std::string> p4 = std::make_shared<std::string>(10,'9');
    std::cout<< *p4 << std::endl;
    std::shared_ptr<int> p5 = std::make_shared<int>();
    auto p6 = std::make_shared<std::vector<std::string>>();
    auto p = std::make_shared<int>(42);
    auto q(p);
    auto r = std::make_shared<int>(42) ;
    r = q; // 丢失r指向的42的内存


    {
        int arg = 4;
        auto p = factory<int>(arg); // 离开释放
    }

    std::shared_ptr<int> q2;
    {
        int arg = 4;
        auto p = factory<int>(arg);
        q2 = p; // 不会释放
    }

    std::vector<std::string> v1;
    {
        std::vector<std::string> v2 = {"an", "an", "the"};
        v1 = v2;
    }
    std::cout<< v1.at(0) << std::endl;

    StrBlob b1;
    {
        StrBlob b2 = {"a", "an", "the"};
        b1 = b2;
        b2.push_back("abuot");
    }
}

int main(int argc,char* argv[])
{
    chapter12_1();
    return 0;
}
