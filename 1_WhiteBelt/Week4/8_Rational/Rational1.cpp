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

    ~Rational(){};

private:
    int numerator;
    int denominator;
};

int main() {

        
    return 0;
}
