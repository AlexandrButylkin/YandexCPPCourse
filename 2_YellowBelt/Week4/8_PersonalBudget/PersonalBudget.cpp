#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>

struct Date {
    int year = 0;
    int month = 0;
    int day = 0;
};

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

class Budget{
public:

    static int MonthToIndex(int month, bool is_leap) {
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

    static int DateToIndex(const Date& date) {
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

    struct Statistic{
        double income = 0;
        double expenses = 0;
    };

    std::array<Statistic, 36526> data;

public:
    Budget() : data() {}

    double ComputeIncome(const Date& from, const Date& to) const{

        double res = 0;

        for(int i = DateToIndex(from); i < DateToIndex(to) + 1; ++i){
            res += data[i].income - data[i].expenses;
        }
        return res;

    }

    void Earn(const Date& from, const Date& to, double value){
        int index_from = DateToIndex(from);
        int index_to = DateToIndex(to);

        double piece_value = value / (index_to + 1 - index_from);

        for(int i = index_from; i < index_to + 1; ++i){
            data[i].income += piece_value;
        }
    }

    void PayTax(const Date& from, const Date& to, double percent){

        for(int i = DateToIndex(from); i < DateToIndex(to) + 1; ++i){
            data[i].income *= percent;
        }

    }

    void Spend(const Date& from, const Date& to, double value){

        int index_from = DateToIndex(from);
        int index_to = DateToIndex(to);

        double piece_value = value / (index_to + 1 - index_from);

        for(int i = index_from; i < index_to + 1; ++i){
            data[i].expenses += piece_value;
        }
    }

};

void Process() {
    int count = 0;
    std::cin >> count;
    Budget b;

    while(count != 0) {
        std::string operation;
        Date from, to;
        std::cin >> operation >> from >> to;
        if(operation == "Earn"){
            double value;
            std::cin >> value;
            b.Earn(from, to, value);
        } else if (operation == "ComputeIncome"){
            std::cout << std::setprecision(25) << std::fixed << b.ComputeIncome(from, to) << "\n";
        } else if (operation == "PayTax") {
            double percent = 0.0;
            std::cin >> percent;
            percent = 1.0 - percent / 100;
            b.PayTax(from, to, percent);
        } else if (operation == "Spend"){
            double value;
            std::cin >> value;
            b.Spend(from, to, value);
        }
        --count;
    }
}


int main() {
    Process();
    return 0;
}