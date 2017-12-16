#include <iostream>
#include <vector>
#include <memory>

#include "quote.h"
#include "bulk_quote.h"
#include "disc_quote.h"
#include "basket.h"
#include "base.h"
#include "query.h"

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


void chapter15_4()
{
    //error: C2259: 'Disc_quote': cannot instantiate abstract class
    //Disc_quote discounted;


    Bulk_quote bulk;

    Pub_Derv d1;
    Pub_Derv d2;
    d1.pub_mem();
    d2.pub_mem();
}

void chapter15_5()
{
    Bulk_quote bulk;
    Bulk_quote *bulkP = &bulk;
    Quote *itemP = &bulk;
    bulkP->discount_policy();
    //error: C2039: 'discount_policy': is not a member of 'Quote'
    //itemP->discount_policy();
}

void chapter15_6()
{
    // 继承中的类作用域
    Bulk_quote bulk;
    std::cout<< bulk.isbn();
    Bulk_quote *bulkP = &bulk;
    Quote* itemP = bulkP;
    bulkP->discount_policy();
    //itemp->discount_policy();

    // 名字查找优先于类型监察
    Deriverd d;
    Base b;
    b.memfcn();
    //d.memfcn(10);
    //d.memfcn();
    d.Base::memfcn();

    // 虚函数和作用域
}

void chapter15_7()
{
    // 虚析构函数
    Quote *itemP = new Quote;
    delete itemP;
    itemP = new Bulk_quote;
    delete itemP;

    // 移动操作与继承
    //D(&& d): Base(std::move(d)){}
}

void chapter15_8()
{
    std::vector<Quote> basket;
    basket.push_back( Quote("3333", 49) );
    basket.push_back(Bulk_quote("aaaa",40, 30, .23));
    std::cout<< basket.back().net_price(13) <<std::endl;

    {
        std::vector<std::shared_ptr<Quote>> basket;
        basket.push_back(std::make_shared<Quote>("aaaa",42));
        basket.push_back(std::make_shared<Bulk_quote>("aaaa",40, 30, .23));
        std::cout<< basket.back()->net_price(13) <<std::endl;
    }

    {
        Basket bsk;
        bsk.add_item(std::make_shared<Quote>("123", 42));
        bsk.add_item(std::make_shared<Bulk_quote>("345", 45, 3, .15));
    }

}

void chapter15_9()
{
    std::string sought1 = "a";
    std::string sought2 = "2";
    Query andq = Query(sought1) & Query(sought2);
    std::cout<< andq << std::endl;
}

int main(int argc, char* argv[])
{
    //chapter15_1();
    //chapter15_2();
    //chapter15_3();
    //chapter15_4();
    //chapter15_5();
    //chapter15_6();
    //chapter15_7();
    //chapter15_8();
    chapter15_9();
    return 0;
}
