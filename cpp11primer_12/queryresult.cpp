#include "queryresult.h"
#include "textquery.h"

std::string make_plural(size_t ctr,const std::string &word, const std::string &ending)
{
    return (ctr==1) ? word : word+ending;
    //make_plural(wc, "word ", "s ")当输入中文本中
    //word数大于一是在word后加s，为words为word的复数！
}

std::ostream& print(std::ostream & os, const QueryResult & qr)
{
    os << qr.sought << " occurs " << qr.lines->size() << " "
       << make_plural(qr.lines->size(), "time", "s") <<std::endl;
    for(auto num : *qr.lines)
    {
        os << "\t(line " << num + 1 << ") "
           << *(qr.file->begin() + num) << std::endl;
    }
    return os;
}
