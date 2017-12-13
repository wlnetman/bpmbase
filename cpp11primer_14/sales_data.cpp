#include "sales_data.h"

Sales_data& Sales_data::operator=(const Sales_data &rhs)
{
    bookNo = rhs.bookNo;
    units_sold = rhs.units_sold;
    revenue = rhs.revenue;
    return *this;
}

Sales_data::~Sales_data()
{
    std::cout << "destructor Sales_data" << std::endl;
}

std::ostream& operator<<(std::ostream &os, const Sales_data &item)
{
    os << item.bookNo << " " << item.units_sold << " "
       << item.revenue ;
    return os;
}

std::istream& operator>>(std::istream &is, Sales_data &item)
{
    is >> item.revenue;
    if( !is )
        item.revenue = 0;
    return is;
}

Sales_data& Sales_data::operator+=(const Sales_data &rhs)
{
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
}

Sales_data operator+(const Sales_data &lhs, const Sales_data& rhs)
{
    Sales_data sum = lhs;
    sum += rhs;
    return sum;
}

bool operator==(const Sales_data &lhs, const Sales_data& rhs)
{
    return lhs.isbn() == rhs.isbn() &&
            lhs.units_sold == rhs.units_sold &&
            lhs.revenue == rhs.revenue;
}

bool operator!=(const Sales_data &lhs, const Sales_data& rhs)
{
    return !(lhs == rhs);
}

