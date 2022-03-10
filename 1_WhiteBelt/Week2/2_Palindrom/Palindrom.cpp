#include <iostream>

bool IsPalindrom(const std::string& str){
    int beg = 0, end = str.size() - 1;
    while(beg <= end){
        if(str[beg] != str[end]) return false;
        --end;
        ++beg;
    }
    return true;
}

int main(){
    std::string str;
    std::cin >> str;
    std::cout << IsPalindrom(str) << std::endl;
    return 0;
}
