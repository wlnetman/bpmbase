#ifndef QUERYRESULT_H
#define QUERYRESULT_H

#include <vector>
#include <string>
#include <set>
#include <map>
#include <iostream>
#include <memory>

#include "textquery.h"

class TextQuery;
class QueryResult
{
    friend class TextQuery;
    // TODO: BUG
    using line_no = std::vector<std::string>::size_type;
    friend std::ostream& print(std::ostream&, const QueryResult& );
public:
    QueryResult::QueryResult(std::string s,
                             std::shared_ptr<std::set<line_no>> p,
                             std::shared_ptr<std::vector<std::string>> f):
        sought(s), lines(p), file(f){}

    std::string sought;
    std::shared_ptr<std::set<line_no>> lines;
    std::shared_ptr<std::vector<std::string>> file;
};

inline
std::string make_plural(size_t ctr,const std::string &word, const std::string &ending)
{
    return (ctr==1) ? word : word+ending;
    //make_plural(wc, "word ", "s ")当输入中文本中
    //word数大于一是在word后加s，为words为word的复数！
}

inline
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

#endif // QUERYRESULT_H
