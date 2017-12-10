#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <vector>
#include <list>
#include <new>

#include "sales_data.h"
#include "hasptr.h"

//--------------------------------
// c++11 primer v5
//     chapter 13  拷贝控制
//
//
//
//      2017 -12-11 wlnetman@gmail.com
//--------------------------------

//阻止拷贝
struct NoCopy{
    NoCopy() = delete;
};

// 析构函数不能使delete
struct NoDelete{
    ~NoDelete() = delete;
};


void chapter13_1()
{
    Sales_data trans, accm;
    trans = accm;

    {
        Sales_data *p = new Sales_data;
        auto p2 = std::shared_ptr<Sales_data>();
        Sales_data item(*p);
        std::vector<Sales_data> vec;
        //vec.push_back(*p2); // 未初始化会崩溃
        delete p;
    }
}

void chapter13_2()
{
    HasPtr lhs("Dashi");
    HasPtr rhs("Hege");
    using std::swap;
    swap(lhs, rhs);
}

int main(int argc,char* argv[])
{
    //chapter13_1();
    chapter13_2();
    return 0;
}
