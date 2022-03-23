#ifndef TEST_RUNNER_COURSERA_OPERATOROUT_H
#define TEST_RUNNER_COURSERA_OPERATOROUT_H

#include <vector>
#include <set>
#include <map>
#include <unordered_map>

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
    for (const auto& [k, v] : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << k << ": " << v;
    }
    return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const unordered_map<K, V>& m) {
    os << "{";
    bool first = true;
    for (const auto& [k, v] : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << k << ": " << v;
    }
    return os << "}";
}

#endif //TEST_RUNNER_COURSERA_OPERATOROUT_H
