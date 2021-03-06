#ifndef TEXTQUERY_H
#define TEXTQUERY_H

#include <vector>
#include <string>
#include <set>
#include <map>
#include <iostream>
#include <memory>

class QueryResult;
class TextQuery
{
    using line_no = std::vector<std::string>::size_type;
public:
    TextQuery(std::ifstream&);
    QueryResult query(const std::string&) const;

private:
    std::shared_ptr<std::vector<std::string>> file;
    std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;
};

#endif // TEXTQUERY_H
