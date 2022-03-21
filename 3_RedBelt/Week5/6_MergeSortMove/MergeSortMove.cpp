#include "../../Utils/TestRunner.h"
#include <algorithm>
#include <vector>

using namespace std;



template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    if(range_begin + 1 < range_end) {

        std::vector<typename RandomIt::value_type> vec_start(
                make_move_iterator(range_begin),
                make_move_iterator(range_end)
        );

        RandomIt it1 = vec_start.begin() + (vec_start.end() - vec_start.begin()) / 3;
        RandomIt it2 = it1 + (vec_start.end() - vec_start.begin()) / 3;

        MergeSort(vec_start.begin(), it1);
        MergeSort(it1, it2);

        std::vector<typename RandomIt::value_type> vec;

        std::merge(
                make_move_iterator(vec_start.begin()),
                make_move_iterator(it1),
                make_move_iterator(it1),
                make_move_iterator(it2),
                back_inserter(vec)
        );

        MergeSort(it2, vec_start.end());

        std::merge(
                make_move_iterator(vec.begin()),
                make_move_iterator(vec.end()),
                make_move_iterator(it2),
                make_move_iterator(vec_start.end()),
                range_begin
        );

    }
}

void TestIntVector() {
    vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
    MergeSort(begin(numbers), end(numbers));
    ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestIntVector);
    return 0;
}
