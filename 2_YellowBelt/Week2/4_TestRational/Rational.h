#ifndef INC_8_RATIONAL_RATIONALFINAL_H
#define INC_8_RATIONAL_RATIONALFINAL_H

#include <numeric>
#include <tuple>
#include <sstream>
#include <exception>

class Rational final {
public:
    Rational() : numerator(0), denominator(1) {}
    Rational(const int& numerator_, const int& denominator_);

    Rational(const Rational &rational) = default;
    Rational &operator=(const Rational &rational) = default;

    int Numerator() const;
    int Denominator() const;

    ~Rational() = default;

private:
    int numerator;
    int denominator;
};

bool operator==(const Rational& lhs, const Rational& rhs);
bool operator!=(const Rational& lhs, const Rational& rhs);
bool operator < (const Rational& lhs, const Rational& rhs);
bool operator <= (const Rational& lhs, const Rational& rhs);
bool operator > (const Rational& lhs, const Rational& rhs);
bool operator >= (const Rational& lhs, const Rational& rhs);

Rational operator+(const Rational& lhs, const Rational& rhs);
Rational operator-(const Rational& lhs, const Rational& rhs);
Rational operator*(const Rational& lhs, const Rational& rhs);
Rational operator/(const Rational& lhs, const Rational& rhs);

std::ostream& operator<<(std::ostream& os, const Rational& rational);
std::istream& operator >> (std::istream& is, Rational& rational);


#endif //INC_8_RATIONAL_RATIONALFINAL_H
