#include "date.h"
#include <string>
#include <iomanip>

std::ostream& operator<<(std::ostream &os, const Date &date) {
    os << std::setw(4) << std::setfill('0') << date.GetYear() << "-";
    os << std::setw(2) << std::setfill('0') << date.GetMonth() << "-";
    os << std::setw(2) << std::setfill('0') << date.GetDay();
    return os;
}

Date ParseDate(std::istream& is){
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
        throw std::runtime_error("Wrong date format");
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

bool operator==(const Date& lhs, const Date& rhs){
    return std::tuple{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} ==
           std::tuple{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}

bool operator<(const Date& lhs, const Date& rhs){
    return std::tuple{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} <
           std::tuple{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}

bool operator!=(const Date& lhs, const Date& rhs){
    return !(lhs == rhs);
}

bool operator>(const Date& lhs, const Date& rhs){
    return !(lhs < rhs) && (lhs != rhs);
}

bool operator<=(const Date& lhs, const Date& rhs){
    return (lhs == rhs) || (lhs < rhs);
}

bool operator>=(const Date& lhs, const Date& rhs){
    return (lhs == rhs) || (lhs > rhs);
}