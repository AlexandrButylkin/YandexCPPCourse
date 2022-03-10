#include <iostream>
#include <set>

int main(){
    std::set<std::string> set;
    int i = 0;
    std::cin >> i;

    while(i > 0){
        std::string str;
        std::cin >> str;
        set.emplace(str);
        i--;
    }

    std::cout << set.size();
    return 0;
}