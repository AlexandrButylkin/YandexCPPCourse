#include <iostream>
#include <numeric>
#include <tuple>
#include <sstream>
#include <set>
#include <map>
#include <vector>

using namespace std;

class Rational final {
public:
    Rational() : numerator(0), denominator(1) {}

    Rational(const int& numerator_, const int& denominator_) {
        //обработка отрицательного знаменателя будет обработана в следующих частях задачи
        if(numerator_ == 0){
            denominator = 1;
            numerator = 0;
        }
        else {
            int gcd_ = std::gcd(numerator_, denominator_);
            if(denominator_ < 0) {
                denominator = denominator_ * -1 / gcd_;
                numerator = numerator_ * -1 / gcd_;
            } else{
                denominator = denominator_ / gcd_;
                numerator = numerator_ / gcd_;
            }
        }
    }

    Rational(const Rational &rational) = default;
    Rational &operator=(const Rational &rational) = default;

    int Numerator() const {
        return numerator;
    }

    int Denominator() const {
        return denominator;
    }

    ~Rational() = default;

private:
    int numerator;
    int denominator;
};

bool operator==(const Rational& lhs, const Rational& rhs){
    return std::tuple{lhs.Denominator(), lhs.Numerator()} ==
           std::tuple{rhs.Denominator(), rhs.Numerator()};
}

Rational operator+(const Rational& lhs, const Rational& rhs){
    int lcm = std::lcm(lhs.Denominator(), rhs.Denominator());
    return {lhs.Numerator() * (lcm / lhs.Denominator()) +
            rhs.Numerator() * (lcm / rhs.Denominator()), lcm};
}

Rational operator-(const Rational& lhs, const Rational& rhs){
    int lcm = std::lcm(lhs.Denominator(), rhs.Denominator());
    return {lhs.Numerator() * (lcm / lhs.Denominator()) -
            rhs.Numerator() * (lcm / rhs.Denominator()), lcm};
}

Rational operator*(const Rational& lhs, const Rational& rhs){
    int num = lhs.Numerator() * rhs.Numerator();
    int denom = lhs.Denominator() * rhs.Denominator();
    return {num, denom};
}

Rational operator/(const Rational& lhs, const Rational& rhs){

    int num = rhs.Numerator();
    int denom = rhs.Denominator();
    std::swap(num, denom);
    return lhs * Rational(num, denom);
}

ostream& operator<<(ostream& os, const Rational& rational){
    os << rational.Numerator() << "/" << rational.Denominator();
    return os;
}

istream& operator >> (istream& is, Rational& rational) {
    int num = 0, denom = 0;
    char c;

    if (is) {
        is >> num >> c >> denom;
        if (is) {
            if (c == '/') {
                rational = Rational(num, denom);
            }
            else {
                is.setstate(ios_base::failbit);
            }
        }
    }

    return is;
}

bool operator < (const Rational& lhs, const Rational& rhs) {
    Rational number = lhs - rhs;
    return number.Numerator() < 0;
}

bool operator <= (const Rational& lhs, const Rational& rhs) {
    Rational number = lhs - rhs;
    return number.Numerator() <= 0;
}

bool operator > (const Rational& lhs, const Rational& rhs) {
    Rational number = lhs - rhs;
    return number.Numerator() > 0;
}

bool operator >= (const Rational& lhs, const Rational& rhs) {
    Rational number = lhs - rhs;
    return number.Numerator() >= 0;
}

int main() {
    {
        const set<Rational> rs = {{1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2}};
        if (rs.size() != 3) {
            cout << "Wrong amount of items in the set" << endl;
            return 1;
        }

        vector<Rational> v;
        for (auto x : rs) {
            v.push_back(x);
        }
        if (v != vector<Rational>{{1, 25}, {1, 2}, {3, 4}}) {
            cout << "Rationals comparison works incorrectly" << endl;
            return 2;
        }
    }

    {
        map<Rational, int> count;
        ++count[{1, 2}];
        ++count[{1, 2}];

        ++count[{2, 3}];

        if (count.size() != 2) {
            cout << "Wrong amount of items in the map" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}
