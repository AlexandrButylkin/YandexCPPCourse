#include <iostream>
#include "TestRunner.h"


using namespace std;

int GetDistinctRealRootCount(double a, double b, double c) {
    double D = b * b - 4 * a * c;
    if (D > 0) {
        return 2;
    } else if (D == 0) {
        return 1;
    } else {
        return 0;
    }
}

void TestCount(){
    {
        double a = 2.0;
        double b = 2.0;
        double c = -1.0;
        int expected = 2;
        AssertEqual(GetDistinctRealRootCount(a, b, c), expected, "114");
    }

    {
        double a = 1.0;
        double b = 2.0;
        double c = 1.0;
        int expected = 1;
        AssertEqual(GetDistinctRealRootCount(a, b, c), expected, "122");
    }

    {
        double a = 8.0;
        double b = 2.0;
        double c = 1.0;
        int expected = 0;
        AssertEqual(GetDistinctRealRootCount(a, b, c), expected, "130");
    }
}

void TestZeroCoefs(){
    {
        double a = 0.0;
        double b = 2.0;
        double c = -1.0;
        int expected = 1;
        AssertEqual(GetDistinctRealRootCount(a, b, c), expected, "140");
    }

    {
        double a = 1.0;
        double b = 0.0;
        double c = 1.0;
        int expected = 0;
        AssertEqual(GetDistinctRealRootCount(a, b, c), expected, "148");
    }

    {
        double a = 1.0;
        double b = 0.0;
        double c = -1.0;
        int expected = 2;
        AssertEqual(GetDistinctRealRootCount(a, b, c), expected, "156");
    }

    {
        double a = 1.0;
        double b = 2.0;
        double c = 0.0;
        int expected = 2;
        AssertEqual(GetDistinctRealRootCount(a, b, c), expected, "164");
    }

    {
        double a = 0.0;
        double b = 0.0;
        double c = 2.0;
        int expected = 0;
        AssertEqual(GetDistinctRealRootCount(a, b, c), expected, "172");
    }
}

int main() {
    TestRunner runner;
    runner.RunTest(TestCount, "Test Count");
    runner.RunTest(TestZeroCoefs, "Test Zero Coefs");
    return 0;
}
