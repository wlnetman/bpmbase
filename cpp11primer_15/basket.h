#ifndef BASKET_H
#define BASKET_H
#include "quote.h"
#include <memory>
#include <iostream>
#include <set>

class Basket
{
public:
    Basket();
    void add_item(const std::shared_ptr<Quote> &sale)
            { items.insert(sale); }
    double total_receipt(std::ostream&) const;

    void add_item(const Quote& sale)
        { items.insert(std::shared_ptr<Quote>(sale.clone())); }
    void add_item(Quote&& sale)
        { items.insert(std::shared_ptr<Quote>(std::move(sale).clone())); }

private:
    static bool compare(const std::shared_ptr<Quote> &lhs,
                        const std::shared_ptr<Quote> &rhs)
    { return lhs->isbn() < rhs->isbn(); }
    std::multiset<std::shared_ptr<Quote>, decltype(compare)*>
        items{compare};
};

#endif // BASKET_H
