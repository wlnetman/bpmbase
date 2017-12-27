#ifndef TIMER_H
#define TIMER_H

#include <chrono>
using namespace std;
using namespace std::chrono;

class Timer
{
public:
        Timer(): m_begin(high_resolution_clock::now()){}
        void reset() { m_begin = high_resolution_clock::now(); }
        
        // 默认输出毫秒
        template <typename Duration = milliseconds>
        int64_t elapsed() const
        {
            return duration_cast<Duration>(high_resolution_clock::now() -
                    m_begin).count();
        }
        
        // weimioa
        int64_t elapsed_micro() const
        {
            return elapsed<microseconds>();
        }
        
        // namiao
        int64_t elapsed_nano() const
        {
            return elapsed<nanoseconds>();
        }
        
        // miao
        int64_t elapsed_seconds() const
        {
            return elapsed<seconds>();
        }
        
        // fen
        int64_t elapsed_minutes() const
        {
            return elapsed<minutes>();
        }
        
        // hour
        int64_t elapsed_hours() const
        {
            return elapsed<hours>();
        }
        
private:
        time_point<high_resolution_clock> m_begin;
};

#endif // TIMER_H
