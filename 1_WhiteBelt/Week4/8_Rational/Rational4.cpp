#include <iostream>
#include <numeric>
#include <tuple>
#include <sstream>

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

int main() {
    {
        ostringstream output;
        output << Rational(-6, 8);
        if (output.str() != "-3/4") {
            cout << "Rational(-6, 8) should be written as \"-3/4\"" << endl;
            return 1;
        }
    }

    {
        istringstream input("5/7");
        Rational r;
        input >> r;
        bool equal = r == Rational(5, 7);
        if (!equal) {
            cout << "5/7 is incorrectly read as " << r << endl;
            return 2;
        }
    }

    {
        istringstream input("");
        Rational r;
        bool correct = !(input >> r);
        if (!correct) {
            cout << "Read from empty stream works incorrectly" << endl;
            return 3;
        }
    }

    {
        istringstream input("5/7 10/8");
        Rational r1, r2;
        input >> r1 >> r2;
        bool correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Multiple values are read incorrectly: " << r1 << " " << r2 << endl;
            return 4;
        }

        input >> r1;
        input >> r2;
        correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Read from empty stream shouldn't change arguments: " << r1 << " " << r2 << endl;
            return 5;
        }
    }

    {
        istringstream input1("1*2"), input2("1/"), input3("/4");
        Rational r1, r2, r3;
        input1 >> r1;
        input2 >> r2;
        input3 >> r3;
        bool correct = r1 == Rational() && r2 == Rational() && r3 == Rational();
        if (!correct) {
            cout << "Reading of incorrectly formatted rationals shouldn't change arguments: "
                 << r1 << " " << r2 << " " << r3 << endl;

            return 6;
        }
    }

    {
        istringstream input("2/4/6/8");
        Rational r1;
        input >> r1;
        bool correct = r1 == Rational(1, 2);
        if (!correct) {
            cout << "Multiple-slashed number sequence value read incorrectly: " << r1 << endl;
            return 7;
        }
    }

    cout << "OK" << endl;
    return 0;
}
