#include "RationalFinal.h"

RationalFinal::RationalFinal(const int& numerator_, const int& denominator_) {
    if(denominator_ == 0){
        throw std::invalid_argument("Invalid argument: denominator = 0");
    }
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

int RationalFinal::Numerator() const {
    return numerator;
}

int RationalFinal::Denominator() const {
    return denominator;
}


bool operator==(const RationalFinal& lhs, const RationalFinal& rhs){
    return std::tuple{lhs.Denominator(), lhs.Numerator()} ==
           std::tuple{rhs.Denominator(), rhs.Numerator()};
}

RationalFinal operator+(const RationalFinal& lhs, const RationalFinal& rhs){
    int lcm = std::lcm(lhs.Denominator(), rhs.Denominator());
    return {lhs.Numerator() * (lcm / lhs.Denominator()) +
            rhs.Numerator() * (lcm / rhs.Denominator()), lcm};
}

RationalFinal operator-(const RationalFinal& lhs, const RationalFinal& rhs){
    int lcm = std::lcm(lhs.Denominator(), rhs.Denominator());
    return {lhs.Numerator() * (lcm / lhs.Denominator()) -
            rhs.Numerator() * (lcm / rhs.Denominator()), lcm};
}

RationalFinal operator*(const RationalFinal& lhs, const RationalFinal& rhs){
    int num = lhs.Numerator() * rhs.Numerator();
    int denom = lhs.Denominator() * rhs.Denominator();
    return {num, denom};
}

RationalFinal operator/(const RationalFinal& lhs, const RationalFinal& rhs){
    if(rhs.Numerator() == 0){
        throw std::domain_error("Division by zero");
    }
    int num = rhs.Numerator();
    int denom = rhs.Denominator();
    std::swap(num, denom);
    return lhs * RationalFinal(num, denom);
}

std::ostream& operator<<(std::ostream& os, const RationalFinal& rational){
    os << rational.Numerator() << "/" << rational.Denominator();
    return os;
}

std::istream& operator >> (std::istream& is, RationalFinal& rational) {
    int num = 0, denom = 0;
    char c;

    if (is) {
        is >> num >> c >> denom;
        if (is) {
            if (c == '/') {
                rational = RationalFinal(num, denom);
            }
            else {
                is.setstate(std::ios_base::failbit);
            }
        }
    }

    return is;
}

bool operator < (const RationalFinal& lhs, const RationalFinal& rhs) {
    RationalFinal number = lhs - rhs;
    return number.Numerator() < 0;
}

bool operator <= (const RationalFinal& lhs, const RationalFinal& rhs) {
    RationalFinal number = lhs - rhs;
    return number.Numerator() <= 0;
}

bool operator > (const RationalFinal& lhs, const RationalFinal& rhs) {
    RationalFinal number = lhs - rhs;
    return number.Numerator() > 0;
}

bool operator >= (const RationalFinal& lhs, const RationalFinal& rhs) {
    RationalFinal number = lhs - rhs;
    return number.Numerator() >= 0;
}