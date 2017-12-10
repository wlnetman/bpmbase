#include "sales_data.h"

Sales_data::Sales_data(const Sales_data &oig):
    bookNo(oig.bookNo),
    units_sold(oig.units_sold),
    revenue(oig.revenue)
{
}

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
