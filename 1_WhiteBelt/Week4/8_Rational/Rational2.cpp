#include <iostream>
#include <tuple>
#include <numeric>

using namespace std;

class Rational final {
public:
    Rational() : numerator(0), denominator(1) {}

    Rational(const int numerator_, const int denominator_) {
        //обработка отрицательного знаменателя будет обработана в следующих частях задачи
        if (numerator_ == 0) {
            denominator = 1;
            numerator = 0;
        } else {
            int gcd_ = std::gcd(numerator_, denominator_);
            if (denominator_ < 0) {
                denominator = denominator_ * -1 / gcd_;
                numerator = numerator_ * -1 / gcd_;
            } else {
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


// Реализуйте для класса Rational операторы ==, + и -

int main() {
    {
        Rational r1(4, 6);
        Rational r2(2, 3);
        bool equal = r1 == r2;
        if (!equal) {
            cout << "4/6 != 2/3" << endl;
            return 1;
        }
    }

    {
        Rational r1(3, 6);
        Rational r2(2, 3);
        bool equal = r1 == r2;
        if (equal) {
            cout << "3/6 == 2/3" << endl;
            return 1;
        }
    }

    {
        Rational a(2, 3);
        Rational b(4, 15);
        Rational c = a + b;
        bool equal = c == Rational(14, 15);
        if (!equal) {
            cout << "2/3 + 4/3 != 2" << endl;
            return 2;
        }
    }

    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a + b;
        bool equal = c == Rational(2, 1);
        if (!equal) {
            cout << "2/3 + 4/3 != 2" << endl;
            return 2;
        }
    }

    {
        Rational a(5, 7);
        Rational b(2, 9);
        Rational c = a - b;
        bool equal = c == Rational(31, 63);
        if (!equal) {
            cout << "5/7 - 2/9 != 31/63" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}
