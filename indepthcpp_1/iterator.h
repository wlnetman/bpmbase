#ifndef ITERATOR_H
#define ITERATOR_H

namespace detail_range{

// range iterator

template <typename T>
class iterator
{
public:
    using value_type = T;
    using size_type = size_t;

private:
    size_type        cursor_;
    const value_type step_;
    value_type       value_;

public:
    iterator(size_type cur_start, value_type begin_val, value_type step_val):
        cursor_(cur_start), step_(step_val), value_(begin_val)
    {
        value_ += (step_ * cursor_);
    }

    value_type operator*() const { return value_; }

    bool operator!=(const iterator& rhs) const
    {
        return (cursor_ != rhs.cursor_);
    }

    iterator& operator++(void)
    {
        value_ += step_;
        ++cursor_;
        return (*this);
    }
};

} // namespace detail range
#endif // ITERATOR_H
