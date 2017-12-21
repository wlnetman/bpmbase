#ifndef RANGE_H
#define RANGE_H

namespace detail_range {

template <typename T>
detail_range::impl<T> range(T end)
{
    return { {}, end, 1};
}

template <typename T>
detail_range::impl<T> range(T begin, T end)
{
    return { begin, end, 1 };
}

template <typename T, typename U>
auto range(T begin, T end, U step)
    -> detail_range::impl<decltype(begin + step)>
{
    using r_t = detail_range::impl<decltype(begin+step)>;
    return r_t(begin, end, step);
}

}


#endif // RANGE_H
