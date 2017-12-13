#ifndef SALES_DATA_H
#define SALES_DATA_H

#include <string>
#include <iostream>

class Sales_data;
std::ostream& operator << (std::ostream &os, const Sales_data &itme);

class Sales_data
{
public:
    Sales_data() = default;
    Sales_data(const std::string &s): bookNo(s) {}
    Sales_data(const std::string &s, unsigned n, double p):
            bookNo(s), units_sold(n), revenue(p){}
    Sales_data(std::string &s):Sales_data(s, 0, 0) {}

    Sales_data::Sales_data(const Sales_data &oig):
                                bookNo(oig.bookNo),
                                units_sold(oig.units_sold),
                                revenue(oig.revenue) {}

    ~Sales_data();

    Sales_data& operator=(const Sales_data &rhs);

    //https://stackoverflow.com/questions/236801/should-operator-be-implemented-as-a-friend-or-as-a-member-function
    // 加friend
    friend std::ostream& operator << (std::ostream &os, const Sales_data &itme);
    friend std::istream& operator >> (std::istream &is, Sales_data &item);

    Sales_data& operator+=(const Sales_data&);
    friend Sales_data operator+(const Sales_data &lhs, const Sales_data& rhs);

    friend bool operator==(const Sales_data &lhs, const Sales_data& rhs);
    friend bool operator!=(const Sales_data &lhs, const Sales_data& rhs);

    std::string isbn() const { return bookNo; }
private:
    // private拷贝控制, 无法拷贝对象
    //PrivateCopy() = default;

    double avg_price() const;
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};

std::ostream &operator<<(std::ostream&, const Sales_data&);
std::istream& operator >> (std::istream &is, Sales_data &item);
bool operator==(const Sales_data &lhs, const Sales_data& rhs);
bool operator!=(const Sales_data &lhs, const Sales_data& rhs);
Sales_data operator+(const Sales_data &lhs, const Sales_data& rhs);


#endif // SALES_DATA_H
