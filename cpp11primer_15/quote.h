#ifndef QUOTE_H
#define QUOTE_H

#include <string>
#include <iostream>

class Quote
{
public:
    Quote() = default;
    Quote(const std::string &book, double sales_price):
        bookNo(book), price(sales_price) { }
    std::string isbn() const { return bookNo; }
    virtual ~Quote() = default;
    virtual double net_price(std::size_t n) const;

    // 15.8隐藏指针
    virtual Quote* clone() const & { return new Quote(*this); }
    virtual Quote* clone() &&
        { return new Quote(std::move(*this)); }

private:
    std::string bookNo;
protected:
    double price = 0.0;
};

#endif // QUOTE_H
