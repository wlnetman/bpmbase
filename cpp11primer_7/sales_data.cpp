#include "sales_data.h"

//double Sales_data::avg_price() const{
//    if(units_sold)
//        return revenue / units_sold;
//    else
//        return 0;
//}

Sales_data& Sales_data::combine(const Sales_data &rhs)
{
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
}

std::istream &read(std::istream &in, Sales_data &item)
{
    double price = 0;
    in >> item.bookNo >> item.units_sold >> price;
    item.revenue = price * item.units_sold;
    return in;
}

std::ostream &print(std::ostream &out, const Sales_data& item)
{
    out << item.bookNo << " " << item.units_sold << " "
        << item.revenue << " " << item.avg_price();
    return out;
}

Sales_data add(const Sales_data &lhs, const Sales_data &rhs)
{
    Sales_data sum = lhs;
    sum.combine(rhs);
    return sum;
}
