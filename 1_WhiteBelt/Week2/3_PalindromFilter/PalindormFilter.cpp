#include <iostream>
#include <vector>

using std::string;
using std::vector;

bool IsPalindrom(const string& str){
    int beg = 0, end = str.size() - 1;
    while(beg <= end){
        if(str[beg] != str[end]) return false;
        --end;
        ++beg;
    }
    return true;
}

vector<string> PalindromFilter(const vector<string>& words, int minLength){
    vector<string> ans;
    ans.reserve(words.size());
    for(const auto& str : words){
        if(IsPalindrom(str) && str.size() >= minLength){
            ans.emplace_back(str);
        }
    }
    return ans;
}

int main(){
    vector<string> strs;
    int min_length;
    std::cin >> min_length;

    for(string line; std::getline(std::cin, line);){
        strs.emplace_back(std::move(line));
    }

    for(const auto& str : PalindromFilter(strs, min_length)){
        std::cout << str << std::endl;
    }

    return 0;
}