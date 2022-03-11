#include "DataBase.h"

Date& Date::operator=(const Date& date){
    year_ = Year(date.GetYear());
    month_ = Month(date.GetMonth());
    day_ = Day(date.GetDay());
    return *this;
}

int Date::GetYear() const {
    return year_.year_;
}

int Date::GetMonth() const {
    return month_.month_;
}

int Date::GetDay() const {
    return day_.day_;
}

std::ostream& operator<<(std::ostream& os, const Date& date){
    os << std::setw(4) << std::setfill('0') << date.GetYear() << "-";
    std::cout << std::setw(2) << std::setfill('0') << date.GetMonth() << "-";
    std::cout << std::setw(2) << std::setfill('0') << date.GetDay();
    return os;
}

bool operator==(const Date& lhs, const Date& rhs){
    return std::tuple{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} ==
           std::tuple{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}

bool operator<(const Date& lhs, const Date& rhs){
    return std::tuple{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} <
           std::tuple{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}

Date StringToDate(const std::string& date){
    std::istringstream is(date);
    int day, month, year;
    bool format_is_ok = true;

    format_is_ok = format_is_ok && (is >> year);
    format_is_ok = format_is_ok && (is.peek() == '-');
    is.ignore(1);

    format_is_ok = format_is_ok && (is >> month);
    format_is_ok = format_is_ok && (is.peek() == '-');
    is.ignore(1);

    format_is_ok = format_is_ok && (is >> day);
    format_is_ok = format_is_ok && (is.eof() || is.peek() == ' ' || is.peek() == '\n');

    if(!format_is_ok) {
        throw std::runtime_error("Wrong date format: " + date);
    } else {
        if(month < 1 || month > 12) {
            throw std::runtime_error("Month value is invalid: " + std::to_string(month));
        }
        if(day < 1 || day > 31) {
            throw std::runtime_error("Day value is invalid: " + std::to_string(day));
        }

        return { Year(year), Month(month), Day(day) };
    }
}




void Database::AddEvent(const Date& date, const std::string& event){
    database[date].emplace(event);
}

bool Database::DeleteEvent(const Date& date, const std::string& event){
    const auto date_iter = database.find(date);

    if(date_iter != database.end()){
        return date_iter->second.erase(event);
    }
    return false;
}

size_t Database::DeleteDate(const Date& date){
    const auto date_iter = database.find(date);

    if(date_iter!= database.end()){
        size_t numberOfEvents = date_iter->second.size();
        database.erase(date);
        return numberOfEvents;
    }
    return 0;
}

std::set<std::string> Database::Find(const Date& date) const{
    const auto date_iter = database.find(date);

    if(date_iter != database.end()){
        return date_iter->second;
    }
    return {};
}

void Database::Print() const{
    for(const auto& date : database){
        for(const auto& event : date.second){
            std::cout << date.first << " " << event << std::endl;
        }
    }
}