#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

int main(){
    int n = 0;
    std::cin >> n;
    std::vector<std::string> vec(n);
    for(auto& i : vec){
        std::cin >> i;
    }
    std::sort(vec.begin(), vec.end(), [](std::string a, std::string b){
        for(size_t i = 0; i < a.size(); ++i)
            a[i] = tolower(a[i]);
        for(size_t i = 0; i < b.size(); ++i)
            b[i] = tolower(b[i]);
        return a < b;
        });
    std::cout << std::endl;
    for(const auto& i : vec){
        std::cout << i << " ";
    }
    std::cout << std::endl;
    return 0;
}