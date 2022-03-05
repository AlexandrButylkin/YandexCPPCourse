#ifndef WEEK6_DATE_H
#define WEEK6_DATE_H
#include <sstream>

struct Year {
    explicit Year(int year_) : year(year_) {}
    int year;
};

struct Month {
    explicit Month(int month_) : month(month_) {}
    int month;
};

struct Day {
    explicit Day(int day_) : day(day_) {}
    int day;
};

class Date {
public:
    explicit Date(Year year_, Month month_, Day day_) : year(year_), month(month_), day(day_){}

    [[nodiscard]] int getYear() const {return year.year;}
    [[nodiscard]] int getMonth() const {return month.month;}
    [[nodiscard]] int getDay() const {return day.day;}

    friend std::ostream& operator<< (std::ostream& os, const Date& date);
    friend bool operator==(const Date& lhs, const Date& rhs);
    friend bool operator!=(const Date& lhs, const Date& rhs);
    friend bool operator<(const Date& lhs, const Date& rhs);
    friend bool operator>(const Date& lhs, const Date& rhs);
    friend bool operator<=(const Date& lhs, const Date& rhs);
    friend bool operator>=(const Date& lhs, const Date& rhs);


private:
    Year year;
    Month month;
    Day day;
};

Date ParseDate(std::istream& is);

#endif //WEEK6_DATE_H
