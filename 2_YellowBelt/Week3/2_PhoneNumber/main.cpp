#include <iostream>
#include "PhoneNumber.h"
#include "TestRunner.h"

void TestCorrectNumber() {
    {
        PhoneNumber pn("+7-495-111-22-33");
        AssertEqual(pn.GetInternationalNumber(), "+7-495-111-22-33");
        AssertEqual(pn.GetCountryCode(), "7");
        AssertEqual(pn.GetCityCode(), "495");
        AssertEqual(pn.GetLocalNumber(), "111-22-33");
    }

    {
        PhoneNumber pn("+7-495-1112233");
        AssertEqual(pn.GetInternationalNumber(), "+7-495-1112233");
        AssertEqual(pn.GetCountryCode(), "7");
        AssertEqual(pn.GetCityCode(), "495");
        AssertEqual(pn.GetLocalNumber(), "1112233");
    }

    {
        PhoneNumber pn("+323-22-460002");
        AssertEqual(pn.GetInternationalNumber(), "+323-22-460002");
        AssertEqual(pn.GetCountryCode(), "323");
        AssertEqual(pn.GetCityCode(), "22");
        AssertEqual(pn.GetLocalNumber(), "460002");
    }

    {
        PhoneNumber pn("+1-2-main-cpp");
        AssertEqual(pn.GetInternationalNumber(), "+1-2-main-cpp");
        AssertEqual(pn.GetCountryCode(), "1");
        AssertEqual(pn.GetCityCode(), "2");
        AssertEqual(pn.GetLocalNumber(), "main-cpp");
    }
}

void TestIncorrectNumber1() {
    {
        PhoneNumber pn("1-2-333");
    }
}

void TestIncorrectNumber2() {
    {
        PhoneNumber pn("+7-1233");
    }
}

void TestIncorrectNumber3() {
    {
        PhoneNumber pn("+74951112233");
    }
}

int main() {
    TestRunner tr;
    tr.RunTest(TestCorrectNumber, "TestCorrectNumber");
    tr.RunTest(TestIncorrectNumber1, "TestIncorrectNumber1");
    tr.RunTest(TestIncorrectNumber2, "TestIncorrectNumber2");
    tr.RunTest(TestIncorrectNumber3, "TestIncorrectNumber3");
    return 0;
}
