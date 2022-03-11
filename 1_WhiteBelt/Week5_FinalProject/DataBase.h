#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include <exception>
#include <iomanip>
#include <tuple>
#include <optional>

struct Year {
    int year_;
    explicit Year(int year) : year_(year) {}
};

struct Month {
    int month_;
    explicit Month(int month) : month_(month) {}
};

struct Day {
    int day_;
    explicit Day(int day) : day_(day) {}
};

class Date final {
private:
    Year year_;
    Month month_;
    Day day_;

public:
    Date() : year_(Year(0)), month_(Month(0)), day_(Day(0)){};
    Date(const Year& year, const Month& month, const Day& day) : year_(year), month_(month), day_(day) {}
    Date(const Date& date) = default;
    Date& operator=(const Date& date);

    int GetYear() const;
    int GetMonth() const;
    int GetDay() const;

};

std::ostream& operator<<(std::ostream& os, const Date& date);
bool operator==(const Date& lhs, const Date& rhs);
bool operator<(const Date& lhs, const Date& rhs);
Date StringToDate(const std::string& date);


class Database final {
private:
    std::map<Date, std::set<std::string>> database;

public:
    void AddEvent(const Date& date, const std::string& event);
    bool DeleteEvent(const Date& date, const std::string& event);
    size_t DeleteDate(const Date& date);
    std::set<std::string> Find(const Date& date) const;
    void Print() const;
};