#include "test_runner.h"

#include <forward_list>
#include <iterator>
#include <unordered_map>

using namespace std;

template <typename Type, typename Hasher>
class HashSet {
public:
    using BucketList = forward_list<Type>;

public:
    explicit HashSet(
            size_t num_buckets,
            const Hasher& hasher = {}
    ) : table(num_buckets), function(hasher){}

    void Add(const Type& value){
        if(!Has(value)) {
            table[function(value)].push_front(value);
        }
    }

    bool Has(const Type& value) const{
        auto iter = table.find(function(value));

        if(iter != table.end()){
            for(const auto& item : iter->second){
                if(item == value) return true;
            }
        } return false;
    }

    void Erase(const Type& value){
        auto hash = function(value);
        auto iter = table.find(hash);

        if(iter == table.end()) return;

        if(*iter->second.begin() == value) {
            iter->second.erase_after(iter->second.before_begin());
        } else {
            for(auto it = iter->second.begin(); it != std::prev(iter->second.end()); ++it){

                if(*std::next(it) == value) iter->second.erase_after(it);

            }
        }

        if(iter->second.empty()) table.erase(hash);

    }



    const BucketList& GetBucket(const Type& value) const{
        auto iter = table.find(function(value));
        if(iter != table.end()){
            return iter->second;
        }
    }

private:
    std::unordered_map<int, BucketList> table;


    //std::vector<BucketList> table;
    Hasher function;
};

struct IntHasher {
    size_t operator()(int value) const {
        // Это реальная хеш-функция из libc++, libstdc++.
        // Чтобы она работала хорошо, std::unordered_map
        // использует простые числа для числа бакетов
        return value;
    }
};

struct TestValue {
    int value;

    bool operator==(TestValue other) const {
        return value / 2 == other.value / 2;
    }
};

struct TestValueHasher {
    size_t operator()(TestValue value) const {
        return value.value / 2;
    }
};

void TestSmoke() {
    HashSet<int, IntHasher> hash_set(2);
    hash_set.Add(3);
    hash_set.Add(4);

    ASSERT(hash_set.Has(3));
    ASSERT(hash_set.Has(4));
    ASSERT(!hash_set.Has(5));

    hash_set.Erase(3);

    ASSERT(!hash_set.Has(3));
    ASSERT(hash_set.Has(4));
    ASSERT(!hash_set.Has(5));

    hash_set.Add(3);
    hash_set.Add(5);

    ASSERT(hash_set.Has(3));
    ASSERT(hash_set.Has(4));
    ASSERT(hash_set.Has(5));
}

void TestEmpty() {
    HashSet<int, IntHasher> hash_set(10);
    for (int value = 0; value < 10000; ++value) {
        ASSERT(!hash_set.Has(value));
    }
}

void TestIdempotency() {
    HashSet<int, IntHasher> hash_set(10);
    hash_set.Add(5);
    ASSERT(hash_set.Has(5));
    hash_set.Add(5);
    ASSERT(hash_set.Has(5));
    hash_set.Erase(5);
    ASSERT(!hash_set.Has(5));
    hash_set.Erase(5);
    ASSERT(!hash_set.Has(5));
}

void TestEquivalence() {
    HashSet<TestValue, TestValueHasher> hash_set(10);
    hash_set.Add(TestValue{2});
    hash_set.Add(TestValue{3});

    ASSERT(hash_set.Has(TestValue{2}));
    ASSERT(hash_set.Has(TestValue{3}));

    const auto& bucket = hash_set.GetBucket(TestValue{2});
    const auto& three_bucket = hash_set.GetBucket(TestValue{3});
    ASSERT_EQUAL(&bucket, &three_bucket);

    ASSERT_EQUAL(1, distance(begin(bucket), end(bucket)));
    ASSERT_EQUAL(2, bucket.front().value);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestSmoke);
    RUN_TEST(tr, TestEmpty);
    RUN_TEST(tr, TestIdempotency);
    RUN_TEST(tr, TestEquivalence);

    /*std::forward_list<int> a;
    a.push_front(1);
    a.push_front(2);
    a.push_front(3);
    a.push_front(4);
    std::vector<std::forward_list<int>> v;
    v.push_back(a);
    v.push_back(a);
    v.push_back(a);
    v.push_back(a);
    return 0;*/
}
