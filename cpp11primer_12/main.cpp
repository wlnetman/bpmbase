#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <list>
#include <new>

#include "strblob.h"

//--------------------------------
// c++11 primer v5
//     chapter 12  动态内存
//       内存：栈(函数变量、小)，堆(自由空间、大)
//  智能指针：自动释放所指向的对象
//       shared_ptr 多个指针指向同一个对象
//       unique_ptr 独占所指向的对象
//       weak_ptr   弱引用,指向shared_ptr管理的对象
//
//      2017 -12-04 @wlnetman@gmail.com
//--------------------------------

template  <typename Foo, typename T>
std::shared_ptr<Foo> factory(T arg)
{
    return std::make_shared<Foo>(arg);
}

std::shared_ptr<int> clone(int p){
    return std::shared_ptr<int>(new int(p));
}

void process(std::shared_ptr<int> ptr)
{
    ++(*ptr);
    //delete ptr;
    return;
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

    //默认初始化的值未定义
    //内置初始化按照函数走
    int *newp = new int;
    int *newp2 = new int();
    *newp = 10;
    int *pi = new int(1024);
    std::string *ps = new std::string(10,'s');
    std::vector<int> *pv = new std::vector<int>{0,1,2,3,4,5,6,7,8,9};
    auto p15 = new auto(StrBlob());
    const std::string *pcs = new std::string;
    int *p8 = new (std::nothrow) int;
    delete newp;
    delete newp2;
    delete pi;
    delete ps;
    delete pv;
    delete p15;
    delete p8;
    delete pcs;
    pcs = nullptr; //有限的保护

    std::shared_ptr<double> p10;
    std::shared_ptr<int> p12(new int(42));

    process(p12);
    int i = *p12;

    int *x(new int(1024));
    //process(x);
    process(std::shared_ptr<int>(x));
    int j = *x; // 悬空

    int *qq = p12.get();
    {
        std::shared_ptr<int>(q);
    }
    int foo = *p12;  // 无效

    p12.reset(new int(42));

    std::shared_ptr<std::string> ps2(new std::string("ee"));
    if( !ps2.unique())
        ps2.reset(new std::string(*ps2));
    *ps2 += "LW";

}

/*
void end_connection(connection *p){ disconnect(*p); }
void f(destination &d)
{
    connection c = connect(&d);
    std::shared_ptr<connection> p(&c, end_connection();)
}
*/
struct destination
{
    int a;
};
struct connection
{
    int a;
};
connection connnect(destination*){ connection a; return a;};
void disconnect(connection){};

// 删除器
void end_connection(connection* p) {disconnect(*p);}

void f(destination &d)
{
    // 获得一个连接；记住使用完毕关闭
    connection c = connnect(&d);
    // 不调用disconnect就无法关闭c

    connection c2 = connnect(&d);
    std::shared_ptr<connection> p(&c, end_connection);

    // 退出时会自动关闭
}

void chapter12_1_4()
{
    std::unique_ptr<double> p1;
    //std::unique_ptr<std::string> p2(p1);
    std::unique_ptr<std::string> p3;
    //p3 = p2;
    p1.release();
    p1.reset();
}


// unique_ptr
//std::unique_ptr<int> clone(int p)
//{
//    return std::unique_ptr<int>(new int(p));
//}
// 删除器
//std::unique_ptr<objT, delT> p(new objT, fcn);
//void f(destionation& d)
//{
//    connection c = connnect(&d);
//    std::unique_ptr<connection, decltype(end_connection)*> p(&c, end_connection);
//}

void chapter12_1_5()
{
    // 创建
    std::unique_ptr<double> p1;
    std::unique_ptr<int> p2(new int(423));

    // 切断联系
    std::unique_ptr<double> p3(p1.release()); // p1为空
    std::unique_ptr<double> p4(p3.release());
    p4.reset(p3.release());

    // 传递

}

// strblob.h
// strblob.cpp
void chapter12_1_6()
{
    auto p = std::make_shared<int>(42);
    std::weak_ptr<int> wp(p);

    if(std::shared_ptr<int> np = wp.lock()){
        // np与p共享对象
    }

    // StrBlobPtr
    StrBlobPtr strP;

}

int main(int argc,char* argv[])
{
    //chapter12_1();
    //chapter12_1_4();
    //chapter12_1_5();
    chapter12_1_6();
    return 0;
}
