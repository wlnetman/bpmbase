#include <iostream>
#include <string>
#include "sales_data.h"
#include "screen.h"

//--------------------------------
// c++11 primer v5
//     chapter 7 class
// 类
//
//      2017-11-27 @wlnetman@gmail.com
//--------------------------------

void chapter7_1()
{
    Sales_data total;
    if(read(std::cin, total)){
        Sales_data trans;
        while(read(std::cin, trans)){
            if(total.isbn() == trans.isbn()){
                total.combine(trans);
            } else {
                print(std::cout, trans);
            }
        }
        print(std::cout, total) << std::endl;
    } else {
        std::cout << "No data?!" << std::endl;
    }
}

void chapter7_3()
{
    Screen myscreen(80,60,'*');
    char ch = myscreen.get();
    std::cout<< ch;
    ch = myscreen.get(0,0);
    std::cout<< ch << std::endl;

    Screen myScreen(5,3,' ');
    const Screen blank(5, 3, ' ');
    myScreen.set('#').display(std::cout);
    blank.display(std::cout);
}

void chapter7_4()
{
    Screen::pos ht = 24, wd = 80;
    Screen scr(ht, wd, ' ');
    Screen *p = &scr;
    char c = scr.get();
    c = p->get();
    std::cout<< c;
}

void chapter7_5()
{
    Sales_data item1("SB");
    print(std::cout, item1);
    Sales_data item2("ibsn", 2190, 22);
    print(std::cout, item2);
    Sales_data item3();
    //print(std::cout, item3); // Error
    Sales_data item4 = item1;
    print(std::cout, item4);
}

int main(int argc, char* argv[])
{
    //chapter7_1();
    //chapter7_3();
    //chapter7_4();
    chapter7_5();
    return 0;
}
