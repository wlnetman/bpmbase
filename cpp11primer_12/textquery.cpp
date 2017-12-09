#include "textquery.h"
#include <vector>
#include <string>
#include <set>
#include <map>
#include <iostream>
#include <sstream>

#include "textquery.h"
#include "queryresult.h"

TextQuery::TextQuery(std::ifstream &is): file(new std::vector<std::string>)
{
    std::string text;
    while ( std::getline(std::cin, text)) {
        file->push_back(text);
        int n = file->size() - 1;
        std::istringstream line(text);
        std::string word;
        while(line >> word){
            auto &lines = wm[word];
            if(!lines)
                lines.reset(new std::set<line_no>);
            lines->insert(n);
        }
    }
}

QueryResult TextQuery::query(const std::string& sought) const
{
    static std::shared_ptr<std::set<line_no>> nodata(new std::set<line_no>);
    auto loc = wm.find(sought);
    if(loc == wm.end())
        return QueryResult(sought, nodata, file);
    else
        return QueryResult(sought, loc->second, file);
}

