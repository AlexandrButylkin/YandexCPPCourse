#ifndef TEST_RUNNER_COURSERA_TEST_RUNER_H
#define TEST_RUNNER_COURSERA_TEST_RUNER_H

#include <sstream>
#include <stdexcept>
#include <iostream>
#include <string>

#include "OperatorsOut.h"

using namespace std;

#define ASSERT_EQUAL(x, y) {                \
  ostringstream osForTests;                 \
  osForTests << #x << " != " << #y << ", "  \
    << __FILE__ << ":" << __LINE__;         \
  AssertEqual(x, y, osForTests.str());      \
}

#define ASSERT(x) {                     \
  ostringstream osForTests;             \
  osForTests << #x << " is false, "     \
    << __FILE__ << ":" << __LINE__;     \
  Assert(x, osForTests.str());          \
}

#define RUN_TEST(tr, func)              \
  tr.RunTest(func, #func)

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
  if (!(t == u)) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty()) {
       os << " hint: " << hint;
    }
    throw runtime_error(os.str());
  }
}

inline void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name);

  ~TestRunner();

private:
  int fail_count = 0;
};

template <class TestFunc>
void TestRunner::RunTest(TestFunc func, const string &test_name) {
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

TestRunner::~TestRunner() {
    if (fail_count > 0) {
        cerr << fail_count << " unit tests failed. Terminate" << endl;
        exit(1);
    }
}



#endif //TEST_RUNNER_COURSERA_TEST_RUNER_H
