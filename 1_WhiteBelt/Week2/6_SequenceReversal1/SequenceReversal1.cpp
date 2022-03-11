#include <iostream>
#include <vector>

void Reverse(std::vector<int> &vec) {
    if (vec.empty()) return;
    int beg = 0, end = vec.size() - 1;
    while (beg <= end) {
        std::swap(vec[beg], vec[end]);
        ++beg;
        --end;
    }
}

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    Reverse(vec);
    for (auto i: vec) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    return 0;
}