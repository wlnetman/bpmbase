#include <iostream>
#include <stdexcept>

#include <vector>
#include <string>
#include "fmt/format.h"
#include "sales_item.h"

//--------------------------------
// c++11 primer v5
//     chapter 5 statement
// while, for , do while
// if ,else if, else
// switch , continue ,break
// goto ,try catch, throw, return
// 2017-11-26 @wlnetman@gmail.com
//--------------------------------

void chapter5_1_5()
{
    // 语句和作用域. if语句
    int grade = 0;

repeat:
    std::cout << "Input grade" << std::endl;
    std::cin >> grade;
    const std::vector<std::string> scores{"F","E","D","C","B","A"};
    std::string lettergreade;
    if(grade > 100)
        std::cout << "Error grade:\n" << std::endl;
    else if(grade < 60)
        lettergreade = scores[0];
    else {
        lettergreade = scores[(grade - 50)/10];
        if(grade != 100)
            if( grade % 10 > 7)
                lettergreade += "+";
            else if (grade % 10 < 3)
                lettergreade += '-';
    }
    std::cout << fmt::format("grade is:{}[{}]\n", grade, lettergreade);
    goto repeat;
}

void chaptert5_3()
{
    unsigned aCnt = 0, eCnt = 0, iCnt = 0, oCnt = 0, uCnt = 0;
    char ch;
    // Windows Dos下面Ctrl+D然后Ctrl+Z
    while ( std::cin >> ch) {
        switch (ch) {
            case 'a':
                ++aCnt;
                break; // 切记Switch的条件后加Break!!!
            case 'e':
                ++eCnt;
                break;
            case 'i':
                ++iCnt;
                break;
            case 'o':
                ++oCnt;
                break;
            case 'u':
                ++uCnt;
                break;
            default:
                break;
        }
    }
    std::cout << "Number of vowei a: \t" << aCnt <<'\n'
              << "Number of vowei e: \t" << eCnt <<'\n'
              << "Number of vowei i: \t" << iCnt <<'\n'
              << "Number of vowei o: \t" << oCnt <<'\n'
              << "Number of vowei u: \t" << uCnt <<'\n';
}

std::string vecToString(std::vector<int>& v)
{
    std::string retVal{"["};
    for(decltype(v.size()) i = 0, sz = v.size(); i != sz; ++i)
        retVal += fmt::format("[{}] ", v[i]);
    retVal += "]\n";
    return retVal;
}

void chaptert5_4()
{
    // for 语句
    std::string s{"WangDashi is good person!"};
    for(decltype(s.size()) index = 0;
        index != s.size() && !isspace(s[index]); ++index)
        s[index] = toupper(s[index]);
    std::cout << s <<std::endl;

    std::vector<int> v{1,2,3,4,5,6,7,8,9,0};
    std::cout << vecToString(v) << std::endl;
    for(decltype(v.size()) i = 0, sz = v.size(); i != sz; ++i)
        v.push_back(v[i]);
    std::cout << vecToString(v) << std::endl;

    std::string rsp;
    do {
        std::cout << "Input two value:\n";
        int val1,val2;
        std::cin >> val1 >> val2;
        std::cout << "The Val1 " << val1 << " and " << val2
                  << " sum = " << val1 + val2 << "\n\n"
                  << "Continue? yes or no?" << std::endl;
        std::cin >> rsp;
    } while( !rsp.empty() && rsp[0] != 'n');

}

void chaptert5_6()
{
    Sales_item item1,item2;

    while( std::cin >> item1 >> item2) {
        try{
            // 异常处理头文件找不到
            if(item1.isbn() != item2.isbn())
                //throw exception("Data must refer to same ISBN");
            {}

            std::cout << item1 + item2 << std::endl;
        } catch (int i ) {
            std::cout << "err.what()"
                      << "nTry Again? Enter y or n" << std::endl;
            char c;
            std::cin >> c;
            if( !std::cin || c == 'n')
                break;
        }
    }
}

int main(int argc, char* argv)
{
    //chapter5_1_5();
    //chaptert5_3();
    //chaptert5_4();
    chaptert5_6();
    return 0;
}
