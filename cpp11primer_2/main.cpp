#include <iostream>
#include "fmt/format.h"
#include "sales_item.h"

void c2_1()
{
    bool b = 42;
    int i = b;
    i = 3.14;
    double pi = i;
    unsigned char c = -1;
    signed char c2 = 256;
    std::cout << b << " ";
    std::cout << i << " " << pi << " ";
    std::cout << c << " ";
    std::cout << "c2=" << c2 << std::endl;

    std::string ret = fmt::format("b={},i={},pi={},c={},c2={}", b,i,pi,c,c2);
    std::cout << ret;

    unsigned u1 = 42, u2 =10;
    std::cout << std::endl << u1 - u2 << std::endl;
    std::cout << u2 - u1 << std::endl;

    for(unsigned char u = 10; u <= 0; --u)
        std::cout << u << std::endl;

    unsigned char u = 11;
    while (u > 0 ) {
        --u;
        std::cout << u << std::endl;
    }
}

int reused = 42;
void c2_2()
{
    int unique = 0;
    std::cout << reused << " " << unique << std::endl;
    int reused = 0;
    std::cout << reused << " " << unique << std::endl;
    //显式访问
    std::cout << ::reused << " " << unique << std::endl;
}

void c2_2_1()
{
    //int units_sold = 0;
    //int units_sold = {0};
    int units_sold{0};
    //int units_sold(0);
}

int c2_3()
{
    // 引用，绑定了另一个名称,不是对象，没有访问地址.
    // 指针，是对象，可以赋值拷贝
    int ival = 1024;
    int &refVal = ival;
    int &refVal2 = refVal;
    std::cout << ival << "refVal" << refVal << " "
              << refVal2 << std::endl;
    refVal2 = 2048;
    std::cout << ival << "refVal" << refVal << " "
              << refVal2 << std::endl;

    double dval;
    double *pd = &dval; // 指向dval的地址
    double *pd2 = pd;   // 指向dval的指针


    return 0;
}

void c2_4()
{
    const int bufsize = 512;
    //bufsize = 1024;

    int i = 42;
    const int ci = i;
    int j = ci;
    const int &r1 = ci;

    const double pi = 3.14;
    //double *ptr = &pi;
    const double *cptr = &pi;
    double dval = 3.14;
    std::cout << cptr << "-->" << std::endl;
    cptr = &dval;
    std::cout << cptr << "--" << dval << std::endl;

    int errNumb = 0;
    int *const curErr = &errNumb;
    //const double pi = 3.1415926;
    const double *const pip = &pi;

    //*pip = 333;
    if(*curErr){
        std::cout<< "ERROR" <<std::endl;
        *curErr = 0;
    }
}

// auto 变量
void c2_5()
{
    Sales_item val1;
    Sales_item val2;
    auto result = val1 + val2;
    std::cout << result << std::endl;

    const int i = 42;
    auto j = i;
    const auto &k = i;
    auto *p = &i;
    const auto j2 = i, &k2 = i;
    // 便以失败时可以看到auto对应的数据类型
    //fmt::format("j{} k{} p{} j2{} k2{}", j, k, p, j2, k2);
    decltype(j) a;
}

struct Sales_data{
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0;
};
int  c2_6()
{
    Sales_data data1, data2;
    double price = 0;
    std::cin >> data1.bookNo >> data1.units_sold >> price;
    data1.revenue = data1.units_sold * price;
    std::cin >> data2.bookNo >> data2.units_sold >> price;
    data2.revenue = data2.units_sold * price;

    if(data1.bookNo == data2.bookNo){
        unsigned totalCnt = data1.units_sold + data2.units_sold;
        double totalRevenue = data1.revenue + data2.revenue;
        std::cout << data1.bookNo << " " << totalCnt
                  << " " << totalRevenue << " ";
        if(totalCnt != 0)
            std::cout << totalRevenue/totalCnt << std::endl;
        else
            std::cout << "No sale" << std::endl;
    } else {
        std::cerr<< "Data must refer to the same isbn" << std::endl;
        return -1;
    }
    return 0;
}

int main(int argc,char* argv)
{
    //c2_1();
    //c2_2();
    //c2_3();
    //c2_4();
    //c2_5();
    c2_6();
    return 0;
}
