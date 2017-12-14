#include <iostream>
#include "quote.h"
#include "bulk_quote.h"

//--------------------------------
// c++11 primer v5
//     chapter 15  面向对象程序设计OOP
//
//
//
//      2017-12-13 wlnetman@gmail.com
//--------------------------------

double print_total(std::ostream &os,
                   const Quote &item, std::size_t n)
{
    double ret = item.net_price(n);
    os << "ISBN: " << item.isbn()
       << " # sold: " << n << " total due:" << ret << std::endl;
    return ret;
}

void chapter15_1()
{
    // 继承，虚函数，动态绑定，
    Quote basic;
    Bulk_quote bulk;
    print_total(std::cout, basic, 20);
    print_total(std::cout, bulk, 20);
}

void chapter15_2()
{
    int n = 42;
    Quote item;
    Bulk_quote bulk;
    Quote *p = &item;
    p = &bulk;
    Quote &r = bulk;

    double ret = item.net_price(n);
    Quote base;
    //Bulk_quote* bulkP = &base;
    //Bulk_quote& bulkRef = base;
    Quote *itemP = &bulk;
    {
        Quote item(bulk);
        item = bulk;  // 切割
    }
}

void chapter15_3()
{
    Quote base("0-201-82470-1", 50);
    print_total(std::cout, base, 10);
    Bulk_quote derived("0-201-82470-1", 50, 5, .19);
    print_total(std::cout, derived, 10);
    base = derived;
    base.net_price(20);
    Quote* baseP = &base;
    double undiscounted = baseP->Quote::net_price(42);
}

int main(int argc, char* argv[])
{
    //chapter15_1();
    chapter15_2();
    chapter15_3();
    return 0;
}
