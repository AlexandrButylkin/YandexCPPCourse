#include "database.h"
#include <stdexcept>


std::ostream& operator<<(std::ostream& os, const Entrie& data){
    os << data.first << " " << data.second;
    return os;
}

void Events::Add(const std::string &event) {
    const auto inserted = ordered_events.emplace(event);
    if(inserted.second){
        events.emplace_back(event);
    }
}

const std::deque<std::string> &Events::GetEvents() const {
    return events;
}


void Database::Add(const Date& date, const std::string& event){
    database[date].Add(event);
}

std::ostream& Database::Print(std::ostream& os) const{
    for(const auto& [date, events] : database){
        for(const auto& event : events.GetEvents()){
            os << date << " ";
            os << event << "\n";
        }
    }
    return os;
}

Entrie Database::Last(const Date& date) const{
    auto date_iter = database.upper_bound(date);

    if(date_iter == database.begin()){
        throw std::invalid_argument("");
    } else {
        date_iter = std::prev(date_iter);
    }
    return {date_iter->first, date_iter->second.GetEvents().back()};
}
