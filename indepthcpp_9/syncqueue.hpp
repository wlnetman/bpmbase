#ifndef SYNCQUEUE
#define SYNCQUEUE

#include <list>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <iostream>
using namespace std;

template <typename T>
class SyncQueue
{
public:
    SyncQueue(int maxSize) :
        m_maxSize(maxSize),
        m_needStop(false)
        {}

    void Put(const T&x)
    {
        Add(x);
    }
    
    void Put( T&&x )
    {
        Add( std::forward<T>(x) );
    }
    
    void Take(std::list<T> &list )
    {
        std::unique_lock<std::mutex> locker(m_mutex);
        m_notEmpty.wait(locker, [this]{ return m_needStop || NotEmpty(); });
        
        if( m_needStop)
            return;
        list = std::move(m_queue);
        m_notFull.notify_one();
    }
    
    void Take(T& t)
    {
        std::unique_lock<std::mutex> locker(m_muter);
        m_notEmpty.wait(locker, [this] {  return m_needStop || NotEmpty(); });
        
        if( m_needStop )
            return;
        t = m_queue.front();
        m_queue.pop_front();
        m_notFull.notify_one();
    }
    
    void Stop()
    {
        {
            std::lock_guard<std::mutex> locker(m_mutex);
            m_needStop = true;
        }
        m_notFull.notify_all();
        m_notEmpty.notify_all();
    }
    
    bool Empty()
    {
        std::lock_gurad<std::mutex> locker(m_mutex);
        return m_queue.emtpy();
    }
    
    bool Full()
    {
        return m_queue.size() == m_maxSize;
    }
    
    size_t Size()
    {
        std::lock_guard<std::mutex> locker(m_mutex);
        return m_queue.size();
    }
    
    int Count()
    {
        return m_queue.size();
    }

private:
    bool NotFull() const
    {
        bool full = m_queue.size() >= m_maxSize;
        if(full)
        {
            std::cout<< "队列满了 " << std::endl;
        }
        
        return !full;
    }
    
    bool NotEmpty() const
    {
        bool empty = m_queue.empty();
        if(empty)
        {
            std::cout<< "缓存区空了,需要等待.... 异步线程ID:"
                     << this_thread::get_id() << std::endl;       
        }
        return !empty;
    }
    
    template <typename F>
    void Add(F&&x)
    {
        std::unique_lock<std::mutex> locker(m_mutex);
        m_notFull.wait(locker, [this]{return m_needStop || NotFull(); });
        if(m_needStop)
            return;
        m_queue.push_back(std::forward<F>(x));
        m_notEmpty.notify_one();
    }

private:
    std::list<T> m_queue;
    std::mutex m_mutex;
    std::condition_variable m_notEmpty;
    std::condition_variable m_notFull;
    int m_maxSize;
    bool m_needStop;
};

#endif //SYNCQUEUE
