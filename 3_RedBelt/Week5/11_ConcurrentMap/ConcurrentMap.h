#ifndef TASK_10_CONCURRENTMAP_H
#define TASK_10_CONCURRENTMAP_H

#include <mutex>
#include <map>
#include <vector>

template<typename K, typename V>
class ConcurrentMap {
public:
    static_assert(is_integral_v<K>, "ConcurrentMap supports only integer keys");

    struct Access {
        std::lock_guard<std::mutex> lg;
        V &ref_to_value;
    };

    explicit ConcurrentMap(size_t bucket_count) : size(bucket_count), data(bucket_count){
        mtxs.reserve(bucket_count);
        for(int i = 0; i < bucket_count; ++i){
            mtxs.push_back(new mutex);
        }
    }

    Access operator[](const K &key) {
        auto index = key % size;
        return {std::lock_guard<mutex>(*mtxs[index]), data[index][key]};

    }

    map<K, V> BuildOrdinaryMap() {
        std::lock_guard<mutex> lg(mtx);
        std::map<K, V> res;
        for(const auto& item : data){
            res.insert(item.begin(), item.end());
        }
        return res;
    }

    ~ConcurrentMap(){
        for(auto& item : mtxs){
            delete item;
        }
    }

private:
    size_t size;

    std::vector<std::map<K, V>> data;
    std::vector<mutex *> mtxs;
    std::mutex mtx;

};

#endif //TASK_10_CONCURRENTMAP_H
