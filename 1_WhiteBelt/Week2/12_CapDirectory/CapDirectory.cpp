#include <iostream>
#include <map>

using std::map;
using std::string;

using Dictionary = map<string, string>;

void CHANGE_CAPITAL(Dictionary & dict, const string& country_name, const string& new_capital){

    auto country = dict.find(country_name);
    if(country == dict.end()){
        country = dict.emplace(country_name, new_capital).first;
        std::cout << "Introduce new country " << country_name
                  << " with capital " << country->second << std::endl;
    } else {
        if(new_capital == country->second){
            std::cout << "Country " << country_name
                      << " hasn't changed its capital" << std::endl;
        }
        else {
            std::cout << "Country " << country_name << " has changed its capital from "
                      << country->second <<  " to " << new_capital << std::endl;
            country->second = new_capital;
        }
    }
}

void RENAME(Dictionary& dict, const string& old_country_name, const string& new_country_name){

    auto old_country = dict.find(old_country_name);
    auto new_country = dict.find(new_country_name);

    if(old_country != dict.end() && new_country == dict.end() && old_country_name != new_country_name) {
        dict[new_country_name] = old_country->second;

        std::cout << "Country " << old_country_name << " with capital "
                  << old_country->second << " has been renamed to " << new_country_name << std::endl;

        dict.erase(old_country_name);

    } else {
        std::cout << "Incorrect rename, skip" << std::endl;
    }
}

void ABOUT(const Dictionary& dict, const std::string& country_name){
    auto country = dict.find(country_name);

    if(country != dict.end()){
        std::cout << "Country " << country_name << " has capital " << country->second << std::endl;
    }
    else{
        std::cout << "Country " << country_name << " doesn't exist" << std::endl;
    }
}

void DUMP(const Dictionary& dict){
    if(dict.empty()) {
        std::cout << "There are no countries in the world" << std::endl;
    } else {
        for(const auto& item : dict){
            std::cout << item.first << "/" << item.second << std::endl;
        }
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
            string country_name, new_capital;
            std::cin >> country_name >> new_capital;
            CHANGE_CAPITAL(map, country_name, new_capital);
        }
        else if(str == "RENAME"){
            string old_country_name, new_country_name;
            std::cin >> old_country_name >> new_country_name;
            RENAME(map, old_country_name, new_country_name);
        }
        else if(str == "ABOUT"){
            std::string country_name;
            std::cin >> country_name;
            ABOUT(map, country_name);
        }
        else if(str == "DUMP"){
            DUMP(map);
        }
        n--;
    }
    return 0;
}