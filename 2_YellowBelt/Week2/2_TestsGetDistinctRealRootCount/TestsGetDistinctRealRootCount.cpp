#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <cmath>

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
