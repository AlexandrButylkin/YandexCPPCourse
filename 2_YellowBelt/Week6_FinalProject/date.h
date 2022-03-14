#ifndef WEEK6_DATE_H
#define WEEK6_DATE_H
#include <sstream>

struct Year final {
    int year_;
    explicit Year(int year) : year_(year) {}
};

struct Month final {
    int month_;
    explicit Month(int month) : month_(month) {}
};

struct Day final {
    int day_;
    explicit Day(int day) : day_(day) {}
};

class Date final {
public:
    Date() : year_(Year(0)), month_(Month(0)), day_(Day(0)){};
    Date(const Year& year, const Month& month, const Day& day) : year_(year), month_(month), day_(day){}

    int GetYear() const {return year_.year_;}
    int GetMonth() const {return month_.month_;}
    int GetDay() const {return day_.day_;}

private:
    Year year_;
    Month month_;
    Day day_;
};

std::ostream& operator<< (std::ostream& os, const Date& date);

bool operator==(const Date& lhs, const Date& rhs);
bool operator<(const Date& lhs, const Date& rhs);
bool operator!=(const Date& lhs, const Date& rhs);
bool operator>(const Date& lhs, const Date& rhs);
bool operator<=(const Date& lhs, const Date& rhs);
bool operator>=(const Date& lhs, const Date& rhs);

Date ParseDate(std::istream& is);

//TESTS
void TestDateOutput();
void TestParseDate();

#endif //WEEK6_DATE_H
