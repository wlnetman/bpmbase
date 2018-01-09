#ifndef SIMPLEQUEUE_H
#define SIMPLEQUEUE_H

#include <condition_variable>
#include <map>
#include <vector>
#include <deque>
#include <mutex>
#include <typeinfo>

template <typename T>
class SimpleQueue
{
public:
    SimpleQueue() = default;
    ~SimpleQueue() { deque_.clear(); }

    void put(T& item)
    {
        std::lock_guard<std::mutex> lock(mutex_);

        deque_.push_back(item);
        notempty_.notify_one();
    }

    void get(T& item)
    {
        std::unique_lock<std::mutex> lock(mutex_);
        notempty_.wait(lock, [this] { return !deque_.empty(); } );

        item = deque_.front();
        deque_.pop_front();
    }

private:
    std::mutex              mutex_;
    std::deque<T>           deque_;
    std::condition_variable notempty_;
};

#endif // SIMPLEQUEUE_H
