#ifndef TMP_H
#define TMP_H

#include <memory>
#include <vector>

template <typename T> inline int compare(const T &v1, const T &v2)
{
    if (v1 < v2) return -1;
    if (v2 < v1) return 1;
    return 0;
}

template <typename T> class Blob {
public:
    typedef T value_type;
    typedef typename std::vector<T>::size_type size_type;

    Blob();
    Blob(std::initializer_list<T> il);
    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    void push_back(const T &t) { data->push_back(t);}
    void push_back();
    T& back();
    T& operator[] (size_type i);
private:
    std::shared_ptr<std::vector<T>> data;
    void check(size_type i, const std::string &msg) const;
};

template <typename T> class BlobPtr {
public:
    BlobPtr():curr(0) {}
    BlobPtr(Blob<T> &a, size_t sz=0) :
        wptr(a.data),curr(sz){}
    T& operator*() const
    {
        auto p = check(curr, "dereference past end");
        return (*p)[curr];
    }
    BlobPtr& operator++(int);
    BlobPtr& operator--();
private:
    std::shared_ptr<std::vector<T>>
        check(std::size_t, const std::string&) const;
    std::weak_ptr<std::vector<T>> wptr;
    std::size_t curr;
};

template <typename T> BlobPtr<T>& BlobPtr<T>::operator++(int)
{
    BlobPtr ret = *this;
    ++*this;
    return ret;
}

#endif // TMP_H
