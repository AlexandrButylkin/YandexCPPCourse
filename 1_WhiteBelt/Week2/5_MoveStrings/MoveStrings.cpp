#include <iostream>
#include <vector>

using std::vector;
using std::string;

void MoveStrings(vector<string>& vec1, vector<string>& vec2){
    vec2.reserve(vec1.size() + vec2.size());
    for(auto& str : vec1)
        vec2.emplace_back(std::move(str));
    vec1.clear();
}

int main(){

    vector<string> vec1 = {"str1", "str2", "str3", "str4", "str5"}, vec2 = {"str6", "str7"};

    MoveStrings(vec1, vec2);
    if(vec1.empty()){
        for(const auto& str : vec2){
            std::cout << str << std::endl;
        }
    }

    return 0;
}