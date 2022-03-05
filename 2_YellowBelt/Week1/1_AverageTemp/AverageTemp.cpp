#include <iostream>
#include <vector>

int main() {
    long long n = 0, sum = 0;
    std::cin >> n;
    std::vector<int> vec(n);

    for(auto& item : vec){
        std::cin >> item;
        sum += item;
    }

    long long av = sum / n;
    std::vector<int> vec2;

    for(size_t i = 0; i < vec.size(); ++i){
        if(vec[i] > av){
            vec2.emplace_back(i);
        }
    }

    std::cout << vec2.size() << "\n";

    for(const auto& item : vec2){
        std::cout << item << " ";
    }
    std::cout << std::endl;
    return 0;
}