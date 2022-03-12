#ifndef TASK_9_PERSONALBUDGETSTARTERPLUSEDITION__BUDGET_H
#define TASK_9_PERSONALBUDGETSTARTERPLUSEDITION__BUDGET_H

#include <iostream>
#include <map>
#include <algorithm>
#include <numeric>
#include <sstream>

struct Date {
    int year = 0;
    int month = 0;
    int day = 0;
};

std::istream& operator>>(std::istream& is, Date& date);
int MonthToIndex(int month, bool is_leap);
int DateToIndex(const Date& date);

class Budget final {
public:

    std::array<size_t, 146101> data;

public:
    Budget() : data() {}

    void GetAllData();
    void GetAllIncome();

private:
    size_t GetIncome(const Date& date1, const Date& date2) const;

};


#endif //TASK_9_PERSONALBUDGETSTARTERPLUSEDITION__BUDGET_H
