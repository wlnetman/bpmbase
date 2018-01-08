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
    using pvector = std::shared_ptr<std::vector<T>>;

public:
    SimpleQueue() : max_size_(10000) { }
    ~SimpleQueue() { table_.clear(); }

    void set_maxsize(int maxsize)
    {
        max_size_ = maxsize;
    }

    void put(const std::string& key, T& item)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        auto it = table_.find(key);
        if( it!= table_.end() ){
            it->second->push_back(item);
            //LOG(INFO)<< "push_back [" << key << "] [count:" << it->second->size() << "]";
        } else {
            // 每个key每天分配 1000 个 TickData 足够了
            pvector p = std::make_shared<std::vector<T>>();
            p->reserve(max_size_);
            p->push_back(item);
            table_[key] = p;
            LOG(INFO)<< "new key : " << key;
        }
    }

    void notify_get()
    {
        std::lock_guard<std::mutex> lock(mutex_);

        if(table_.size() >= 12)
            notempty_.notify_one();
    }

    void get(std::vector<T>& item)
    {
        std::unique_lock<std::mutex> lock(mutex_);

        //TODO: table_ 始终有数据在里面, 不能阻塞到主力合约tick开始计算
        notempty_.wait(lock, [this] { return !table_.empty(); } );

        for( const auto & k : table_ ){
            //LOG(INFO)<< "key:" << k.first << " size:" << (k.second)->size() << "\n";
            item.push_back( (k.second)->back() );
        }
    }

private:
    int max_size_;
    std::mutex      mutex_;
    std::map<std::string, pvector> table_;
    std::condition_variable notempty_;
};

#endif // SIMPLEQUEUE_H
