#ifndef TASK_1_HASHSET_H
#define TASK_1_HASHSET_H

#include <forward_list>
#include <iterator>
#include <vector>

using namespace std;

template <typename Type, typename Hasher>
class HashSet {
public:
    using BucketList = forward_list<Type>;

public:
    explicit HashSet(size_t num_buckets, const Hasher& hasher = {}) : data_(num_buckets), hasher_(hasher) {}

    void Add(const Type& value){
        const auto hash = GetHash(value);

        if(!Has(value)){
            data_[hash].emplace_front(value);
        }
    }

    bool Has(const Type& value) const {
        auto bl = GetBucket(value);
        return std::find(bl.begin(), bl.end(), value) != bl.end();
    }

    void Erase(const Type& value){
        const auto hash = GetHash(value);
        data_[hash].remove(value);
    }

    const BucketList& GetBucket(const Type& value) const{
        const auto hash = GetHash(value);
        return data_[hash];
    }

private:

    size_t GetHash(const Type& value) const {
        return hasher_(value) % data_.size();
    }

    std::vector<BucketList> data_;
    Hasher hasher_;
};

#endif //TASK_1_HASHSET_H
