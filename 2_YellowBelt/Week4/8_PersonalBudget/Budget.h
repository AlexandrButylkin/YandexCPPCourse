#ifndef TASK_8_PERSONALBUDGET__BUDGET_H
#define TASK_8_PERSONALBUDGET__BUDGET_H

#include <vector>
#include <sstream>
#include <iomanip>

struct Date final {
    int year = 0;
    int month = 0;
    int day = 0;
};

std::istream& operator>>(std::istream& is, Date& date);
int MonthToIndex(int month, bool is_leap);
int DateToIndex(const Date& date);

class Budget{
public:

    struct Statistic{
        double income = 0;
        double expenses = 0;
    };

    std::array<Statistic, 36526> data;

public:
    Budget() : data() {}

    double ComputeIncome(const Date& from, const Date& to) const;
    void Earn(const Date& from, const Date& to, double value);
    void PayTax(const Date& from, const Date& to, double percent);
    void Spend(const Date& from, const Date& to, double value);

};


#endif //TASK_8_PERSONALBUDGET__BUDGET_H
