#include <iostream>
#include <list>
#include <vector>

using ListIterator = std::list<int>::iterator;


int main() {
    std::list<int> lst;
    const int MAX_ATHLETES = 100'000;
    std::vector<ListIterator> athletes(MAX_ATHLETES + 1, lst.end());


    size_t count = 0;
    std::cin >> count;

    for(auto i = 0; i < count; ++i) {
        int curr = 0, before = 0;
        std::cin >> curr >> before;

        athletes[curr] = lst.insert(athletes[before], curr);
    }

    for(const auto& item : lst){
        std::cout << item << "\n";
    }

    return 0;
}
