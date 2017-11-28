#include <iostream>
#include <fstream>
#include <sstream>
#include "sales_data.h"
#include <vector>

void process_input(std::istream &cin)
{
    int ival;
    cin >> ival;
}

void chapter8_1()
{
    std::string text{"WangDaShi"};
    std::ofstream out1(text);
    out1 << "Text" << std::endl << text;
    //std::cout<< text << std::endl;

    int ival;
    while(std::cin >> ival){
        std::cout<< ival << std::endl;
    }

    auto old_state = std::cin.rdstate();
    std::cin.clear();
    std::cin.clear(std::cin.rdstate() & ~std::cin.failbit & ~std::cin.badbit);
    process_input(std::cin);
    std::cin.setstate(old_state);

    std::cin.tie(&std::cout);
    std::ostream *old_tie = std::cin.tie(nullptr);
    std::cin.tie(&std::cerr);
    std::cin.tie(old_tie);
}

void coutFileWithSteam(const char *filename)
{
    // 显式文本
    std::cout<< "File: "<< filename << std::endl;
    std::ifstream show(filename);
    std::string line;
    while( getline(show, line))
        std::cout<< line << std::endl;
}

void chapter8_2(char* argv[])
{
    // tie函数关联 输出/输入 流, 来自网络
    std::ostream *prevstr;
    std::ofstream ofs;
    ofs.open("test.txt");
    std::cout << "tie example:\n";
    // 默认空参数返回当前绑定的流指针(std默认绑定的是std::cout
    *std::cin.tie() << "This is inserted into cout";
    // 关联输入到文件,此时输入不会显示到cmd命令行,而是ofs
    prevstr = std::cin.tie(&ofs);
    *std::cin.tie() << "This is inserted into the file";
    std::cin.tie(prevstr);
    std::cout<< std::endl;
    ofs.close();

    std::ifstream input(argv[1]);
    std::ofstream output(argv[2]);   // 默认会截断文件
    Sales_data total;
    if( read(input, total)) {
        Sales_data trans;
        while (read(input, trans) ){
            if( total.isbn() == trans.isbn() ){
                total.combine(trans);
            } else {
                print(output, total) << std::endl;
                total = trans;
            }
        }
        print(output, total) << std::endl;
    } else
        std::cerr << "No Data?!" << std::endl;

    coutFileWithSteam(argv[1]);
    coutFileWithSteam(argv[2]);
}

struct PersonInfo{
    std::string name;
    std::vector<std::string> phones;
};

bool valid(const std::string &phone)
{
    if( phone.size()>5 && phone[0] == '1')
        return true;
    else
        return false;
}

std::string format(const std::string &phone)
{
    std::string tmp;
    tmp = "[" + phone;
    tmp += "]";
    return tmp;
}

void chapter8_3()
{
    std::string line,word;
    std::vector<PersonInfo> people;
    while(getline( std::cin, line)){
        PersonInfo info;
        std::istringstream record(line);   // 记录绑定到line
        record >> info.name;
        while ( record >> word)
            info.phones.push_back(word);
        people.push_back(info);
    }

    for( const auto &entry : people){
        std::ostringstream formatted, badNums;
        for(const auto &nums : entry.phones){
            if( !valid(nums)) {
                badNums << " " << nums;
            } else {
                formatted << " " << format(nums);
            }
        }
        if(badNums.str().empty())
            std::cout<< entry.name << " "
                     << formatted.str() << std::endl;
        else
            std::cerr<< "input error:" << entry.name
                     << "invaild number(s) " << badNums.str()
                     << std::endl;
    }
}

int main(int argc, char* argv[])
{
    if(argc < 3){
        std::cout<< "Usage: cpp11primer_8.exe data.txt data_count.txt"
                 << std::endl;
        return 0;
    }
    //chapter8_1();
    //chapter8_2(argv);
    chapter8_3();
    return 0;
}
