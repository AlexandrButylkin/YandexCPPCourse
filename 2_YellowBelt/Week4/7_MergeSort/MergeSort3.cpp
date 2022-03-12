#include <iostream>
#include<vector>

using std::cout;
using std::cin;
using std::endl;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    if(range_begin + 1 < range_end) {

        std::vector<typename RandomIt::value_type> vec_start(
                range_begin,
                range_end
        );

        RandomIt it1 = vec_start.begin() + (vec_start.end() - vec_start.begin()) / 3;
        RandomIt it2 = it1 + (vec_start.end() - vec_start.begin()) / 3;

        MergeSort(vec_start.begin(), it1);
        MergeSort(it1, it2);

        std::vector<typename RandomIt::value_type> vec;

        std::merge(
                vec_start.begin(),
                it1,
                it1,
                it2,
                back_inserter(vec)
        );

        MergeSort(it2, vec_start.end());

        std::merge(
                vec.begin(),
                vec.end(),
                it2,
                vec_start.end(),
                range_begin
        );

    }
}

int main() {
    std::vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1};
    MergeSort(begin(v), end(v));
    for (int x : v) {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}