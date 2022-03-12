#include <iostream>
#include "TestRunner.h"

using namespace std;

bool IsPalindrom(const std::string& str){
    int beg = 0, end = str.size() - 1;
    while(beg <= end){
        if(str[beg] != str[end]) return false;
        --end;
        ++beg;
    }
    return true;
}

void TestEmpty(){
    string str;
    AssertEqual(IsPalindrom(str), true);
}

void TestPalindrom(){
    {
        string str = "aba";
        AssertEqual(IsPalindrom(str), true);
    }

    {
        string str = "aaa";
        AssertEqual(IsPalindrom(str), true);
    }

    {
        string str = "abba";
        AssertEqual(IsPalindrom(str), true);
    }

    {
        string str = "abbbbbbbbbba";
        AssertEqual(IsPalindrom(str), true);
    }

    {
        string str = "aa a aa";
        AssertEqual(IsPalindrom(str), true);
    }

    {
        string str = " b ";
        AssertEqual(IsPalindrom(str), true);
    }

    {
        string str = "b";
        AssertEqual(IsPalindrom(str), true);
    }
}

void TestNoPalindrom(){
    {
        string str = " b";
        AssertEqual(IsPalindrom(str), false);
    }

    {
        string str = " b b";
        AssertEqual(IsPalindrom(str), false);
    }

    {
        string str = "qwe";
        AssertEqual(IsPalindrom(str), false);
    }

    {
        string str = "PPppa";
        AssertEqual(IsPalindrom(str), false);
    }

    {
        string str = "rut";
        AssertEqual(IsPalindrom(str), false);
    }

    {
        string str = "12 1";
        AssertEqual(IsPalindrom(str), false);
    }
}

int main() {
    TestRunner runner;
    runner.RunTest(TestEmpty, "Empty");
    runner.RunTest(TestPalindrom, "Palindrom");
    runner.RunTest(TestNoPalindrom, "NoPalindrom");
    return 0;
}
