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

#endif // QUERYRESULT_H
