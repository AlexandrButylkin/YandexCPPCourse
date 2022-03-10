#include <iostream>
#include <algorithm>
#include <vector>

std::string StringToLower(std::string str){
    for(char& c : str){
        c = tolower(c);
    }
    return str;
}

int main(){
    int n = 0;
    std::cin >> n;

    std::vector<std::string> vec(n);
    for(auto& i : vec){
        std::cin >> i;
    }

    std::sort(vec.begin(), vec.end(), [](std::string a, std::string b){
        return StringToLower(std::move(a)) < StringToLower(std::move(b));
    });

    std::cout << std::endl;
    for(const auto& i : vec){
        std::cout << i << " ";
    }
    std::cout << std::endl;

    return 0;
}