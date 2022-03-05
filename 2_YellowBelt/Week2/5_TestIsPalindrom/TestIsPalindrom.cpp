#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
    os << "{";
    bool first = true;
    for (const auto& kv : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
    if (t != u) {
        ostringstream os;
        os << "Assertion failed: " << t << " != " << u;
        if (!hint.empty()) {
            os << " hint: " << hint;
        }
        throw runtime_error(os.str());
    }
}

void Assert(bool b, const string& hint) {
    AssertEqual(b, true, hint);
}

class TestRunner {
public:
    template <class TestFunc>
    void RunTest(TestFunc func, const string& test_name) {
        try {
            func();
            cerr << test_name << " OK" << endl;
        } catch (exception& e) {
            ++fail_count;
            cerr << test_name << " fail: " << e.what() << endl;
        } catch (...) {
            ++fail_count;
            cerr << "Unknown exception caught" << endl;
        }
    }

    ~TestRunner() {
        if (fail_count > 0) {
            cerr << fail_count << " unit tests failed. Terminate" << endl;
            exit(1);
        }
    }

private:
    int fail_count = 0;
};

bool IsPalindrom(const string& str) {
    // Вы можете вставлять сюда различные реализации функции,
    // чтобы проверить, что ваши тесты пропускают корректный код
    // и ловят некорректный
}

void TestEmpty(){
    string str= "";
    AssertEqual(IsPalindrom(str), true, "104");
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
