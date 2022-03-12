#include "Rational.h"
#include "TestRunner.h"


using namespace std;

void TestConstructors(){

    {
        Rational r(3, 10);
        AssertEqual(r.Numerator(), 3, "204");
        AssertEqual(r.Denominator(), 10, "205");
    }

    {
        Rational r(8, 12);
        AssertEqual(r.Numerator(), 2, "210");
        AssertEqual(r.Denominator(), 3, "211");
    }

    {
        Rational r(-4, 6);
        AssertEqual(r.Numerator(), -2, "210");
        AssertEqual(r.Denominator(), 3, "211");
    }

    {
        Rational r(4, -6);
        AssertEqual(r.Numerator(), -2, "210");
        AssertEqual(r.Denominator(), 3, "211");
    }

    {
        Rational r(0, 15);
        AssertEqual(r.Numerator(), 0, "210");
        AssertEqual(r.Denominator(), 1, "211");
    }

    {
        Rational r;
        AssertEqual(r.Numerator(), 0, "210");
        AssertEqual(r.Denominator(), 1, "211");
    }

}

void TestOperatorsEqualPlusMinus(){
    {
        Rational r1(4, 6);
        Rational r2(2, 3);
        AssertEqual(r1, r2, "51");
    }

    {
        Rational r1(3, 6);
        Rational r2(2, 3);
        AssertEqual(r1 != r2, true, "57");
    }

    {
        Rational a(2, 3);
        Rational b(4, 15);
        Rational c = a + b;
        AssertEqual(c, Rational(14, 15), "63");
    }

    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a + b;
        AssertEqual(c, Rational(2, 1), "71");
    }

    {
        Rational a(5, 7);
        Rational b(2, 9);
        Rational c = a - b;
        AssertEqual(c, Rational(31, 63), "78");
    }
}

void TestOperatorMultiplyDivision(){
    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a * b;
        AssertEqual(c, Rational(8, 9), "88");
    }

    {
        Rational a(5, 4);
        Rational b(15, 8);
        Rational c = a / b;
        AssertEqual(c, Rational(2, 3), "94");
    }
}

void TestInputOutputOperator(){
    {
        ostringstream output;
        output << Rational(-6, 8);
        AssertEqual(output.str(), "-3/4", "102");
    }

    {
        istringstream input("5/7");
        Rational r;
        input >> r;
        AssertEqual(r, Rational(5, 7), "110");
    }

    {
        istringstream input("");
        Rational r;
        AssertEqual(!(input >> r), true, "116");
    }

    {
        istringstream input("5/7 10/8");
        Rational r1, r2;
        input >> r1 >> r2;
        AssertEqual(r1, Rational(5, 7), "123");
        AssertEqual(r2, Rational(5, 4), "124");
    }

    {
        istringstream input1("1*2"), input2("1/"), input3("/4");
        Rational r1, r2, r3;
        input1 >> r1;
        input2 >> r2;
        input3 >> r3;
        AssertEqual(r1, Rational(), "134");
        AssertEqual(r2, Rational(), "135");
        AssertEqual(r3, Rational(), "136");
    }

    {
        istringstream input("2/4/6/8");
        Rational r1;
        input >> r1;
        AssertEqual(r1, Rational(1, 2), "145");
    }
}

void TestComparisonOperator() {
    {
        const set<Rational> rs = {
                {1, 2},
                {1, 25},
                {3, 4},
                {3, 4},
                {1, 2}
        };
        AssertEqual(rs.size(), 3, "150");

        vector<Rational> v;
        vector<Rational> expected = {
                {1, 25},
                {1, 2},
                {3, 4}
        };
        for (auto x : rs) {
            v.push_back(x);
        }
        AssertEqual(v, expected, "167");
    }

    {
        map<Rational, int> count;
        ++count[{1, 2}];
        ++count[{1, 2}];
        ++count[{2, 3}];
        AssertEqual(count.size(), 2, "175");
    }
};

void TestExeption () {
    Rational r(1, 0);
    auto x = Rational(1, 2) / Rational(0, 1);
}

int main() {
    TestRunner runner;
    runner.RunTest(TestConstructors, "TestConstructors");
    runner.RunTest(TestOperatorsEqualPlusMinus, "TestOperatorsEqualPlusMinus");
    runner.RunTest(TestOperatorMultiplyDivision, "TestOperatorMultiplyDivision");
    runner.RunTest(TestInputOutputOperator, "TestInputOutputOperator");
    runner.RunTest(TestComparisonOperator, "TestComparisonOperator");
    runner.RunTest(TestExeption, "TestExeption");
    return 0;
}
