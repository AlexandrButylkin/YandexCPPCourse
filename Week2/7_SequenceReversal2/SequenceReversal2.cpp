#include <iostream>
#include <vector>

std::vector<int> Reversed(const std::vector<int>& vec){
    std::vector<int> ans;
    if(vec.empty()){
        return ans;
    }
    std::vector<int>::const_iterator end = vec.end() - 1;
    while(end >= vec.begin()){
        ans.push_back(*end);
        end--;
    }
    return ans;
}

int main(){
    std::vector<int> vec = {2};
    vec = Reversed(vec);
    for(auto i : vec){
        std::cout << i << " ";
    }
    std::cout << std::endl;
    return 0;
}