#include "../../Utils/TestRunner.h"

#include <list>
#include <numeric>
#include <vector>

using namespace std;

template <typename C, typename ForwardIt>
ForwardIt Loop(C& container, ForwardIt pos){
    return pos == container.end() ? container.begin() : pos;
}


template <typename RandomIt>
void MakeJosephusPermutation(RandomIt first, RandomIt last, uint32_t step_size) {
    list<typename RandomIt::value_type> pool;
    for(auto it = first; it != last; ++it){
        pool.push_back(std::move(*it));
    }

    auto curr_pos = pool.begin();
    while(!pool.empty()){
        *(first++) = std::move(*curr_pos);
        curr_pos = pool.erase(curr_pos);
        curr_pos = Loop(pool, curr_pos);
        for(int i = 0; i < step_size - 1; ++i){
            curr_pos = Loop(pool, ++curr_pos);
        }
    }
}

vector<int> MakeTestVector() {
    vector<int> numbers(10);
    iota(begin(numbers), end(numbers), 0);
    return numbers;
}

void TestIntVector() {
    const vector<int> numbers = MakeTestVector();
    {
        vector<int> numbers_copy = numbers;
        MakeJosephusPermutation(begin(numbers_copy), end(numbers_copy), 1);
        ASSERT_EQUAL(numbers_copy, numbers);
    }
    {
        vector<int> numbers_copy = numbers;
        MakeJosephusPermutation(begin(numbers_copy), end(numbers_copy), 3);
        ASSERT_EQUAL(numbers_copy, vector<int>({0, 3, 6, 9, 4, 8, 5, 2, 7, 1}));
    }
}

struct NoncopyableInt {
    int value;

    NoncopyableInt(int value) : value(value) {}

    NoncopyableInt(const NoncopyableInt&) = delete;
    NoncopyableInt& operator=(const NoncopyableInt&) = delete;

    NoncopyableInt(NoncopyableInt&&) = default;
    NoncopyableInt& operator=(NoncopyableInt&&) = default;
};

bool operator == (const NoncopyableInt& lhs, const NoncopyableInt& rhs) {
    return lhs.value == rhs.value;
}

ostream& operator << (ostream& os, const NoncopyableInt& v) {
    return os << v.value;
}

void TestAvoidsCopying() {
    vector<NoncopyableInt> numbers;
    numbers.emplace_back(1);
    numbers.emplace_back(2);
    numbers.emplace_back(3);
    numbers.emplace_back(4);
    numbers.emplace_back(5);

    MakeJosephusPermutation(begin(numbers), end(numbers), 2);

    vector<NoncopyableInt> expected;
    expected.emplace_back(1);
    expected.emplace_back(3);
    expected.emplace_back(5);
    expected.emplace_back(4);
    expected.emplace_back(2);

    ASSERT_EQUAL(numbers, expected);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestIntVector);
    RUN_TEST(tr, TestAvoidsCopying);
    return 0;
}
