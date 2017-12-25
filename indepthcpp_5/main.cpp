#include <thread>
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <list>
#include <atomic>
#include <future>
#include <utility>
#include "simplesyncqueue.h"

void func_argc(int i, double d, std::string &name)
{
    std::cout<< "Func " << i<<  d << name << std::endl;
}

void func()
{
    std::cout<< "Func" <<std::endl;
}

void f_sleep()
{
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout<< "Time out" << std::endl;
}

std::vector<std::thread> g_list;
std::vector<std::shared_ptr<std::thread>> g_list2;
void CreateThread()
{
    std::thread t(func);
    g_list.push_back(std::move(t));
    g_list2.push_back(std::make_shared<std::thread>(func));
}

void chapter5_1()
{
    {
        std::string name = "netman";
        std::thread t(func_argc, 1, 1, name);
        std::thread t2(std::move(t));
        t.join();
        t2.join();
    }
    {
        std::thread t3([](int a,double b){std::cout<< a<< b;}, 1, 2);
        t3.join();
    }
    {
        CreateThread();
        for(auto& thread : g_list)
            thread.join();
        for(auto &thread : g_list2)
            thread->join();
    }

    // 线程信息
    {
        std::thread t(func);
        std::cout<< t.get_id() << std::endl;
        std::cout<< std::thread::hardware_concurrency() << std::endl;
    }

    {
        std::thread t(f_sleep);
        t.join();
    }
}

std::mutex g_lock;
void func2()
{
    g_lock.lock();
    std::cout<< "entered thread " << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout<< "leving thread " << std::this_thread::get_id() << std::endl;
    g_lock.unlock();
}

void func_auto_lock()
{
    std::lock_guard< std::mutex> locker(g_lock);
    std::cout<< "entry thread:" << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout<< "levint thread:" << std::this_thread::get_id() << std::endl;
}

void chapter5_2()
{
    std::thread t1(func2);
    std::thread t2(func2);
    std::thread t3(func2);
    t1.join();
    t2.join();
    t3.join();

    func_auto_lock();
}

struct Complex{
    std::recursive_mutex mutex;
    int i;
    Complex():i(0){}
    void mul(int x){
        std::lock_guard<std::recursive_mutex> lock(mutex);
        i *= x;
    }
    void div(int x){
        std::lock_guard<std::recursive_mutex> lock(mutex);
        i /= x;
    }
    void both(int x,int y){
        std::lock_guard<std::recursive_mutex> lock(mutex);
        mul(x);
        div(y);
    }

};

void chapter5_3()
{
    Complex complex;
    complex.both(32, 23);
}

std::timed_mutex mutex_time;
void work()
{
    std::chrono::milliseconds timeout(100);

    while ( true ) {
        if(mutex_time.try_lock_for(timeout)){
            std::cout<< std::this_thread::get_id() << ": do work with the mutex"
                     << std::endl;
            std::chrono::milliseconds sleepDuration(250);
            std::this_thread::sleep_for(sleepDuration);
            mutex_time.unlock();
            std::this_thread::sleep_for(sleepDuration);
        } else {
            std::cout<< std::this_thread::get_id() << ": do word without mutex"
                     << std::endl;
            std::chrono::milliseconds sleepDuration(100);
            std::this_thread::sleep_for(sleepDuration);
        }
    }
}

void chapter5_4()
{
    // 带超时互斥量
    std::thread t1(work);
    std::thread t2(work);
    t1.join();
    t2.join();

    // 条件变量跟互斥量结合使用
    SimpleSyncQueue<int> ssq;
}

struct Counter
{
    std::atomic<int> value;

    void increment()
    {
        ++value;
    }

    void decrement()
    {
        --value;
    }

    int get()
    {
        return value.load();
    }
};

std::once_flag flag;
void do_once()
{
    std::call_once(flag, [](){ std::cout<< "Call once" << std::endl; });
}

void chapter5_5()
{
    Counter c;
    std::cout<< c.get() << std::endl;
    c.increment();
    std::cout<< c.get() << std::endl;
    c.decrement();
    std::cout<< c.get() << std::endl;
    c.increment();
    std::cout<< c.get() << std::endl;

    std::thread t1(do_once);
    std::thread t2(do_once);
    std::thread t3(do_once);
    t1.join();
    t2.join();
    t3.join();
}

void std_pack_task()
{
    std::packaged_task<int()> task([](){ return 7; });
    std::thread t1(std::ref(task));
    std::future<int> f1 = task.get_future();
    auto r1 = f1.get();
}

// promise
int func_int(int x)
{
    return x + 2;
}

void package_promise()
{
    std::packaged_task<int(int)> tsk (func_int);
    std::future<int> fut = tsk.get_future();

    std::thread(std::move(tsk), 2).detach();

    int value = fut.get();
    std::cout<< "Thre result is:" << value << std::endl;

    // shared_vector问题
    std::vector<std::shared_future<int>> v;
    auto f = std::async(std::launch::async,
                        [](int a, int b){ return a+b; },
                        2,
                        3);
    // vc编译不过，类型不匹配
    // cannot convert from 'std::future<_Ret>' to 'std::shared_future<_Ty>'
    v.push_back(std::async(std::launch::async,
                           [](int a, int b){ return a+b; },
                           2,
                           3));
    std::cout<< "Thre shared future result is " << v[0].get() << std::endl;

}

void chapter5_6()
{
    {
        std::future<int> future;
        std::future_status status;
        do{
            status = future.wait_for(std::chrono::seconds(1));
            if(status == std::future_status::deferred)
                std::cout<< "Deferred" << std::endl;
            else if (status == std::future_status::ready)
                std::cout<< "ready" << std::endl;
            else if (status == std::future_status::timeout)
                std::cout<< "Timeout" << std::endl;
        } while( status != std::future_status::ready);
    }

    std_pack_task();

    package_promise();
}

void chapter5_7()
{
    std::future<int> f1 = std::async(std::launch::async, [](){
        return 8;
    });

    std::cout<< f1.get() << std::endl;

    std::future<void> f2 = std::async(std::launch::async, [](){
        std::cout<< 8 << std::endl;
    });

    f2.wait();

    std::future<int> future = std::async(std::launch::async, [](){
        std::this_thread::sleep_for(std::chrono::seconds(3));
        return 9;
    });

    std::cout<< "Wait ing ..." << std::endl;

    std::future_status status;
    do{
        status = future.wait_for(std::chrono::seconds(1));
        if(status == std::future_status::deferred)
            std::cout<< "Deferred" << std::endl;
        else if (status == std::future_status::ready)
            std::cout<< "ready" << std::endl;
        else if (status == std::future_status::timeout)
            std::cout<< "Timeout" << std::endl;
    } while( status != std::future_status::ready);

    std::cout<< "result is " << future.get() << std::endl;

}

int main(int argc, char* argv[])
{
    //chapter5_1();
    //chapter5_2();
    //chapter5_3();
    //chapter5_4();
    //chapter5_5();
    //chapter5_6();
    chapter5_7();
    return 0;
}
