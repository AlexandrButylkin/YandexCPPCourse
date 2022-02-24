#include <iostream>
#include <sstream>
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
        Rational a(rhs);
        swap(a.numerator, a.denominator);
        return lhs * a;
    }

    ~Rational(){};

private:
    int numerator;
    int denominator;
};

// Вставьте сюда реализацию operator == для класса Rational из второй части

// Реализуйте для класса Rational операторы << и >>

int main() {
    /*{
        istringstream input("");
        Rational r;
        input >> r;
        bool equal = r == Rational();
        if (!equal) {
            cout << "pustota " << r << endl;
            return 2;
        }
    }

    {
        ostringstream output;
        output << Rational(-6, 8);
        //std::cout << Rational(-6, 8);
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
    }*/

    {
        istringstream input(" ");
        Rational r;
        int b = input.gcount();
        //bool c = input.eofbit();
        bool a = !(input >> r);
        bool correct = !(input >> r);
        if (!correct) {
            cout << "Read from empty stream works incorrectly" << endl;
            return 3;
        }
    }

    /*{
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
    }*/

    cout << "OK" << endl;
    return 0;
}
