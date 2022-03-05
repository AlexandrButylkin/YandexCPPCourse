#include <iostream>
#include<vector>

using std::cout;
using std::cin;
using std::endl;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end){
    if(range_begin + 1 == range_end){
        return;
    }

    std::vector<typename RandomIt::value_type> vec(
            range_begin,
            range_end
            );

    RandomIt range_mid = vec.begin() + (vec.end() - vec.begin()) / 2;

    MergeSort(vec.begin(), range_mid);
    MergeSort(range_mid, vec.end());

    std::merge(
            vec.begin(),
            range_mid,
            range_mid,
            vec.end(),
            range_begin
            );
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
