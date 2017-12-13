#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <initializer_list>
#include <new>
#include <algorithm>
#include <functional>

#include "sales_data.h"
#include "strvec.h"
#include "strblob.h"
#include "strblobptr.h"
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

void chapter14_3()
{
    // 算数运算符和关系运算符
    Sales_data d1("aaaa");
    Sales_data d2("bbb");
    // << 被重载了，cmd输出会有问题
    std::cout<< "d1==d2 ? " << (d1==d2) << std::endl;
    std::cout<< "d1!=d2 ? "<< (d1!=d2) << std::endl;
}

void chapter14_4()
{
    std::vector<std::string> v;
    v = {"a", "an", "the"};

    std::initializer_list<std::string> il = {"a", "an", "the"};
    StrVec sv;
    sv = il;

}

void chapter14_5()
{
    StrVec svec;
    svec.push_back("aaaa");
    svec.push_back("bbbbb");
    const StrVec cvec;
    if(svec.size() && svec[0].empty() )
        svec[0] = "zero";
        //cvec[0] = "Zip";
}

void chapter14_6()
{
    StrBlob a1;
    a1.push_back("dashi");
    a1.push_back("hege");
    a1.push_back("hege");
    StrBlobPtr p(a1);
    p.operator++(0);
    p.operator--(0);
    p.operator++(0);
    p.operator--(0);
}

void chapter14_7()
{
    StrBlob a1 = {"Dashi", "Hege", "zonglie"};
    StrBlobPtr p(a1);
    *p = "Okay";
    std::cout<< p->size() << std::endl;
    std::cout<< (*p).size() << std::endl;
}

struct absInt {
    int operator()(int val) const {
        return val < 0 ? -val : val;
    }
};

class PrintString {
public:
    PrintString(std::ostream &o = std::cout, char c = ' '):
        os(o), sep(c) { }
    void operator()(const std::string &s) const { os<< s << std::endl;}
private:
    std::ostream &os;
    char sep;
};

int add (int i, int j){
    return i + j;
}

void chapter14_8()
{
    int i = -42;
    absInt absObj;
    int ui = absObj(i);
    std::cout<< ui;

    std::string s("Dashi is good better best");
    PrintString printer;
    printer(s);
    PrintString error( std::cerr, '\n');
    error(s);

    std::vector<std::string> words = {"Dashi", "Zongli", "Hege"};

    // 可调用对象
    std::vector<std::string>::size_type sz;
    auto wc = std::find_if(words.begin(), words.end(),
                           [sz](const std::string &a){ return a.size() > sz; });


    std::plus<int> intAdd;
    std::negate<int> intNegate;
    int sum = intAdd(10, 20);
    sum = intNegate(intAdd(10,20));
    sum = intAdd(10, intNegate(10));

    StrVec svec;
    std::sort(svec.begin(), svec.end(), std::greater<std::string>());
    std::vector<std::string *> nameTable;
    std::sort(nameTable.begin(), nameTable.end(), std::less<std::string*>());

    // 可调用对象，function， lambda
    auto mod = [](int i, int j){ return i + j;};
    struct divide {
        int operator()(int den, int div){
            return den/div;
        }
    };

    std::map<std::string, int(*)(int,int)> binops2;
    binops2.insert({"+", add});
    //binops.insert({"+", mod});
    std::function<int(int,int)> f1 = add;
    std::function<int(int,int)> f2 = divide();
    std::function<int(int,int)> f3 = [](int i, int j)
                                        {return i + j;};
    std::cout<< f1(2,3) <<std::endl;
    std::cout<< f2(2,3) <<std::endl;
    std::cout<< f3(2,3) <<std::endl;

    std::map<std::string, std::function<int(int,int)>> binops = {
            {"+", add},
            {"-", std::minus<int>() },
            {"x", [](int i,int j){return i*j;}},
            {"/", divide() },
            {"%", mod} };
    binops["+"](10,5);
    binops["-"](10,5);
    binops["x"](10,5);
    binops["/"](10,5);
    binops["%"](10,5);

}

class SmallInt{
    friend SmallInt operator+(const SmallInt&, const SmallInt&);
public:
    SmallInt(int i = 0):val(i)
    {
        if( i < 0 || i > 255){
            throw std::out_of_range("Bad SmallInt value");
        }
    }
    explicit operator int() const { return val; }
    // operator int*() const { return 42; }
private:
    std::size_t val;
};
inline
SmallInt operator+(const SmallInt& i, const SmallInt& j)
{
    return SmallInt(i.val + j.val);
}


struct C{
    C(int);
};
struct D{
    D(int);
};
void mainp(const C&){};
void mainp(const D&){};

void chapter14_9()
{
    SmallInt si;
    si = 4;
    //si + 3.15;
    //si + 3;
    static_cast<int> (si) + 3;

    // IO operator bool

    // 实参匹配同类型
    struct B;
    struct A{
        A() = default;
        A(const B&){};
    };
    struct B{
        operator A() const{};
    };
    A f(const A&);
    B b;
    //A a = f(b);
    //A a1 = f(b.operator A());
    //A a2 = f(A(b));

    //mainp(190);
    SmallInt s1,s2;
    SmallInt s3 = s1 + s2;
    int i = int(s3) + 9;
}

int main(int argc,char* argv[])
{
    //chapter14_1();
    //chapter14_2();
    //chapter14_3();
    //chapter14_4();
    //chapter14_5();
    //chapter14_6();
    //chapter14_7();
    //chapter14_8();
    chapter14_9();
    return 0;
}
