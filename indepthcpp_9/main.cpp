#include <iostream>
#include <chrono>
#include "threadpool.hpp"

void TestThdPool()
{
    ThreadPool pool;
    
    std::thread thd1( [&pool] {
        for(int i = 0; i < 10; ++i)
        {
            auto thdId = this_thread::get_id();
            pool.AddTask( [ thdId ] {
                std::cout<< "同步层线程1的线程ID: " 
                         << thdId << std::endl;
            });
        }
    });

    std::thread thd2([&pool] {
        for(int i = 0; i < 10; ++i)
        {
            auto thdId = this_thread::get_id();
            pool.AddTask( [thdId] {
                std::cout<< "同步层线程2的线程id："
                << thdId << std::endl;
            });
        }
    });

    this_thread::sleep_for(std::chrono::seconds(2));
    getchar();
    pool.Stop();
    thd1.join();
    thd2.join();
}

int main(int argc, char* argv[])
{
    TestThdPool();
    return 0;
}
