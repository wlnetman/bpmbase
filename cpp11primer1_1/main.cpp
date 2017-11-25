#include <iostream>
#include "sales_item.h"

void c1_2()
{
    std::cout << "input Tow number" << std::endl;
    int v1,v2;
    std::cin >> v1 >> v2;
    std::cout << "The sum of v1:"<< v1<< " and "<< v2 <<" is: " << v1+v2 << std::endl;
}

void c1_4()
{
    int val = 0,sum = 0;
    while (val<10) {
        sum += val;
        ++val;
    }
    std::cout << "Sum of 1 to 10 inclusive is "
              << sum << std::endl;
}

void c1_4_2()
{
    int sum=0;
    for(int val=1; val<=10; ++val)
        sum += val;
    std::cout << "Sum 1-10:"
              << sum << std::endl;
}

void c1_4_3()
{
    int sum = 0, value = 0;
    while(std::cin >> value)
    {
        sum += value;
    }
    std::cout << "Sum is :" << sum << std::endl;
}

void c1_4_4()
{
    int currVal = 0, val = 0, cnt = 0;
    if(std::cin >> currVal)
    {
        cnt =1;
        while (std::cin >> val) {
            if( currVal == val)
            {
                cnt++;
            } else {
                std::cout << currVal << " occous "
                          << cnt << " times" << std::endl;
                currVal = val;
                cnt = 1;
            }
        }
        std::cout << currVal << " occous "
                  << cnt << " times " << std::endl;
    }
}

void c1_7()
{
    /*不正确注释嵌套
    // * 注释fau/* dsd*/
    // *
    //*/
    return;
}

void c1_9()
{
    int i=50;
    int sum = 0;
    while ( i<=100) {
        sum += i++;
    }
    std::cout << "sum 50-100 = " << sum << std::endl;
}

void c1_11()
{
    int i1,i2;
    std::cout << "Input Two Interge:" << std::endl;
    std::cin >> i1 >> i2;
    int num = i1;
    while ( num <= i2) {
        std::cout << num << std::endl;
        num++;
    }
}

void c1_5_1()
{
    Sales_item book;
    std::cin >> book;
    std::cout << book << std::endl;
}

void c1_5_3()
{
    Sales_item item1,item2;

    std::cin >> item1 >> item2;
    std::cout << item1 + item2 << std::endl;
}

int c1_5_5()
{
    Sales_item item1,item2;

    std::cin >> item1 >> item2;
    if(item1.isbn() == item2.isbn())
    {
        std::cout << item1 + item2 << std::endl;
        return 0;
    } else {
        std::cout << "Data must refer to same ISBN"
                  << std::endl;
        return -1;
    }

}

int c1_6_1()
{
    Sales_item total;
    if(std::cin >> total)
    {
        Sales_item trans;
        while( std::cin >> trans)
        {
            // 处理相同的isbn
            if(total.isbn() == trans.isbn())
            {
                total += trans;
            } else {
                std::cout << total << std::endl;
                total = trans;
            }
        }
        std::cout << total << std::endl;
    } else {
        std::cout << "NO data!" << std::endl;
        return -1;
    }
    return 0;
}

// 学习一门新的程序设计语言的最好方法就是练习编写程序
int main(int argc,char* argv)
{
    //c1_2();
    //c1_7();
    //c1_8();
    //c1_9();
    //c1_4();
    //c1_4_2();
    //c1_4_3();
    //c1_4_4();
    //c1_5_1();
    //c1_5_3();
    //c1_5_5();
    c1_6_1();
    return 0;
}

