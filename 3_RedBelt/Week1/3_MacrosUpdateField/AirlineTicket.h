#ifndef INC_3_MACROSUPDATEFIELD_AIRLINETICKET_H
#define INC_3_MACROSUPDATEFIELD_AIRLINETICKET_H

#include <string>
#include <tuple>
#include <sstream>

using std::string;
using std::tie;
using std::ostream;
using std::istream;

struct Date {
    int year, month, day;
};

struct Time {
    int hours, minutes;
};

struct AirlineTicket {
    string from;
    string to;
    string airline;
    Date departure_date;
    Time departure_time;
    Date arrival_date;
    Time arrival_time;
    int price;
};


bool operator < (const Date& lhs, const Date& rhs) {
    return tie(lhs.year, lhs.month, lhs.day) < tie(rhs.year, rhs.month, rhs.day);
}

bool operator == (const Date& lhs, const Date& rhs) {
    return tie(lhs.year, lhs.month, lhs.day) == tie(rhs.year, rhs.month, rhs.day);
}

bool operator < (const Time& lhs, const Time& rhs) {
    return tie(lhs.hours, lhs.minutes) < tie(rhs.hours, rhs.minutes);
}

bool operator == (const Time& lhs, const Time& rhs) {
    return tie(lhs.hours, lhs.minutes) == tie(rhs.hours, rhs.minutes);
}

ostream& operator<<(ostream& os, const Date& d) {
    return os << d.year << '.' << d.month << '.' << d.day;
}

ostream& operator<<(ostream& os, const Time& t) {
    return os << t.hours << ':' << t.minutes;
}

istream& operator>> (istream& is, Date& date){
    is >> date.year;
    is.ignore(1);
    is >> date.month;
    is.ignore(1);
    is >> date.day;
    return is;
}

istream& operator>> (istream& is, Time& time){
    is >> time.hours;
    is.ignore(1);
    is >> time.minutes;
    return is;
}

#define UPDATE_FIELD(ticket, field, values){        \
    auto it = (values).find(#field);                \
    if(it != (values).end()){                       \
        std::istringstream is(it->second);          \
        is >> (ticket).field;                       \
    }\
}

#endif //INC_3_MACROSUPDATEFIELD_AIRLINETICKET_H
