#ifndef INC_4_CONCURRENTMAP2_CONCURRENTMAP_H
#define INC_4_CONCURRENTMAP2_CONCURRENTMAP_H

#include <mutex>
#include <type_traits>
#include <unordered_map>
#include <vector>


template<typename K, typename V, typename Hash = std::hash<K>>
class ConcurrentMap {
public:
    using MapType = std::unordered_map<K, V, Hash>;
private:
    Hash hasher;

    struct Bucket {
        MapType map;
        mutable std::mutex mtx;
    };

    size_t size;
    std::vector<Bucket> data;
public:
    struct WriteAccess : std::lock_guard<mutex> {
        V& ref_to_value;

        WriteAccess(const K& key, Bucket& bucket) :
                std::lock_guard<std::mutex>(bucket.mtx),
                ref_to_value(bucket.map[key]){}

    };

    struct ReadAccess : std::lock_guard<mutex> {
        const V& ref_to_value;

        ReadAccess(const K& key, const Bucket& bucket) :
                std::lock_guard<mutex>(bucket.mtx),
                ref_to_value(bucket.map.at(key)){}

    };

    explicit ConcurrentMap(size_t bucket_count) : size(bucket_count), data(bucket_count){}

    WriteAccess operator[](const K& key){
        auto index = Index(key);
        return {key, data[index]};
    }

    ReadAccess At(const K& key) const{
        auto index = Index(key);
        return {key, data[index]};
    }

    MapType BuildOrdinaryMap() const {
        MapType result;
        for (auto& map : data) {
            for (const auto& [key, value] : map.map) {
                result[key] = At(key).ref_to_value;
            }
        }
        return result;

    }

    bool Has(const K& key) const{
        auto index = Index(key);
        return data[index].map.count(key);
    }

private:
    size_t Index(const K& key) const {
        return hasher(key) % size;
    }
};


#endif //INC_4_CONCURRENTMAP2_CONCURRENTMAP_H
