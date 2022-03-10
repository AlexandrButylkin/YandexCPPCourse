#include <iostream>
#include <vector>

std::vector<int> Reversed(const std::vector<int>& vec){
    if(vec.empty()) return {};

    std::vector<int> ans;
    ans.reserve(vec.size());

    for(int i = vec.size() - 1; i >= 0; --i){
        ans.emplace_back(vec[i]);
    }

    return ans;
}

int main(){
    std::vector<int> vec = {2, 3, 4, 5, 6};
    for(auto i : Reversed(vec)){
        std::cout << i << " ";
    }
    for(auto i : vec){
        std::cout << i << " ";
    }
    std::cout << std::endl;
    return 0;
}