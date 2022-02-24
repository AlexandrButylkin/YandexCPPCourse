#include <iostream>
#include <exception>
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
        if(denominator_ == 0){
            throw invalid_argument("Invalid argument");
        }
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

    friend ostream& operator<<(ostream& os, const Rational& rational){
        os << rational.numerator << "/" << rational.denominator;
        return os;
    }

    friend istream& operator>>(istream& is, Rational& rational){
        int num = 0, denom = 0;
        char c;
        if(!(is >> num)) return is;
        if(is >> c) if(c != '/') return is;
        if(!(is >> denom)) return is;
        if(denom == 0) throw invalid_argument("Invalid argument");
        rational = Rational(num, denom);
        return is;
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

    friend Rational operator*(const Rational& lhs, const Rational& rhs){
        int num = lhs.numerator * rhs.numerator;
        int denom = lhs.denominator * rhs.denominator;
        return Rational(num, denom);
    }

    friend Rational operator/(const Rational& lhs, const Rational& rhs){
        if(rhs.numerator == 0){
            throw domain_error("Division by zero");
        }
        Rational a(rhs);
        swap(a.numerator, a.denominator);
        return lhs * a;
    }


    friend bool operator<(const Rational& lhs, const Rational& rhs){
        int first = 0, second = 0, lcm_ = 0;
        cd(lhs, rhs, first, second, lcm_);
        if(first < second) return true;
        else return false;
    }

    friend bool operator<=(const Rational& lhs, const Rational& rhs){
        if(!(lhs < rhs)){
            return lhs == rhs;
        }
        else return true;
    }

    ~Rational(){};

private:
    int numerator;
    int denominator;
};

int main() {
    Rational first, second;
        char operation = '\000';
            try {
                std::cin >> first >> operation >> second;
            } catch (invalid_argument& str) {
                std::cout << str.what() << std::endl;
                return 1;
            }

            try {
                if(operation == '+'){
                    std::cout << first + second << std::endl;
                }
                else if(operation == '-'){
                    std::cout << first - second << std::endl;
                }
                else if(operation == '*'){
                    std::cout << first * second << std::endl;
                }
                else if(operation == '/'){
                    std::cout << first / second << std::endl;
                }

            } catch (domain_error& str) {
                std::cout << str.what() << std::endl;
                return 2;
            }
    return 0;
}
