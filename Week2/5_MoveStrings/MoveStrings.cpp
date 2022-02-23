#include <iostream>
#include <vector>

void MoveStrings(std::vector<std::string>& vec1, std::vector<std::string>& vec2){
    for(auto str : vec1)
        vec2.push_back(str);
    vec1.clear();
}

int main(){

std::vector<std::string> vec1 = {"kek", "lol", "mem", "krinj", "booling"}, vec2 = {"krash", "fake"};
    MoveStrings(vec1, vec2);
    for(auto str : vec1){
        std::cout << str << std::endl;
    }
    for(auto str : vec2){
        std::cout << str << std::endl;
    }
    return 0;
}