#ifndef WEEK6_DATABASE_H
#define WEEK6_DATABASE_H

#include "date.h"

#include <string>
#include <map>
#include <set>
#include <deque>
#include <vector>
#include <list>
#include <algorithm>
#include <sstream>


class Events final {
public:
    void Add(const std::string& event);
    const std::deque<std::string>& GetEvents() const;

    template<typename T>
    size_t RemoveIf(T predicate);



private:
    std::deque<std::string> events;
    std::set<std::string> ordered_events;
};

template<typename T>
size_t Events::RemoveIf(T predicate){
    auto iter_event = std::stable_partition(events.begin(), events.end(), predicate);
    size_t result = iter_event - events.begin();
    for(auto it = events.begin(); it != iter_event; ++it){
        ordered_events.erase(*it);
    }
    events.erase(events.begin(), iter_event);
    return result;
}

using Entrie= std::pair<Date, std::string>;
using Entries = std::vector<Entrie>;

std::ostream& operator<<(std::ostream& os, const Entrie& data);

class Database final {
public:
    void Add(const Date& date, const std::string& event);
    std::ostream& Print(std::ostream& os) const;
    Entrie Last(const Date& date) const;

    template <typename T>
    size_t RemoveIf(T predicate);
    template <typename T>
    Entries FindIf(T predicate) const;
private:
    std::map<Date, Events> database;
};

template <typename T>
size_t Database::RemoveIf(T predicate) {
    size_t count = 0;
    auto date_iter = database.begin();

    while(date_iter != database.end()){
        count += date_iter->second.RemoveIf([&date_iter, &predicate](const std::string& event){
            return predicate(date_iter->first, event);
        });
        if(date_iter->second.GetEvents().empty()){
            date_iter = database.erase(date_iter);
        } else {
            ++date_iter;
        }
    }

    return count;
}

template <typename T>
Entries Database::FindIf(T predicate) const{
    Entries entries;
    auto date_iter = database.begin();

    for(const auto& [date, events] : database){
        for(const auto& event : events.GetEvents()){
            if(predicate(date, event)){
                entries.emplace_back(date, event);
            }
        }
    }
    return entries;
}

//TESTS
void TestDatabaseAddAndPrint();
void TestDatabaseFind();
void TestDatabaseRemove();
void TestDatabaseLast();
void TestDatabaseException();

#endif //WEEK6_DATABASE_H
