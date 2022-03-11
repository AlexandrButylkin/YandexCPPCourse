#ifndef INC_8_RATIONAL_RATIONALFINAL_H
#define INC_8_RATIONAL_RATIONALFINAL_H

#include <numeric>
#include <tuple>
#include <sstream>
#include <exception>

class RationalFinal final {
public:
    RationalFinal() : numerator(0), denominator(1) {}
    RationalFinal(const int& numerator_, const int& denominator_);

    RationalFinal(const RationalFinal &rational) = default;
    RationalFinal &operator=(const RationalFinal &rational) = default;

    int Numerator() const;
    int Denominator() const;

    ~RationalFinal() = default;

private:
    int numerator;
    int denominator;
};

bool operator==(const RationalFinal& lhs, const RationalFinal& rhs);
bool operator < (const RationalFinal& lhs, const RationalFinal& rhs);
bool operator <= (const RationalFinal& lhs, const RationalFinal& rhs);
bool operator > (const RationalFinal& lhs, const RationalFinal& rhs);
bool operator >= (const RationalFinal& lhs, const RationalFinal& rhs);

RationalFinal operator+(const RationalFinal& lhs, const RationalFinal& rhs);
RationalFinal operator-(const RationalFinal& lhs, const RationalFinal& rhs);
RationalFinal operator*(const RationalFinal& lhs, const RationalFinal& rhs);
RationalFinal operator/(const RationalFinal& lhs, const RationalFinal& rhs);

std::ostream& operator<<(std::ostream& os, const RationalFinal& rational);
std::istream& operator >> (std::istream& is, RationalFinal& rational);


#endif //INC_8_RATIONAL_RATIONALFINAL_H
