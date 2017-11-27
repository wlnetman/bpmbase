#include <iostream>
#include <string>
#include <vector>
#include <assert.h>
#include <cassert>

#include <initializer_list>
#include "fmt/format.h"
#include "sales_item.h"

//--------------------------------
// c++11 primer v6
//     chapter 5 statement
// 函数，重载，实参形参
//
//      2017-11-27 @wlnetman@gmail.com
//--------------------------------

void print(const int *beg, const int *end);
void print(const int ia[], std::size_t size);
void print(int (&arr)[10]);
void print(int (*matrix)[10], int rowSize);

int fact(int val)
{
    int ret = 1;
    while (val > 1)
        ret *= val--; // 经典阶乘函数
    static size_t ctr = 0;
    ctr++;
    std::cout<< "call " << ctr << " times" <<std::endl;
    return ret;
}

void chapter6_1()
{
    int j = fact(2.2);
    std::cout<< j << std::endl;

    for(int i = 1; i <= 10; ++i){
        std::cout<< i << "\t"
                 << fact(i) << std::endl;
    }


}

bool isShorter(std::string &s1, std::string &s2)
{
    return s1.size() > s2.size();
}

std::string::size_type find_char(const std::string &s, char c,
                                 std::string::size_type &occurs)
{
    auto ret = s.size();
    occurs = 0;
    for(decltype(ret) i = 0; i != s.size(); ++i){
        if( s[i] == c){
            if(ret == s.size())
                ret = i;
            ++occurs;
        }
    }
    return ret;
}

bool is_sentence(const std::string &s)
{
    std::string::size_type ctr = 0;
    return find_char(s, '.', ctr) == s.size() - 1 && ctr == 1;
}

void print(const int *beg, const int *end)
{
    while (beg != end) {
        std::cout << *beg++ << std::endl;
    }
}

void print(const int ia[], std::size_t size)
{
    for(std::size_t i = 0; i != size; ++i)
        std::cout<< ia[i] << std::endl;
}

// 数组形式形参
void print(int (&arr)[10])
{
    for(auto elem : arr)
        std::cout<< elem <<std::endl;
}

void print(int (*matrix)[10], int rowSize)
{
    std::cout<< fmt::format("addr:matrix[{}]", static_cast<void*>(matrix));
    std::cout<< fmt::format("rowSize[{}]", rowSize);
}

void error_msg(std::initializer_list<std::string> il)
{
    for(auto beg = il.begin(); beg != il.end(); ++beg)
        std::cout<< *beg << " ";
    std::cout<< std::endl;
}

using ErrCode = int;
void error_msg(ErrCode e, std::initializer_list<std::string> il)
{
    std::cout<< e << ": ";
    for( const auto &elem : il){
        std::cout<< elem << " " ;
    }
    std::cout<< std::endl;
}

void chapter6_2()
{
    const std::string s{"WangDaShi is good person and he is very handsome."};
    decltype(s.size()) ctr = 0;
    auto index = find_char(s, 'o', ctr);
    std::cout<< fmt::format("find char w in s:{},occurs:{}\n", index, ctr);

    std::cout<< fmt::format("s is a sentence:{}\n", is_sentence(s));

    int j[2]{1,2};
    print(std::begin(j), std::end(j));
    print(j, std::end(j)- std::begin(j));
    int k[10] = {0,1,2,3,4,5,6,7,8,9};
    //print(j); // error
    print(k);
    error_msg({"Error Message", "fuck", "ok", "system error"});
}

// 判断是否两个字符串中一个是另一个的子集
bool str_subrange(const std::string &str1, const std::string &str2)
{
    if(str1.size() == str2.size())
        return str1 == str2;
    auto size = str1.size() > str2.size() ? str2.size() : str1.size();
    for(decltype(size) i = 0; i != size; ++i){
        if(str1[i] != str2[i])
            return false;
    }
    return true;
}

std::string make_plural(std::size_t ctr, const std::string &word,
                        const std::string &ending)
{
    return (ctr > 1) ? word + ending : word;
}

auto &shorterString(const std::string &s1,
                                 const std::string &s2)
{
    return s1.size() <= s2.size() ? s1 : s2;
}

char &get_val(std::string &str, std::string::size_type ix)
{
    return str[ix];
}

std::vector<std::string> process()
{
    if(0)
        return {};
    else
        return {"functioniX", "2", "end"};
}

double factorial(int val)
{
    if(val > 1)
        return factorial(val-1)*val;
    return 1;
}

//  指针，指向实参为整型，大小为10的整型数组
int (*func(int i))[10];
// niubility的 c++11
auto func(int i) -> int(*)[10];

int odd[] = {1,3,5,7,9};
int even[] = {2,4,6,8, 10};
decltype(odd) *arrPtr(int i)
{
    return ( i % 2) ? &odd : &even;
}

void chapter6_3()
{
    bool ret = str_subrange("wangdashi", "wang");
    std::cout<< ret << std::endl;
    ret = str_subrange("waNgdashi", "wang");
    std::cout<< ret << std::endl;

    const std::string w = "people";
    const std::string e = "peoples";
    std::cout<< make_plural(10, w, e) << std::endl;

    std::cout<< shorterString(w,e) <<std::endl;

    std::cout<< get_val(std::string("qwertyuiop"), 2) <<std::endl;

    std::cout<< factorial(17) <<std::endl;


}

//Record lookup(const Account&);
//Record lookup(const phone&);
//Record lookup(const Name&);
std::string shorterString(std::string &s1, std::string &s2)
{
    auto &r = shorterString(const_cast<const std::string&>(s1),
                         const_cast<const std::string&>(s2));
    return const_cast<std::string&>(r);
}

void chapter6_4()
{
    auto a = shorterString(std::string("Dashi"), std::string("Dashigood"));
    std::cout<< a <<std::endl;
}

typedef std::string::size_type sz;
inline std::string screen(sz ht = 800, sz wid = 600, char backgrnd = ' ')
{
    std::string ret = fmt::format("{} X {} [{}]", ht, wid, backgrnd);
    return ret;
}

// 常量函数
constexpr int new_sz() { return 42; }
constexpr int foo = new_sz();
constexpr std::size_t scale(std::size_t cnt) {return new_sz() * cnt;}
void chapter6_5()
{
    std::cout<< screen() << std::endl;
    std::cout<< screen(1027, 768, '3') << std::endl;

    int arr[scale(2)] ={ 1,2,3,4,5};
    std::cout<< arr[2] << std::endl;


    assert(1);
    //assert(0);
#ifndef NDEBUG
    std::cout<< "Eror: " << __FILE__
             << " : in function " << __func__
             << " at line " << __LINE__ << std::endl
             << " at " << __TIME__ << std::endl
             << "over!" <<std::endl;
#endif

}

// 函数指针
bool lengthCompare(const std::string &, const std::string &);
bool lengthCompare(const std::string &s1, const std::string &s2)
{
    return s1.size() > s2.size();
}
bool (*pf)(const std::string &, const std::string &);
void useBigger(const std::string&s1, const std::string &s2,
               bool pf(const std::string &s1, const std::string &s2));
void useBigger(const std::string&s1, const std::string &s2,
               bool (*pf)(const std::string &s1, const std::string &s2));
typedef decltype(lengthCompare) Func2; // 没有括号
void useBigger(const std::string&s1, const std::string &s2,Func2);

void chapter6_7()
{
    pf = lengthCompare;
    pf = &lengthCompare;
    bool b1 = pf("hello", "goodbye");
    bool b2 = (*pf)("hello", "goodbye");
    bool b3 = lengthCompare("hello", "goodbye");
    std::cout<< b1 << b2 << b3 << std::endl;

    // function
    using F = int(int*, int);
    // pointer of function
    using PF = int(*)(int*,int);
    PF f1(int);
    F *f2(int);
    auto f1(int) -> int (*)(int*, int); // 尾置返回类型

    // 简介写法获取lengthCompare的返回值类型
    decltype(lengthCompare) *getFcn(const std::string&);
}

int main(int argc, char* argv[])
{
    //chapter6_1();
    //chapter6_2();
    //chapter6_3();
    //chapter6_4();
    //chapter6_5();
    chapter6_7();

    for(int i = 0; i < argc; ++i)
        std::cout<< fmt::format("argv:[{}]{}\n", i, argv[i]);

    return 0;
}

