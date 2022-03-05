#include "test_runner.h"
//#include "C:\Users\cobak\CLionProjects\red_belt\profiler\MyProfiler.h"
#include "profile.h"

#include <algorithm>
#include <future>
#include <map>
#include <vector>
#include <string>
#include <random>
#include <set>

using namespace std;

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

void RunConcurrentUpdates(ConcurrentMap<int, int> &cm, size_t thread_count, int key_count) {
    auto kernel = [&cm, key_count](int seed) {
        vector<int> updates(key_count);
        iota(begin(updates), end(updates), -key_count / 2);
        shuffle(begin(updates), end(updates), default_random_engine(seed));

        for (int i = 0; i < 2; ++i) {
            for (auto key: updates) {
                cm[key].ref_to_value++;
            }
        }
    };

    vector<future<void>> futures;
    for (size_t i = 0; i < thread_count; ++i) {
        futures.push_back(async(kernel, i));
    }
}

void TestConcurrentUpdate() {
    const size_t thread_count = 3;
    const size_t key_count = 50000;

    ConcurrentMap<int, int> cm(thread_count);
    RunConcurrentUpdates(cm, thread_count, key_count);

    const auto result = cm.BuildOrdinaryMap();
    ASSERT_EQUAL(result.size(), key_count);
    for (auto&[k, v]: result) {
        AssertEqual(v, 6, "Key = " + to_string(k));
    }
}

void TestReadAndWrite() {
    ConcurrentMap<size_t, string> cm(5);

    auto updater = [&cm] {
        for (size_t i = 0; i < 50000; ++i) {
            cm[i].ref_to_value += 'a';
        }
    };
    auto reader = [&cm] {
        vector<string> result(50000);
        for (size_t i = 0; i < result.size(); ++i) {
            result[i] = cm[i].ref_to_value;
        }
        return result;
    };

    auto u1 = async(updater);
    auto r1 = async(reader);
    auto u2 = async(updater);
    auto r2 = async(reader);

    u1.get();
    u2.get();

    for (auto f: {&r1, &r2}) {
        auto result = f->get();
        ASSERT(all_of(result.begin(), result.end(), [](const string &s) {
            return s.empty() || s == "a" || s == "aa";
        }));
    }
}

void TestSpeedup() {
    {
        ConcurrentMap<int, int> single_lock(1);

        LOG_DURATION("Single lock");
        RunConcurrentUpdates(single_lock, 4, 50000);
    }
    {
        ConcurrentMap<int, int> many_locks(10000);

        LOG_DURATION("100 locks");
        RunConcurrentUpdates(many_locks, 4, 50000);
    }
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestConcurrentUpdate);
    RUN_TEST(tr, TestReadAndWrite);
    RUN_TEST(tr, TestSpeedup);
}

/*
template<typename K, typename V>
class ConcurrentMap {
public:
    static_assert(is_integral_v<K>, "ConcurrentMap supports only integer keys");

    struct Access {
        std::lock_guard<std::mutex> lg;
        V &ref_to_value;
    };

    explicit ConcurrentMap(size_t bucket_count) : size(bucket_count),
                                                  curr_id(0) {
        mtxs.reserve(bucket_count);
        for (size_t i = 0; i < bucket_count; ++i) {
            mtxs.push_back(new mutex);
        }

        submaps.reserve(bucket_count - 1);

        for (size_t i = 0; i < bucket_count - 1; ++i) {
            submaps.push_back(map.end());
        }


    }

    Access operator[](const K &key) {
        return FindKey(key);
    }

    map<K, V> BuildOrdinaryMap() {

    }

private:
    using Iterator = typename std::map<K, V>::iterator;


    Access FindKey(const K &key) {
        auto it = map.emplace(key, V()).first;

        if (it == map.begin()) return {lock_guard<mutex>(*mtxs[0]), map[key]};


        for (curr_id = 0; curr_id < submaps.size(); ++curr_id) {

            if (submaps[curr_id] == map.end()) return AddIter(key, it);

            if (submaps[curr_id]->first > it->first) {

                if (curr_id == 0) {
                    auto dist1 = distance(it, submaps[curr_id]);
                    auto dist2 = distance(map.begin(), it);

                    if (dist1 < dist2) --submaps[curr_id];

                } else if (curr_id == size - 1) {
                    auto dist1 = distance(it, map.end());
                    auto dist2 = distance(submaps[curr_id], it);

                    if (dist2 < dist1) --submaps[curr_id];

                } else {
                    auto dist1 = distance(it, submaps[curr_id]);
                    auto dist2 = distance(submaps[curr_id - 1], it);

                    if (dist1 > dist2) {
                        ++submaps[curr_id - 1];
                    } else --submaps[curr_id];

                }

            } else CurrIdInc();

        }

        return {lock_guard<mutex>(*mtxs[curr_id]), map[key]};

    }

    Access AddIter(const K &key, Iterator& it) {
        submaps[curr_id] = it;
        return {lock_guard<mutex>(*mtxs[curr_id]), map[key]};
    }

    void CurrIdInc() {
        if (curr_id == size - 1) {
            curr_id = 0;
        } else ++curr_id;
    }

    using Submap = std::map<K, V>;
    using Id = int;
    using Key = int;
    using MinMaxKey = std::pair<int, int>;



    size_t curr_id;
    size_t size;
    std::mutex mtx;

    std::map<K, V> map;

    std::vector<Iterator> submaps;
    std::vector<mutex *> mtxs;
};
*/


/*
template<typename K, typename V>
class ConcurrentMap {
public:
    static_assert(is_integral_v<K>, "ConcurrentMap supports only integer keys");

    struct Access {
        std::lock_guard<std::mutex> lg;
        V &ref_to_value;
    };

    explicit ConcurrentMap(size_t bucket_count) : size(bucket_count),
                                                  curr_id(0){
        mtxs.reserve(bucket_count);
        submaps.reserve(bucket_count);
        for(size_t i = 0; i < bucket_count; ++i){
            submaps.emplace_back();
            mtxs.push_back(new mutex);
        }


    }

    Access operator[](const K &key) {
        return FindKeyId(key);
    }

    map<K, V> BuildOrdinaryMap() {
        std::map<K, V> res;
        for(auto& item : submaps){
            res.insert(item.begin(), item.end());
        }
        return res;
    }

private:

    Access FindKeyId(const K& key){
        std::lock_guard<mutex> lg(mtx);
        auto key_it = keys.find(key);
        if(key_it == keys.end()){
            CurrIdInc();
            return AddKey(key);
        } else {
            return {lock_guard<mutex>(*mtxs[key_it->second]), submaps[key_it->second][key]};
        }
    }

    Access AddKey(const K& key){
        keys[key] = curr_id;

        return {lock_guard<mutex>(*mtxs[curr_id]), submaps[curr_id][key]};
    }

    void CurrIdInc(){
        if(curr_id == size - 1){
            curr_id = 0;
        } else ++curr_id;
    }

    using Submap = std::map<K, V>;
    using Id = int;
    using Key = int;
    using MinMaxKey = std::pair<int, int>;

    size_t curr_id;
    size_t size;

    std::mutex mtx;

    std::map<Key, Id> keys;
    std::vector<Submap> submaps;
    std::vector<mutex*> mtxs;
};
*/