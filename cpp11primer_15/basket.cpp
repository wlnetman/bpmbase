#include "basket.h"

double print_total2(std::ostream &os,
                   const Quote &item, std::size_t n)
{
    double ret = item.net_price(n);
    os << "ISBN: " << item.isbn()
       << " # sold: " << n << " total due:" << ret << std::endl;
    return ret;
}

Basket::Basket()
{

}

double Basket::total_receipt(std::ostream &os) const
{
    double sum = 0.0;
    for(auto iter = items.cbegin();
            iter != items.cend();
            iter = items.upper_bound(*iter))
    {
        sum += print_total2(os, **iter, items.count(*iter));
    }
    os<< "Total sale: " << sum << std::endl;
    return sum;
}
