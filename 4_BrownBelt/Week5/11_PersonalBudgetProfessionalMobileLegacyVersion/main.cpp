#include <array>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <optional>
#include <sstream>
#include <stdexcept>
#include <string_view>
#include <utility>

using namespace std;

pair<string_view, optional<string_view>> SplitTwoStrict(string_view s, string_view delimiter = " ") {
    const size_t pos = s.find(delimiter);
    if (pos == s.npos) {
        return {s, nullopt};
    } else {
        return {s.substr(0, pos), s.substr(pos + delimiter.length())};
    }
}

pair<string_view, string_view> SplitTwo(string_view s, string_view delimiter = " ") {
    const auto[lhs, rhs_opt] = SplitTwoStrict(s, delimiter);
    return {lhs, rhs_opt.value_or("")};
}

string_view ReadToken(string_view &s, string_view delimiter = " ") {
    const auto[lhs, rhs] = SplitTwo(s, delimiter);
    s = rhs;
    return lhs;
}

int ConvertToInt(string_view str) {
    // use std::from_chars when available to git rid of string copy
    size_t pos;
    const int result = stoi(string(str), &pos);
    if (pos != str.length()) {
        std::stringstream error;
        error << "string " << str << " contains " << (str.length() - pos) << " trailing chars";
        throw invalid_argument(error.str());
    }
    return result;
}

template<typename Number>
void ValidateBounds(Number number_to_check, Number min_value, Number max_value) {
    if (number_to_check < min_value || number_to_check > max_value) {
        std::stringstream error;
        error << number_to_check << " is out of [" << min_value << ", " << max_value << "]";
        throw out_of_range(error.str());
    }
}

class Date {
public:
    static Date FromString(string_view str) {
        const int year = ConvertToInt(ReadToken(str, "-"));
        const int month = ConvertToInt(ReadToken(str, "-"));
        ValidateBounds(month, 1, 12);
        const int day = ConvertToInt(str);
        ValidateBounds(day, 1, 31);
        return {year, month, day};
    }

    // Weird legacy, can't wait for std::chrono::year_month_day
    time_t AsTimestamp() const {
        std::tm t;
        t.tm_sec  = 0;
        t.tm_min  = 0;
        t.tm_hour = 0;
        t.tm_mday = day_;
        t.tm_mon  = month_ - 1;
        t.tm_year = year_ - 1900;
        t.tm_isdst = 0;
        return mktime(&t);
    }

private:
    int year_;
    int month_;
    int day_;

    Date(int year, int month, int day)
            : year_(year), month_(month), day_(day)
    {}
};

int ComputeDaysDiff(const Date& date_to, const Date& date_from) {
    const time_t timestamp_to = date_to.AsTimestamp();
    const time_t timestamp_from = date_from.AsTimestamp();
    static constexpr int SECONDS_IN_DAY = 60 * 60 * 24;
    return (timestamp_to - timestamp_from) / SECONDS_IN_DAY;
}

static const Date START_DATE = Date::FromString("2000-01-01");
static const Date END_DATE = Date::FromString("2100-01-01");
static const size_t DAY_COUNT = ComputeDaysDiff(END_DATE, START_DATE);
static const size_t DAY_COUNT_P2 = 1 << 16;
static const size_t VERTEX_COUNT = DAY_COUNT_P2 * 2;

size_t ComputeDayIndex(const Date& date) {
    return ComputeDaysDiff(date, START_DATE);
}


array<double, VERTEX_COUNT> tree_values, tree_add, tree_factor, tree_del, tree_values_sp;

void Init() {
    tree_values.fill(0);
    tree_add.fill(0);
    tree_factor.fill(1);
}

void Push(size_t v, size_t l, size_t r) {
    for (size_t w = v * 2; w <= v * 2 + 1; ++w) {
        if (w < VERTEX_COUNT) {
            tree_factor[w] *= tree_factor[v];
            (tree_add[w] *= tree_factor[v]) += tree_add[v];
            tree_del[w] += tree_del[v];
            (tree_values[w] *= tree_factor[v]) += tree_add[v] * (r - l) / 2;
            tree_values_sp[w] += tree_del[v] * (r - l) / 2;
        }
    }
    tree_factor[v] = 1;
    tree_add[v] = 0;
    tree_del[v] = 0;
}

double ComputeSum(size_t v, size_t l, size_t r, size_t ql, size_t qr) {
    if (v >= VERTEX_COUNT || qr <= l || r <= ql) {
        return 0;
    }
    Push(v, l, r);
    if (ql <= l && r <= qr) {
        return tree_values[v] - tree_values_sp[v];
    }
    return ComputeSum(v * 2, l, (l + r) / 2, ql, qr)
           + ComputeSum(v * 2 + 1, (l + r) / 2, r, ql, qr);
}

void Add(size_t v, size_t l, size_t r, size_t ql, size_t qr, double value) {
    if (v >= VERTEX_COUNT || qr <= l || r <= ql) {
        return;
    }
    Push(v, l, r);
    if (ql <= l && r <= qr) {
        tree_add[v] += value;
        tree_values[v] += value * (r - l);
        return;
    }
    Add(v * 2, l, (l + r) / 2, ql, qr, value);
    Add(v * 2 + 1, (l + r) / 2, r, ql, qr, value);
    tree_values[v] =
            (v * 2 < VERTEX_COUNT ? tree_values[v * 2] : 0)
            + (v * 2 + 1 < VERTEX_COUNT ? tree_values[v * 2 + 1] : 0);
}

void Del(size_t v, size_t l, size_t r, size_t ql, size_t qr, double value) {
    if (v >= VERTEX_COUNT || qr <= l || r <= ql) {
        return;
    }
    Push(v, l, r);
    if (ql <= l && r <= qr) {
        tree_del[v] += value;
        tree_values_sp[v] += value * (r - l);
        return;
    }
    Del(v * 2, l, (l + r) / 2, ql, qr, value);
    Del(v * 2 + 1, (l + r) / 2, r, ql, qr, value);
    tree_values_sp[v] =
            (v * 2 < VERTEX_COUNT ? tree_values_sp[v * 2] : 0)
            + (v * 2 + 1 < VERTEX_COUNT ? tree_values_sp[v * 2 + 1] : 0);
}

void Multiply(size_t v, size_t l, size_t r, size_t ql, size_t qr, double percent) {
    if (v >= VERTEX_COUNT || qr <= l || r <= ql) {
        return;
    }
    Push(v, l, r);
    if (ql <= l && r <= qr) {
        tree_factor[v] *= percent;
        tree_add[v] *= percent;
        tree_values[v] *= percent;
        return;
    }
    Multiply(v * 2, l, (l + r) / 2, ql, qr, percent);
    Multiply(v * 2 + 1, (l + r) / 2, r, ql, qr, percent);
    tree_values[v] =
            (v * 2 < VERTEX_COUNT ? tree_values[v * 2] : 0)
            + (v * 2 + 1 < VERTEX_COUNT ? tree_values[v * 2 + 1] : 0);
}


int main() {
    cout.precision(25);
    assert(DAY_COUNT <= DAY_COUNT_P2 && DAY_COUNT_P2 < DAY_COUNT * 2);

    Init();

    int q;
    cin >> q;

    for (int i = 0; i < q; ++i) {
        string query_type;
        cin >> query_type;

        string date_from_str, date_to_str;
        cin >> date_from_str >> date_to_str;

        auto idx_from = ComputeDayIndex(Date::FromString(date_from_str));
        auto idx_to = ComputeDayIndex(Date::FromString(date_to_str)) + 1;

        if (query_type == "ComputeIncome") {
            cout << ComputeSum(1, 0, DAY_COUNT_P2, idx_from, idx_to) << endl;
        } else if (query_type == "PayTax") {
            double percent;
            std::cin >> percent;
            percent = 1.0 - percent / 100;
            Multiply(1, 0, DAY_COUNT_P2, idx_from, idx_to, percent);
        } else if (query_type == "Earn") {
            double value;
            cin >> value;
            Add(1, 0, DAY_COUNT_P2, idx_from, idx_to, value / (idx_to - idx_from));
        } else if (query_type == "Spend") {
            double value;
            std::cin >> value;
            Del(1, 0, DAY_COUNT_P2, idx_from, idx_to, value / (idx_to - idx_from));
        }
    }

    return 0;
}
