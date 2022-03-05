#ifndef WEEK6_DATABASE_H
#define WEEK6_DATABASE_H

#include <string>
#include <map>
#include <set>
#include <deque>
#include <vector>
#include <iostream>
#include <list>
#include <algorithm>

#include "date.h"

struct AddedValue{
    std::vector<std::string> vec;
    std::set<std::string> set;
};

using Entries = std::vector<std::pair<Date, std::string>>;
using iterate = std::vector<std::string>;
class Database {
private:
    std::map<Date, AddedValue> database;
public:
    void Add(const Date& date, const std::string& event);
    std::ostream& Print(std::ostream& os) const;

    template <typename T>
    size_t RemoveIf(T predicate);

    template <typename T>
    Entries FindIf(T predicate) const;

    std::string Last(const Date& date) const;



};

template <typename T>
size_t Database::RemoveIf(T predicate) {
    size_t count = 0;
    auto mIt = database.begin();

    while (mIt != database.end()) {

        /*if (predicate(mIt->first, "")){
            count += mIt->second.size();
            mIt = database.erase(mIt);

        } else */
        auto it = mIt->second.vec.begin();
        auto lambda = [&mIt, &predicate](auto it){return !predicate(mIt->first, it);};
        it = std::stable_partition(it, mIt->second.vec.end(), lambda);
            auto lIt = mIt->second.vec.end();
            while(lIt != it){
                mIt->second.set.erase( mIt->second.vec.back());
                mIt->second.vec.pop_back();
                ++count;
                --lIt;
            }
            if (mIt->second.vec.empty()) {
                mIt = database.erase(mIt);
            } else ++mIt;


    }
    return count;




    /*while(mIt != database.end()) {
        auto sIt = mIt->second.begin();

        if(predicate(mIt->first, *sIt)) {

        } else {
            while (sIt != mIt->second.end() && !mIt->second.empty()) {
                if (predicate(mIt->first, *sIt)) {
                    sIt = mIt->second.erase(sIt);
                    ++count;
                } else ++sIt;
            }
            if (mIt->second.empty()) {
                auto mItDel = mIt;
                ++mIt;
                database.erase(mItDel);
            } else ++mIt;
        }

    }
    return count;*/
}

template <typename T>
Entries Database::FindIf(T predicate) const{
    Entries entries;
    auto mIt = database.begin();

    while(mIt != database.end()){

        /*if(predicate(mIt->first, "")){

            for(const auto& item : mIt->second) {
                entries.emplace_back(mIt->first, item);
            }

        } else {*/
        /*auto it = mIt->second.begin();
        auto lambda = [&mIt, &predicate](auto it){return predicate(mIt->first, it);};
        it = std::stable_partition(it, mIt->second.end(), lambda);
        auto lIt = mIt->second.begin();

        while(lIt != it){
            entries.emplace_back(mIt->first, *lIt);
            ++lIt;
        }*/


        for(const auto& item : mIt->second.vec){
            if(predicate(mIt->first, item)){
                entries.emplace_back(mIt->first, item);
            }
        }

        ++mIt;
    }

    return entries;


    /*while(it != database.end()) {
        for (const auto &item: it->second) {
            if (predicate(it->first, item)) {
                entries.push_back({it->first, item});
            }
        }
        ++it;
    }
    return entries;*/
}


#endif //WEEK6_DATABASE_H
