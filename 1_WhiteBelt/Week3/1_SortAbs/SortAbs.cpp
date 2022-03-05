#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

int main(){
    int n = 0;
    std::cin >> n;
    std::vector<int> vec(n);
    for(auto& i : vec){
        std::cin >> i;
    }
    std::sort(vec.begin(), vec.end(), [](int a, int b){return abs(a) < abs(b);});
    std::cout << std::endl;
    for(const auto& i : vec){
        std::cout << i << " ";
    }
    std::cout << std::endl;
    return 0;
}