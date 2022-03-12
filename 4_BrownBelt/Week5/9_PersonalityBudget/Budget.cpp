#include "Budget.h"

std::istream& operator>>(std::istream& is, Date& date){
    is >> date.year;
    date.year = date.year % 1700;
    is.ignore(1);

    is >> date.month;
    is.ignore(1);

    is >> date.day;
    is.ignore(1);

    return is;
}

int MonthToIndex(int month, bool is_leap) {
    int res = 0;
    if(is_leap && month > 1) res += 1;

    res += month * 31;

    if(month == 0 || month == 1) return res;
    if(month == 2 || month == 3) return res - 3;
    if(month == 4 || month == 5) return res - 4;
    if(month == 6 || month == 7 || month == 8) return res - 5;
    if(month == 9 || month == 10) return res - 6;
    if(month == 11) return res - 7;
}

int DateToIndex(const Date& date) {
    int res = 0;

    res += date.year * 365;
    if(date.year != 0) {
        res += (date.year - 1) / 4 + 1;
    }

    if(date.year % 4 == 0)
        res += MonthToIndex(date.month - 1, true);
    else res += MonthToIndex(date.month - 1, false);

    res += date.day;

    return res;
}


void Budget::GetAllData(){
    size_t count = 0;
    std::cin >> count;
    while(count > 0){
        Date date;
        size_t value;
        std::cin >> date >> value;
        data[DateToIndex(date)] += value;

        --count;
    }

    std::partial_sum(data.begin(), data.end(), data.begin());

}

void Budget::GetAllIncome(){
    size_t count = 0;
    std::cin >> count;
    while(count != 0) {

        Date date1, date2;
        std::cin >> date1 >> date2;

        std::cout << GetIncome(date1, date2) << std::endl;

        --count;
    }

}

size_t Budget::GetIncome(const Date& date1, const Date& date2) const{
    size_t first = DateToIndex(date1), second = DateToIndex(date2);

    return data[second] - data[first - 1];
}
