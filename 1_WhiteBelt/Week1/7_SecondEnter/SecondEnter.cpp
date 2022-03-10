#include <iostream>
#include <string>

int main(){
    std::string str;
    std::cin >> str;

    if(auto pos = str.find('f'); pos == std::string::npos) {
        std::cout << -2 <<std::endl;
    } else {
        if(pos = str.find('f', pos + 1); pos == std::string::npos){
            std::cout << -1 << std::endl;
        } else {
            std::cout << pos << std::endl;
        }
    }
    return 0;
}

