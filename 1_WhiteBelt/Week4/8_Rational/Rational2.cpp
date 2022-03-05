#include <iostream>
using namespace std;

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

class Rational {
public:
    Rational() : numerator(0), denominator(1) {}

    Rational(const int& numerator_, const int& denominator_) {
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

    Rational(const Rational& rational) : numerator(rational.numerator), denominator(rational.denominator) {}

    Rational& operator=(const Rational& rational){
        if(&rational == this) return *this;
        numerator = rational.numerator;
        denominator = rational.denominator;
        return *this;
    }

    int Numerator() const {
        return numerator;
    }

    int Denominator() const {
        return denominator;
    }

    friend bool operator==(const Rational& lhs, const Rational& rhs){
        if(lhs.denominator == rhs.denominator) 
            return lhs.numerator == rhs.numerator;
        else return false;
    }

    friend void cd(const Rational& lhs, const Rational& rhs, int& first, int& second, int& lcm_){
        int gcd_ = gcd(lhs.denominator, rhs.denominator);
        lcm_ = (rhs.denominator * lhs.denominator) / gcd_;
        first = lhs.numerator * (lcm_ / lhs.denominator);
        second = rhs.numerator * (lcm_ / rhs.denominator);
    }

    friend Rational operator+(const Rational& lhs, const Rational& rhs){
        int first = 0, second = 0, lcm_ = 0;
        cd(lhs, rhs, first, second, lcm_);
        return {first + second, lcm_};
    }

    friend Rational operator-(const Rational& lhs, const Rational& rhs){
        int first = 0, second = 0, lcm_ = 0;
        cd(lhs, rhs, first, second, lcm_);
        return {first - second, lcm_};
    }

    ~Rational(){};

private:
    int numerator;
    int denominator;
};

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

    /*{
        Rational r1(3, 6);
        Rational r2(2, 3);
        bool equal = r1 == r2;
        if (!equal) {
            cout << "3/6 == 2/3" << endl;
            return 1;
        }
    }*/

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

    /*{
        Rational a(-2, -3);
        Rational b(-4, -15);
        Rational c = a + b;
        Rational kek(-14, 15);
        bool equal = c == kek;
        if (!equal) {
            cout << "2/3 + 4/3 != 2" << endl;
            return 2;
        }
    }*/

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
