#include <iostream>
#include "Rectangle.h"
#include "TestRunner.h"

void TestConstructor() {
    {
        Rectangle r(5, 10);
        AssertEqual(r.GetWidth(), 5);
        AssertEqual(r.GetHeight(), 10);
    }

    {
        Rectangle r(1, 0);
        AssertEqual(r.GetWidth(), 1);
        AssertEqual(r.GetHeight(), 0);
    }

    {
        Rectangle r(0, 1);
        AssertEqual(r.GetWidth(),  0);
        AssertEqual(r.GetHeight(), 1);
    }

    {
        Rectangle r(0, 0);
        AssertEqual(r.GetWidth(), 0);
        AssertEqual(r.GetHeight(), 0);
    }
}

void TestPerimeter() {
    {
        Rectangle r(5, 10);
        AssertEqual(r.GetPerimeter(), 30);
    }

    {
        Rectangle r(1, 0);
        AssertEqual(r.GetPerimeter(), 2);
    }

    {
        Rectangle r(0, 1);
        AssertEqual(r.GetPerimeter(), 2);
    }

    {
        Rectangle r(0, 0);
        AssertEqual(r.GetPerimeter(), 0);
    }
}

void TestArea() {
    {
        Rectangle r(5, 10);
        AssertEqual(r.GetArea(), 50);
    }

    {
        Rectangle r(1, 0);
        AssertEqual(r.GetArea(), 0);
    }

    {
        Rectangle r(0, 1);
        AssertEqual(r.GetArea(), 0);
    }

    {
        Rectangle r(0, 0);
        AssertEqual(r.GetArea(), 0);
    }
}

int main() {
    TestRunner tr;
    tr.RunTest(TestConstructor, "TestConstructor");
    tr.RunTest(TestPerimeter, "TestPerimeter");
    tr.RunTest(TestArea, "TestArea");
    return 0;
}
