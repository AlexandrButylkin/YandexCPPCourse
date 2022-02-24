#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>

struct Year{
    int year_;
    explicit Year(int year) : year_(year) {}
};

struct Month{
    int month_;
    explicit Month(int month) : month_(month) {}
};

struct Day{
    int day_;
    explicit Day(int day) : day_(day) {}
};

class Date {
private:
    Year year_;
    Month month_;
    Day day_;

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


public:
    explicit Date() : year_(0), month_(0), day_(0) {}

    explicit Date(const Year& year, const Month& month, const Day& day):
            year_(year),
            month_(month),
            day_(day){}

    int DateToIndex() const{
        int res = 0;

        res += year_.year_ * 365;
        if(year_.year_ != 0) {
            res += (year_.year_ - 1) / 4 + 1;
        }

        if(year_.year_ % 4 == 0)
            res += MonthToIndex(month_.month_ - 1, true);
        else res += MonthToIndex(month_.month_ - 1, false);

        res += day_.day_;

        return res;
    }

};

std::istream& operator>>(std::istream& is, Date& date) {

    int year, month, day;

    is >> year;
    year = year % 100;
    is.ignore(1);

    is >> month;
    is.ignore(1);

    is >> day;
    is.ignore(1);

    date = Date(Year(year), Month(month), Day(day));

    return is;
}

class Budget{
public:

    struct Statistic{
        double income = 0;
        double expenses = 0;
    };

    std::array<Statistic, 36526> data;

public:
    Budget() : data() {}

    double ComputeIncome(const Date& from, const Date& to) const{

        double res = 0;

        for(int i = from.DateToIndex(); i < to.DateToIndex() + 1; ++i){
            res += data[i].income - data[i].expenses;
        }
        return res;

    }

    void Earn(const Date& from, const Date& to, double value){
        int index_from = from.DateToIndex();
        int index_to = to.DateToIndex();

        double piece_value = value / (index_to + 1 - index_from);

        for(int i = index_from; i < index_to + 1; ++i){
            data[i].income += piece_value;
        }
    }

    void PayTax(const Date& from, const Date& to, double percent){

        for(int i = from.DateToIndex(); i < to.DateToIndex() + 1; ++i){
            data[i].income *= percent;
        }

    }

    void Spend(const Date& from, const Date& to, double value){

        int index_from = from.DateToIndex();
        int index_to = to.DateToIndex();

        double piece_value = value / (index_to + 1 - index_from);

        for(int i = index_from; i < index_to + 1; ++i){
            data[i].expenses += piece_value;
        }
    }

};

class Manager {
private:
    class DefaultRequest{
    public:
        DefaultRequest(Date from, Date to, Budget* b) : from_(from), to_(to), b_(b) {}

        virtual void Process() const = 0;
        virtual ~DefaultRequest() = default;
    protected:
        Date from_;
        Date to_;
        Budget* b_;
    };

    class Earn : public DefaultRequest{
    public:
        Earn(double value, Date from, Date to, Budget* b) : value_(value), DefaultRequest(from, to, b) {}
        void Process() const override{
            b_->Earn(from_, to_, value_);
        }
    private:
        double value_;
    };

    class PayTax : public DefaultRequest {
    public:
        PayTax(double percent, Date from, Date to, Budget* b) : percent_(percent), DefaultRequest(from, to, b) {}
        void Process() const override{
            b_->PayTax(from_, to_, percent_);
        }
    private:
        double percent_;
    };

    class ComputeIncome : public DefaultRequest {
    public:

        ComputeIncome( std::ostream& output, Date from, Date to, Budget* b) : os(output), DefaultRequest(from, to, b) {}
        void Process() const override{
            os << b_->ComputeIncome(from_, to_) << std::endl;
        }

    private:
        std::ostream& os;
    };

    class Spend : public DefaultRequest{
    public:
        Spend(double value, Date from, Date to, Budget* b) : value_(value), DefaultRequest(from, to, b) {}
        void Process() const override{
            b_->Spend(from_, to_, value_);
        }
    private:
        double value_;
    };

public:
    Manager(std::istream& input, std::ostream& output) : is(input), os(output), b() {
        input >> count_request;
        queue.reserve(count_request);
    }

    void ReadAllRequest() {
        for(size_t i = 0; i < count_request; ++i) {
            std::string str;
            Date from, to;
            is >> str >> from >> to;
            if (str == "Earn") {
                double value;
                is >> value;
                queue.push_back(std::make_unique<Earn>(value, from, to, &b));
            } else if (str == "PayTax") {
                double percent;
                is >> percent;
                percent = 1 - percent / 100;
                queue.push_back(std::make_unique<PayTax>(percent, from, to, &b));
            } else if (str == "ComputeIncome") {
                queue.push_back(std::make_unique<ComputeIncome>(os, from, to, &b));
            } else if (str == "Spend") {
                double value;
                is >> value;
                queue.push_back(std::make_unique<Spend>(value, from, to, &b));
            }
        }
    }

    void ProcessAllRequest(){
        for(const auto& item : queue){
            item->Process();
        }
    }


private:
    Budget b;
    std::istream& is;
    std::ostream& os;
    size_t count_request;
    std::vector<std::unique_ptr<DefaultRequest>> queue;
};


int main() {
    std::cout.precision(25);
    Manager m(std::cin, std::cout);
    m.ReadAllRequest();
    m.ProcessAllRequest();
    return 0;
}
