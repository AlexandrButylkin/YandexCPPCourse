#ifndef TASK_5_DATABASE_H
#define TASK_5_DATABASE_H

#include <unordered_map>
#include <memory>
#include <map>

struct Record final {
    std::string id = {};
    std::string title = {};
    std::string user = {};
    int timestamp = {};
    int karma = {};
    bool operator==(const Record &record) const;
};

class Database final {
public:

    bool Put(const Record &record);
    const Record *GetById(const std::string &id) const;
    bool Erase(const std::string &id);

    template<typename Callback>
    void RangeByTimestamp(int low, int high, Callback callback) const;

    template<typename Callback>
    void RangeByKarma(int low, int high, Callback callback) const;

    template<typename Callback>
    void AllByUser(const std::string &user, Callback callback) const;


private:

    template<typename T>
    using Index = std::multimap<T, std::shared_ptr<Record>>;

    struct Data {
        std::shared_ptr<Record> record_;

        Index<int>::iterator timestamp_it;
        Index<int>::iterator karma_it;
        Index<std::string>::iterator user_it;
    };

    std::unordered_map<std::string, Data> data;

    Index<int> timestamps;
    Index<int> karmas;
    Index<std::string> users;
};


template<typename Callback>
void Database::RangeByTimestamp(int low, int high, Callback callback) const {
    auto begin = timestamps.lower_bound(low);
    auto end = timestamps.upper_bound(high);

    for(; begin != end; ++begin) {
        if(!callback(*begin->second)){
            return;
        }
    }
}

template<typename Callback>
void Database::RangeByKarma(int low, int high, Callback callback) const {
    auto begin = karmas.lower_bound(low);
    auto end = karmas.upper_bound(high);

    for(; begin != end; ++begin){
        if(!callback(*begin->second)){
            return;
        }
    }
}

template<typename Callback>
void Database::AllByUser(const std::string &user, Callback callback) const {
    auto [begin, end] = users.equal_range(user);

    for(; begin != end; ++begin){
        if(!callback(*begin->second)){
            return;
        }
    }
}



#endif //TASK_5_DATABASE_H
