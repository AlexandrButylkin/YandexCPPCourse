#include "Rational_last.h"
    void swap(int& a, int& b){
        int c = a;
        a = b;
        b = c;
    }

    int gcd(const int& num, const int& denom){
        if(denom != 0){
            int a = num, b = denom;
            if(a < 0) a *= -1;
            if(b < 0) b *= -1;
            if(a == b)return a;
            else if(b > a) swap(a, b);
            while (a != b){
                while(a > b){
                    a -= b;
                    if(a == b) return b;
                }
                swap(a, b);
            }
        }
        return -1;
    }

    Rational::Rational(const int& numerator_, const int& denominator_){
        if(numerator_ == 0){
            denominator = 1;
            numerator = 0;
        } 
        else {
            int gcd_ = gcd(numerator_, denominator_);
            if(denominator_ < 0) {
                denominator = denominator_ * -1 / gcd_;
                numerator = numerator_ * -1 / gcd_;
            } else{
                denominator = denominator_ / gcd_;
                numerator = numerator_ / gcd_;
            }
        }
    }

    Rational& Rational::operator=(const Rational& rational){
        if(&rational == this) return *this;
        numerator = rational.numerator;
        denominator = rational.denominator;
        return *this;
    }

    int Rational::Numerator() const {
        return numerator;
    }

    int Rational::Denominator() const {
        return denominator;
    }

    ostream& operator<<(ostream& os, const Rational& rational){
        os << rational.numerator << "/" << rational.denominator;
        return os;
    }

    istream& operator>>(istream& is, Rational& rational){
        if(!is.eof()){
            int num = 0, denom = 0;
            char c;
            if(!(is >> num)) return is;
            if(is >> c) if(c != '/') return is;
            if(!(is >> denom)) return is;
            rational = Rational(num, denom);
        }
        return is;
    }

    bool operator==(const Rational& lhs, const Rational& rhs){
        if(lhs.denominator == rhs.denominator) 
            return lhs.numerator == rhs.numerator;
        else return false;
    }

    void cd(const Rational& lhs, const Rational& rhs, int& first, int& second, int& lcm_){
        int gcd_ = gcd(lhs.denominator, rhs.denominator);
        lcm_ = (rhs.denominator * lhs.denominator) / gcd_;
        first = lhs.numerator * (lcm_ / lhs.denominator);
        second = rhs.numerator * (lcm_ / rhs.denominator);
    }

    Rational operator+(const Rational& lhs, const Rational& rhs){
        int first = 0, second = 0, lcm_ = 0;
        cd(lhs, rhs, first, second, lcm_);
        return {first + second, lcm_};
    }

    Rational operator-(const Rational& lhs, const Rational& rhs){
        int first = 0, second = 0, lcm_ = 0;
        cd(lhs, rhs, first, second, lcm_);
        return {first - second, lcm_};
    }

    Rational operator*(const Rational& lhs, const Rational& rhs){
        int num = lhs.numerator * rhs.numerator;
        int denom = lhs.denominator * rhs.denominator;
        return Rational(num, denom);
    }

    Rational operator/(const Rational& lhs, const Rational& rhs){
        Rational a(rhs);
        swap(a.numerator, a.denominator);
        return lhs * a;
    }

    bool operator<(const Rational& lhs, const Rational& rhs){
        int first = 0, second = 0, lcm_ = 0;
        cd(lhs, rhs, first, second, lcm_);
        if(first < second) return true;
        else return false;
    }

    bool operator<=(const Rational& lhs, const Rational& rhs){
        if(!(lhs < rhs)){
            return lhs == rhs;
        }
        else return true;
    }