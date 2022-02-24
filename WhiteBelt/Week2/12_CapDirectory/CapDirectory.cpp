#include <iostream>
#include <map>

void CHANGE_CAPITAL(std::map<std::string, std::string>& map){
    std::string str1 = "";
    std::string str2 = "";
    std::cin >> str1 >> str2;
    if(map.find(str1) == map.end()){
        map[str1] = str2;
        std::cout << "Introduce new country " << str1 << " with capital " << str2 << std::endl;
    }
    else{
        if(str2 == map[str1]){
            std::cout << "Country " << str1 << " hasn't changed its capital" << std::endl;
        }
        else{
            std::cout << "Country " << str1 << " has changed its capital from " << map[str1] <<  " to " << str2 << std::endl;
            map[str1] = str2;
        }
    }
}

void RENAME(std::map<std::string, std::string>& map){
    std::string str1 = "";
    std::string str2 = "";
    std::cin >> str1 >> str2;
    if(map.find(str1) != map.end() && map.find(str2) == map.end() && str1 != str2){
        std::cout << "Country " << str1 << " with capital " << map[str1] << " has been renamed to " << str2 << std::endl;
        map[str2] = map[str1];
        map.erase(str1);
    }
    else{
        std::cout << "Incorrect rename, skip" << std::endl;
    }
}

void ABOUT(const std::map<std::string, std::string>& map){
    std::string str = "";
    std::cin >> str;
    if(map.find(str) != map.end()){
        std::cout << "Country " << str << " has capital " << map.find(str)->second << std::endl;
    }
    else{
        std::cout << "Country " << str << " doesn't exist" << std::endl;
    }
}

void DUMP(const std::map<std::string, std::string>& map){
    if(!map.empty()){
        for(const auto& item : map){
            std::cout << item.first << "/" << item.second << std::endl;
        }
    }
    else {
        std::cout << "There are no countries in the world" << std::endl;
    }
}

int main(){
    int n = 0;
    std::cin >> n;
    std::map<std::string, std::string> map;
    while(n > 0){
        std::string str;
        std::cin >> str;
        if(str == "CHANGE_CAPITAL"){
            CHANGE_CAPITAL(map);
        }
        else if(str == "RENAME"){
            RENAME(map);
        }
        else if(str == "ABOUT"){
            ABOUT(map);
        }
        else if(str == "DUMP"){
            DUMP(map);
        }
        n--;
    }
    return 0;
}