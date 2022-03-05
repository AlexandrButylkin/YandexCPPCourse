#include "date.h"
#include <string>
#include <iomanip>
#include <exception>

std::ostream& operator<<(std::ostream &os, const Date &date) {
    os << std::setw(4) << std::setfill('0') << date.year.year << "-" <<
            std::setw(2) << std::setfill('0') << date.month.month << "-" <<
            std::setw(2) << std::setfill('0') << date.day.day;
    return os;
}

Date ParseDate(std::istream& is){
    int year = 0, month = 0, day = 0;

    if (!(is >> year)) throw std::runtime_error("Wrong date format: ");
    if(is.peek() != '-') throw std::runtime_error("Wrong date format: ");
    else is.ignore(1);

    if (!(is >> month)) throw std::runtime_error("Wrong date format: ");
    if(is.peek() != '-') throw std::runtime_error("Wrong date format: ");
    else is.ignore(1);

    if (!(is >> day)) throw std::runtime_error("Wrong date format: ");
    is >> std::ws;

    if(month < 1 || month > 12) throw std::runtime_error("Month value is invalid: " + std::to_string(month));
    if(day < 1 || day > 31) throw std::runtime_error("Day value is invalid: " + std::to_string(day));

    return Date(Year(year), Month(month), Day(day));
}

bool operator==(const Date& lhs, const Date& rhs){
    if(lhs.getYear() == rhs.getYear()){
        if(lhs.getMonth() == rhs.getMonth()) return lhs.getDay() == rhs.getDay();
        else return false;
    }
    else return false;
}

bool operator!=(const Date& lhs, const Date& rhs){
    if(lhs.getYear() == rhs.getYear()){
        if(lhs.getMonth() == rhs.getMonth()) return lhs.getDay() != rhs.getDay();
        else return true;
    }
    else return true;
}

bool operator<(const Date& lhs, const Date& rhs){
    if(lhs.getYear() != rhs.getYear()) return lhs.getYear() < rhs.getYear();
    else if(lhs.getMonth() != rhs.getMonth()) return lhs.getMonth() < rhs.getMonth();
    else return lhs.getDay() < rhs.getDay();
}

bool operator>(const Date& lhs, const Date& rhs){
    if(lhs.getYear() != rhs.getYear()) return lhs.getYear() > rhs.getYear();
    else if(lhs.getMonth() != rhs.getMonth()) return lhs.getMonth() > rhs.getMonth();
    else return lhs.getDay() > rhs.getDay();
}

bool operator<=(const Date& lhs, const Date& rhs){
    if(lhs.getYear() != rhs.getYear()) return lhs.getYear() <= rhs.getYear();
    else if(lhs.getMonth() != rhs.getMonth()) return lhs.getMonth() <= rhs.getMonth();
    else return lhs.getDay() <= rhs.getDay();
}

bool operator>=(const Date& lhs, const Date& rhs){
    if(lhs.getYear() != rhs.getYear()) return lhs.getYear() >= rhs.getYear();
    else if(lhs.getMonth() != rhs.getMonth()) return lhs.getMonth() >= rhs.getMonth();
    else return lhs.getDay() >= rhs.getDay();
}