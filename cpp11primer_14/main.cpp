#include <iostream>
#include <string>

#include "sales_data.h"

//--------------------------------
// c++11 primer v5
//     chapter 14  重载运算和类转换
//
//
//
//      2017-12-13 wlnetman@gmail.com
//--------------------------------

void chapter14_1()
{
    // 不可以重载的运算符
    // :: .*  .  ? :   ,
    //
    std::string s = "world";
    std::string t = s + "!";
    std::string u = "U" + s;

}

void chapter14_2()
{
    Sales_data data;
    std::cout << data;

    std::cin >> data;

    Sales_data data1;
    Sales_data data2;
    Sales_data data3;
    data3 = data1 + data2;

}

int main(int argc,char* argv[])
{
    //chapter14_1();
    chapter14_2();
    //chapter14_3();
    return 0;
}
