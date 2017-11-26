#ifndef SALES_ITEM_H
#define SALES_ITEM_H

#include <string>
#include <iostream>

class Sales_item
{
public:
    std::string isbn() const {
        return isbn_;
    }

    friend std::ostream& operator<<(std::ostream& os, const Sales_item &item)
    {
        std::string tmp;
        tmp = item.isbn();
        os << tmp.c_str() << " "
            << item.count_ << " "
            << item.sum_ << " "
            << item.avg_ << std::endl;
        return os;
    }

    friend std::istream &operator>>(std::istream &is, Sales_item &item)
    {
        is >> item.isbn_ >> item.count_ >> item.avg_;
        item.sum_ = item.count_ * item.avg_;
        return is;
    }

    friend Sales_item operator+(const Sales_item& item1,const Sales_item& item2)
    {
        Sales_item result;
        if( item1.isbn() == item2.isbn() )
        {
            result.setIsbn(item1.isbn_);
            result.count_ = item1.count_ + item2.count_;
            result.sum_ = item1.sum_ + item2.sum_;
            result.avg_ = result.sum_ / result.count_;
        } else {
            std::cout << "cannot add to diff isbn" <<std::endl;
        }
        return result;
    }

    friend Sales_item operator+=(const Sales_item& item1,const Sales_item& item2)
    {
        Sales_item result;
        result = item1 + item2;
        return result;
    }

    Sales_item operator=(const Sales_item& item)
    {
        Sales_item result;
        result.setIsbn(item.isbn());
        result.count_ = item.count_;
        result.avg_ = item.avg_;
        result.sum_ = result.count_ * result.avg_;
        return result;
    }

    int count_;
    double avg_;
    int sum_;

    void setIsbn(std::string name)
    {
        isbn_ = name;
    }
private:
    std::string isbn_;
};
#endif // SALES_ITEM_H
