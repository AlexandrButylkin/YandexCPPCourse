#include <iostream>
#include <vector>

template <typename T>
void input(std::vector<T>& vec, int n){
    std::cin >> n;
    vec.resize(n);
    for(T& i : vec)
        std::cin >> i;
}

std::vector<int> daysTmp(std::vector<int>& vec){
    std::vector<int> ans;
    if(!vec.empty()){
        int sum = 0;
        for(int i : vec)
            sum += i;
        sum = sum / vec.size();
        for(size_t i = 0; i < vec.size(); i++)
            if(vec[i] > sum)
                ans.push_back(i);
    }
    return ans;
}

template <typename T>
void output_vec(const std::vector<T> vec){
    std::cout << vec.size() << std::endl; 
    for(T i : vec)
        std::cout << i << " ";
    std::cout << std::endl;
}

void output_vec(const std::vector<std::string> vec){
    std::cout << vec.size() << std::endl; 
    for(auto i : vec){
        std::cout << i << std::endl;
    }
}

int main(){
    int n = 0;
    std::vector<int> vec;
    input(vec, n);
    output_vec(daysTmp(vec));
    return 0;
}