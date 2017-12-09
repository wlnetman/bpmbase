#ifndef STRBLOB_H
#define STRBLOB_H

#include <string>
#include <memory>
#include <vector>

class StrBlobPtr;
class StrBlob{
    friend class StrBlobPtr;
    StrBlobPtr begin();
    StrBlobPtr end();

public:
    typedef std::vector<std::string>::size_type size_type;
    StrBlob();
    StrBlob(std::initializer_list<std::string> il);
    size_type size() const { return data->size();}
    bool empty() const { return data->empty();}
    void push_back(const std::string &t) { data->push_back(t);}
    void pop_back();

    std::string& front();
    std::string& back();

private:
    std::shared_ptr<std::vector<std::string>> data;
    bool check(size_type i, const std::string &msg) const;
};


#endif // STRBLOB_H
