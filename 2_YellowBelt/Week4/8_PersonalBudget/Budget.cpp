#include "Budget.h"

std::istream& operator>>(std::istream& is, Date& date){
    is >> date.year;
    date.year = date.year % 100;
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



double Budget::ComputeIncome(const Date& from, const Date& to) const{

    double res = 0;

    for(int i = DateToIndex(from); i < DateToIndex(to) + 1; ++i){
        res += data[i].income - data[i].expenses;
    }
    return res;

}

void Budget::Earn(const Date& from, const Date& to, double value){
    int index_from = DateToIndex(from);
    int index_to = DateToIndex(to);

    double piece_value = value / (index_to + 1 - index_from);

    for(int i = index_from; i < index_to + 1; ++i){
        data[i].income += piece_value;
    }
}

void Budget::PayTax(const Date& from, const Date& to, double percent){

    for(int i = DateToIndex(from); i < DateToIndex(to) + 1; ++i){
        data[i].income *= percent;
    }

}

void Budget::Spend(const Date& from, const Date& to, double value){

    int index_from = DateToIndex(from);
    int index_to = DateToIndex(to);

    double piece_value = value / (index_to + 1 - index_from);

    for(int i = index_from; i < index_to + 1; ++i){
        data[i].expenses += piece_value;
    }
}