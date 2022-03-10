#include <iostream>
#include <vector>
#include <numeric>

std::vector<int> DaysTmp(const std::vector<int>& vec){
    if (vec.empty()) return {};

    int sum = std::accumulate(vec.begin(), vec.end(), 0) / static_cast<int>(vec.size());
    std::vector<int> ans;
    ans.reserve(vec.size());


    for(auto i = 0; i < vec.size(); ++i){
        if(vec[i] > sum){
            ans.emplace_back(i);
        }
    }

    return ans;
}

int main(){
    int n = 0;
    std::cin >> n;

    std::vector<int> vec(n);
    for(auto& item : vec){
        std::cin >> item;
    }

    auto days = DaysTmp(vec);
    std::cout << days.size() << std::endl;
    for(auto i : days){
        std::cout << i << " ";
    }
    std::cout << std::endl;
    return 0;
}