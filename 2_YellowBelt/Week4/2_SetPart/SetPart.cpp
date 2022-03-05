#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

using IT = std::vector<int>::const_iterator;

template <typename T>
std::vector<T> FindGreaterElements(const std::set<T>& elements, const T& border){
    std::vector<T> vec;
    for(const auto& item : elements){
        if(item > border){
            vec.push_back(std::move(item));
        }
    }
    return vec;
}

int main(){
    for (int x : FindGreaterElements(set<int>{6,7,8,2, 3,9,0}, 5)) {
        cout << x << " ";
    }
    cout << endl;

    string to_find = "C";
    cout << FindGreaterElements(set<string>{"C", "C++"}, to_find).size() << endl;
    return 0;
}