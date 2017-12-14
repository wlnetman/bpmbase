#include "quote.h"


double Quote::net_price(std::size_t cnt) const
{
    return cnt * price;
}
