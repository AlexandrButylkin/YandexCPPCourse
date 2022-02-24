#include <iostream>
#include <map>

void build_map(std::map<char, int>& map, const std::string& str){
    for(const char& c : str){
        ++map[c];
    }
}

void BuildCharCounters(const std::string& str1, const std::string& str2){
    std::map<char, int> mp1, mp2;
    build_map(mp1, str1);
    build_map(mp2, str2);
    if(mp1 == mp2){
        std::cout << "YES" << std::endl;
    }
    else{
        std::cout << "NO" << std::endl;
    }
}

int main(){
    int n = 0;
    std::cin >> n;
    while(n > 0){
        std::string str1, str2;
        std::cin >> str1 >> str2;
        BuildCharCounters(str1, str2);
        n--;
    }
    return 0;
}