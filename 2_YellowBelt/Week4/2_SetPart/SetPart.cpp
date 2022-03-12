#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

template <typename T>
std::vector<T> FindGreaterElements(const std::set<T>& elements, const T& border){
    auto iter = elements.begin();
    while(*iter > border && iter != elements.end()){
        ++iter;
    }
    return {elements.begin(), iter};
}

int main(){
    for (int x : FindGreaterElements(std::set<int>{6,7,8,2,3,9,0}, 5)) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    std::string to_find = "C";
    std::cout << FindGreaterElements(std::set<std::string>{"C", "C++"}, to_find).size() << std::endl;
    return 0;
}