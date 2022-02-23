#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;

class Rational {
public:
    Rational() : numerator(0), denominator(1) {}
    Rational(const int& numerator_, const int& denominator_);
    Rational(const Rational& rational) : numerator(rational.numerator), denominator(rational.denominator) {}
    Rational& operator=(const Rational& rational);

    int Numerator() const;
    int Denominator() const;

    friend ostream& operator<<(ostream& os, const Rational& rational);
    friend istream& operator>>(istream& is, Rational& rational);

    friend void cd(const Rational& lhs, const Rational& rhs, int& first, int& second, int& lcm_);
    friend Rational operator+(const Rational& lhs, const Rational& rhs);
    friend Rational operator-(const Rational& lhs, const Rational& rhs);
    friend Rational operator*(const Rational& lhs, const Rational& rhs);
    friend Rational operator/(const Rational& lhs, const Rational& rhs);

    friend bool operator==(const Rational& lhs, const Rational& rhs);
    friend bool operator<(const Rational& lhs, const Rational& rhs);
    friend bool operator<=(const Rational& lhs, const Rational& rhs);

    ~Rational(){};

private:
    int numerator;
    int denominator;
};