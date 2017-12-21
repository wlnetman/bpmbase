#include <iostream>
#include <vector>
#include <string>
#include "template_compile.h"

//--------------------------------
// c++11 primer v5
//     chapter 16 模范和泛型编程
//
//
//
//      2017-12-17 wlnetman@gmail.com
//--------------------------------


void chapter16_1()
{
    std::cout<< compare(1,0) << std::endl;
    std::vector<int> vec1{1,2,3}, vec2{4,5,6};
    std::cout<< compare(vec1, vec2) <<std::endl;

    //Blob<int> ia;
    //Blob<int> ia2 = { 0,1,2,3,4};

    //Blob<std::string> names{"Wang","DaSHI"};
    //Blob<double> prices;

}


int main()
{
    chapter16_1();
    return 0;
}
