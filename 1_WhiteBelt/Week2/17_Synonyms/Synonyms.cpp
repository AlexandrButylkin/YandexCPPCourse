#include <iostream>
#include <map>
#include <set>

void add_map(std::map<std::string, std::set<std::string>>& map, const std::string& word1, const std::string& word2){
    std::set<std::string> set;
    set.emplace(word2);
    map.emplace(word1, set);
}

void ADD(std::map<std::string, std::set<std::string>>& map) {
    std::string word1;
    std::string word2;
    std::cin >> word1 >> word2;
    if(map.find(word1) != map.end()){
        map.find(word1)->second.emplace(word2);
    } else add_map(map, word1, word2);
    if(map.find(word2) != map.end()){
        map.find(word2)->second.emplace(word1);
    } else add_map(map, word2, word1);
}

void COUNT(const std::map<std::string, std::set<std::string>>& map){
    std::string word;
    std::cin >> word;
    if(map.find(word) != map.end()){
        std::cout << map.find(word)->second.size() << std::endl;
    } else std::cout << 0 << std::endl;
}

void CHECK(const std::map<std::string, std::set<std::string>>& map){
    std::string word1;
    std::string word2;
    std::cin >> word1 >> word2;
    if(map.find(word1) != map.end()){
        if(map.find(word1)->second.count(word2) == 1){
            std::cout << "YES" << std::endl;
        } else std::cout << "NO" << std::endl;
    } else std::cout << "NO" << std::endl;
}

int main(){
    int n = 0;
    std::cin >> n;
    std::map<std::string, std::set<std::string>> map;
    while(n > 0){
        std::string str;
        std::cin >> str;
        if(str == "ADD"){
            ADD(map);
        }
        else if(str == "COUNT"){
            COUNT(map);
        }
        else if(str == "CHECK"){
            CHECK(map);
        }
        n--;
    }
    return 0;
}