#include "database.h"
#include <algorithm>
#include <iostream>
void Database::Add(const Date& date, const std::string& event){
    if(database.find(date) != database.end()){
        if(database[date].set.find(event) == database[date].set.end()){
            database[date].vec.emplace_back(event);
            database[date].set.emplace(event);
        }
    } else {
        database[date].vec.emplace_back(event);
        database[date].set.emplace(event);
    }
}

/*template <typename T>
std::ostream& operator<<(std:: ostream& os, const std::set<T>& st){
    bool first = true;
    for (const auto &item: st) {
        if (!first) {
            os << " ";
        }
        first = false;
        os << item;
    }
    return os;
}*/


std::ostream& Database::Print(std::ostream& os) const{
    for(const auto& mItem : database){
        for(const auto& sItem : mItem.second.vec){
            os << mItem.first << " ";
            os << sItem << std::endl;
        }
    }
    return os;
}

std::string Database::Last(const Date& date) const{
    if(database.empty()) return "No entries";
    if (date < database.begin()->first) return "No entries";

    std::ostringstream os;
    auto it = database.find(date);

    if(it == database.end()){
        it = database.lower_bound(date);
        --it;
    }

    os << it->first << " " << it->second.vec.back();
    return os.str();



    /*if(!database.empty()) {
        if (date < database.begin()->first) return "No entries";

        for (auto it = database.rbegin(); it != database.rend(); ++it) {
            if (it->first <= date) {
                std::ostringstream os;
                os << it->first << " " << *(it->second.rbegin());
                return os.str();
            }
        }
    } else return "No entries";*/
}
