#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <vector>
#include <list>
#include <new>
#include <algorithm>

#include "sales_data.h"
#include "hasptr.h"
#include "message.h"
#include "folder.h"
#include "strvec.h"

//--------------------------------
// c++11 primer v5
//     chapter 13  拷贝控制
//
//
//
//      2017 -12-11 wlnetman@gmail.com
//--------------------------------

//阻止拷贝
struct NoCopy{
    NoCopy() = delete;
};

// 析构函数不能使delete
struct NoDelete{
    ~NoDelete() = delete;
};


void chapter13_1()
{
    Sales_data trans, accm;
    trans = accm;

    {
        Sales_data *p = new Sales_data;
        auto p2 = std::shared_ptr<Sales_data>();
        Sales_data item(*p);
        std::vector<Sales_data> vec;
        //vec.push_back(*p2); // 未初始化会崩溃
        delete p;
    }
}

void chapter13_2()
{
    //类对象行为像值，行为像指针
    HasPtr hs("Dashi");
    //delete hs;
}

void chapter13_3()
{
    // swap 交换对象
    HasPtr lhs("Dashi");
    HasPtr rhs("Hege");
    using std::swap;
    swap(lhs, rhs);
}

void chapter13_4()
{
    // 拷贝控制
    Message msg("msg1");
    Message msg2("msg2");
    Folder f("F1");
    Folder f2("F2");

}

void chapter13_5()
{
    // 动态内存管理 alloc
    StrVec str;
    str.push_back("aaaaaaaaaa");
    str.push_back(std::string(1024,'s'));
    std::cout<< *(str.begin()) << std::endl;
}

class Foo{
public:
    Foo sorted() &&;
    Foo sorted() const &;

    Foo retFoo();
    Foo& retval();
private:
    std::vector<int> data;
};
Foo Foo::sorted() &&
{
    sort(data.begin(), data.end());
    return *this;
}
Foo Foo::sorted() const &{
    Foo ret(*this);
    std::sort(ret.data.begin(), ret.data.end());
    return ret;
}
Foo retFoo()
{
    Foo ret;
    return ret;
}


void chapter13_6()
{
    // 对象移动
    int i = 42;
    int &r = i;
    int &&rr = i * 42;
    int &&rr1 = 42;
    std::cout<< rr << "r" << r << rr1 << std::endl;

    int &&rr3 = std::move(rr1);

    StrVec v1,v2;
    v1 = v2;
    //v2 = getVec(std::cin);


    {
        // 慎重使用move
        HasPtr hp("Hp1");
        HasPtr &hp2 = hp;
        //hp = hp2;
        //hp = std::move(hp2);
    }

    StrVec vec;
    std::string s = "Some String or another";
    vec.push_back(s);
    vec.push_back("sssssss");

    // 重载引用函数
    retFoo().sorted();
}

int main(int argc,char* argv[])
{
    //chapter13_1();
    //chapter13_2();
    //chapter13_3();
    chapter13_4();
    chapter13_5();
    chapter13_6();
    return 0;
}
