#include <iostream>
#include <string>
#include <chrono>
#include <typeinfo>
#include <ctime>
#include <iomanip>
#include <codecvt>
#include "timer.h"


/*
    深入应用c++11
    chapter6 使用c++11中的便利的工具
    
    2017-12-27  by wlnetman@icloud.com
*/

void TestChrono()
{
    std::chrono::duration<double, std::ratio<9,7>> d1(3);
    std::chrono::duration<double, std::ratio<6,5>> d2(1);
    auto d3 = d2 - d1;
    std::cout << typeid(d3).name() << std::endl;
    std::cout << d3.count() << std::endl;
    std::cout<< std::chrono::duration_cast<std::chrono::minutes>( d3 ).count() << "minutes"
             << std::endl;
}

void chapter6_1()
{
    // ration 代表分子除以分母的分数值
    // duration 时间间隔
    // clock 时钟
    std::chrono::milliseconds ms{3};
    std::chrono::microseconds us = 2*ms;
    std::chrono::duration<double, std::ratio<1,30>> hz30{3.5};
    std::cout << "3ms duration has " << ms.count() << " ticks" << std::endl
              << "600 us duration has " << us.count() << "ticks" << std::endl;
    std::chrono::minutes t1(10);
    std::chrono::seconds t2(60);
    std::chrono::seconds t3 = t1 - t2;
    std::cout << t3.count() << " second" << std::endl;
    
    TestChrono();
    
    std::cout<< std::chrono::duration_cast<std::chrono::minutes>( t3 ).count() << "minutes"
             << std::endl;

    // time point 时间点
    {
        using namespace std::chrono;
        typedef duration<int, std::ratio<60*60*24>> day_type;
        time_point<system_clock, day_type> today =
        time_point_cast<day_type>(system_clock::now());

        std::cout<< today.time_since_epoch().count() << " days since ephoch"
                 << std::endl;
    }
    // time point 算数运算
    {
        using namespace std::chrono;
        system_clock::time_point now = system_clock::now();
        std::time_t last = system_clock::to_time_t(now - hours(24));
        std::time_t next = system_clock::to_time_t(now + hours(24));

        std::cout<< "One day ago,the time was "
                 << std::put_time(std::localtime(&last), "%F %T") << std::endl;
        std::cout<< "Next day, the time is "
                 << std::put_time(std::localtime(&next), "%F %T") << std::endl;
    }

    // clocks 系统时钟
    {
        std::chrono::system_clock::time_point t1 =
                std::chrono::system_clock::now();
        std::cout<< "Hello World!\n";
        std::chrono::system_clock::time_point t2 =
                std::chrono::system_clock::now();
        std::cout<< (t2 - t1).count() << " tick count" << std::endl;

        std::cout<<
        std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count()
                 <<" tick count microseconds"
                 << std::endl;

        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
        auto t = std::chrono::system_clock::to_time_t(now);
        std::cout<< "to_time_t " << typeid(t).name() << std::endl;
        std::cout<< std::put_time(std::localtime(&t), "%Y-%m-%d %X") << std::endl;
        std::cout<< std::put_time(std::localtime(&t), "%Y-%m-%d %H.%M.%S") << std::endl;

        auto now_t = std::chrono::system_clock::from_time_t(t);
        std::cout<< "frome_time_t " << typeid(now_t).name() << std::endl;
        std::cout<< now_t.time_since_epoch().count() << std::endl;
    }

    // timer
    {
        std::cout<< "Start Timer " << std::endl;
        Timer t;
        TestChrono();
        std::cout<< t.elapsed() << std::endl;
        std::cout<< t.elapsed_micro() << std::endl;
        std::cout<< t.elapsed_nano() << std::endl;
        std::cout<< t.elapsed_seconds() << std::endl;
        std::cout<< t.elapsed_minutes() << std::endl;
        std::cout<< t.elapsed_hours() << std::endl; 
    }
}

void chapter6_2()
{
    //字符串处理转换
    const char *str1 = "10";
    const char *str2 = "3.14159265358";
    const char *str3 = "322 3wit e";
    const char *str4 = "wwww 3333 333";

    int num1 = std::atoi(str1);
    int num2 = std::atoi(str2);
    int num3 = std::atoi(str3);
    int num4 = std::atoi(str4);

    std::cout<< num1 << " " << num2 << " "
             << num3 << " " << num4 << std::endl;
}

void chapter6_3()
{
    //std::wstring str = L"中国人";
    //std::wstring str = L"繁体字";
    std::wstring str = L"色·戒 【贾兰兰】";
    std::wstring_convert<std::codecvt<wchar_t, char, std::mbstate_t>>
        converter( new std::codecvt<wchar_t, char, std::mbstate_t>("CHS"));
    std::string narrowStr = converter.to_bytes(str);
    std::wstring wstr = converter.from_bytes(narrowStr);
    std::cout<< narrowStr << std::endl;

    std::wcout.imbue(std::locale("CHS"));
    std::wcout<< wstr << std::endl;
}

int main(int argc, char* argv[])
{
    //chapter6_1();
    //chapter6_2();
    chapter6_3();
    return 0;
}
