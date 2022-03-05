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

class Budget{
public:

    std::array<size_t, 146101> data;

public:
    Budget() : data() {}

    void GetAllData(){
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

    void GetAllIncome(){
        size_t count = 0;
        std::cin >> count;
        while(count != 0) {

            Date date1, date2;
            std::cin >> date1 >> date2;

            std::cout << GetIncome(date1, date2) << std::endl;

            --count;
        }

    }

private:
    size_t GetIncome(const Date& date1, const Date& date2) const{
        size_t first = DateToIndex(date1), second = DateToIndex(date2);

        return data[second] - data[first - 1];
    }

};


int main() {
    Budget b;
    b.GetAllData();
    b.GetAllIncome();
    return 0;
}

/*
class Budget{
public:
    Budget(std::istream& input, std::ostream& output) : is(input), os(output) {}

    void GetAllData(){
        size_t count = 0;
        is >> count;
        std::cerr << count << "\n";


        while(count > 0){
            std::string date;
            size_t value;

            is >> date >> value;
            std::cerr << date << " " << value << "\n";


            data[date] += value;

            --count;
        }

        IncomeToPartialSum();

    }

    void GetAllIncome(){
        size_t count = 0;
        is >> count;
        std::cerr << count << "\n";


        while(count != 0) {

            std::string date1, date2;
            is >> date1 >> date2;

            std::cerr << date1 << " " << date2 << "\n";

            os << GetIncome(date1, date2) << std::endl;

            --count;
        }

    }



private:

    void IncomeToPartialSum(){
        std::vector<size_t> vec;
        vec.reserve(data.size());

        for(const auto& item : data){
            vec.emplace_back(item.second);
        }

        std::partial_sum(vec.begin(), vec.end(), vec.begin());

        auto iter_data = data.begin();
        auto iter_vec = vec.begin();

        while(iter_data != data.end() && iter_vec != vec.end()){

            iter_data++->second = *iter_vec++;

        }
    }

    size_t GetIncome(const std::string& date1, const std::string& date2) const{
        size_t first = 0, second = 0;

        auto iter_date1 = data.lower_bound(date1);
        auto iter_date2 = data.lower_bound(date2);

        if(iter_date1->first == date1 && iter_date1 != data.begin()){
            first = (--iter_date1)->second;
        }

        if(iter_date2->first != date2 || iter_date2 == data.end()){
            --iter_date2;
        }
        second = iter_date2->second;

        return second - first;
    }

private:

    std::map<std::string, size_t> data;

    std::istream& is;
    std::ostream& os;

};

int main() {
    std::vector<int> a(1);
    Budget b(std::cin, std::cout);
    b.GetAllData();
    b.GetAllIncome();
    std::cout << a[2];
    return 0;
}*/
