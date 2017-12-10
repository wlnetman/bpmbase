#ifndef SALES_DATA_H
#define SALES_DATA_H

#include <string>
#include <iostream>

class Sales_data
{
public:
    Sales_data() = default;
    ~Sales_data();
    Sales_data(const Sales_data&);
    Sales_data& operator=(const Sales_data &rhs);

private:
    // private拷贝控制, 无法拷贝对象
    //PrivateCopy() = default;

    std::string bookNo;
    int units_sold = 0;
    double revenue = 0.0;
};

#endif // SALES_DATA_H
