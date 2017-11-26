#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include "fmt/format.h"

void chapter4_12345()
{
    std::cout << (6 + 3) * (4 / 2 + 2) << std::endl;
    std::cout << ((6 + 3) * 4) / 2 + 2 << std::endl;
    std::cout << 6 + 3 * 4 /(2 + 2) << std::endl;

    int ia[] = {0,2,4,6,8};
    int last = *(ia + 4);
    std::cout << last << std::endl; //4
    last = *ia + 4;
    std::cout << last << std::endl; //4

    int i = 0;
    // 错误例子，++  跟 << 优先级一样
    std::cout << i << " " << ++i << std::endl;

    short short_value = 32767;
    short_value += 1;
    std::cout << "short_value :" << short_value << std::endl; // -32768

    // % 取模跟 /除法
    std::cout << "21%6=" << (21 % 6) << " 21/6= " << (21/6) << std::endl;
    std::cout << "21%7=" << (21 % 7) << " 21/7= " << (21/7) << std::endl;
    std::cout << "-21%-8=" << (-21 % -8) << " -21/-8= " << (-21/-8) << std::endl;
    std::cout << "21%-5=" << (21 % -5) << " 21/-5= " << (21/-5) << std::endl;

    // 逻辑运算符
    std::vector<std::string> text{"WangLinDaShi BPM.","old Programmers!.","He is a handsome man\n.",".\n"};
    for(const auto &s : text){
        std::cout << s;
        if(s.empty() || s[s.size()-1] == '.')
            std::cout << std::endl;
        else
            std::cout << " ";
    }

    auto pbeg = text.begin();
    while (pbeg != text.end() && (*pbeg).size()>=2 ) {
        std::cout << *pbeg++ << std::endl;
    }
}

void chapter4_678()
{
    std::string s1 = "mystring", *p = &s1;
    auto n = s1.size();
    n = (*p).size();
    n = p->size();
    std::cout << n << ",*p=" << (*p) << std::endl;

    // 位运算符
    unsigned long quiz1 = 0;
    quiz1 |= 1UL << 27;
    bool status = static_cast<bool>(quiz1 & (1UL << 27));
    std::bitset<64> bin = quiz1;
    std::cout << fmt::format("nquiz1=[{}]\nquiz1={}, status={}\n", bin.to_string(), quiz1, status);
    //quiz1 = quiz1 | 1UL << 27;
    quiz1 &= ~(1UL << 27);
    quiz1 |= 1UL << 28;
    status = static_cast<bool>(quiz1 & (1UL << 27));
    bin = quiz1;
    std::cout << fmt::format("nquiz1=[{}]\nquiz1={}, status={}\n", bin.to_string(), quiz1, status);
}

struct Sales_data{
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0;
};
void chapter4_9()
{
    std::bitset<64> bin = 1UL;

    // sizeof
    Sales_data data, *p;
    std::cout<< sizeof(Sales_data) << std::endl; // 40
    std::cout<< sizeof Sales_data << std::endl; // 40
    std::cout<< sizeof data << std::endl; //40
    std::cout<< sizeof p << std::endl;  // 4
    std::cout<< sizeof *p << std::endl;  //40
    std::cout<< sizeof data.revenue << std::endl; // 8
    std::cout<< sizeof Sales_data::revenue <<std::endl; //8
    std::cout<< sizeof bin << std::endl;  // 8
    std::cout<< sizeof('2') << std::endl;  // 1
    std::cout<< sizeof("2") << std::endl;  // 2
    std::cout<< sizeof(L"2") << std::endl;  // 4
    std::cout<< sizeof(std::string("")) << std::endl;  // 28
}

void chapter4_11()
{
    bool flag;
    char cval;
    short sval;
    int ival;
    long lval;
    float fval;
    unsigned short usval;
    unsigned int uival;
    double dval;
    std::cout << 3.141592653 + 'a' + flag << std::endl;
    std::cout << dval + ival << std::endl;
    std::cout << dval + fval << std::endl;
    std::cout << (ival == dval) << std::endl;
    //std::cout << decltype(flag = dval) << std::endl;
    std::cout << sval + lval << std::endl;
    std::cout << uival + lval << std::endl;

    // static_cast    不包含const
    int i, j;
    double slope = static_cast<double>(j) / i;

    // const_cast 只能改变底层const
    const char *cp;
    char *p = const_cast<char*>(cp);
    static_cast<std::string>(cp);

    // dynamic_cast
    // reinterpret_cast
    int *ip;
    char *pc = reinterpret_cast<char*>(ip);

    std::string str(pc);
    std::cout << str << std::endl;
}

int main(int argc, char *argv)
{

    //chapter4_12345();
    //chapter4_678();
    //chapter4_9();
    //chapter4_11();
    return 0;
}
