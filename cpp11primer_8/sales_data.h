#ifndef SALES_ITEM_H
#define SALES_ITEM_H

#include <string>

class Sales_data{
    // 友元
friend Sales_data add(const Sales_data &,const Sales_data &);
friend std::istream &read(std::istream&, Sales_data &);
friend std::ostream &print(std::ostream&, const Sales_data &);

public:
    // 构造函数
    Sales_data() = default;
    //Sales_data(const std::string &s = ""):bookNo(s){}
    Sales_data(const std::string &s, unsigned n, double p):
        bookNo(s), units_sold(n), revenue(p*n) { }
    //Sales_data(std::istream &);
    // 委托构造函数
    Sales_data(const std::string s):Sales_data("", 0, 0) {}
    //Sales_data(std::string s):Sales_data(s, 0, 0) {}
    Sales_data(std::istream &is):Sales_data()
                                    { read(is, *this);}

    std::string isbn() const {return bookNo;}
    Sales_data &combine(const Sales_data &);

public:
    double avg_price() const
        { return units_sold ? revenue / units_sold : 0; }

    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};

Sales_data add(const Sales_data &,const Sales_data &);
std::istream &read(std::istream&, Sales_data &);
std::ostream &print(std::ostream&, const Sales_data &);

#endif // SALES_ITEM_H
