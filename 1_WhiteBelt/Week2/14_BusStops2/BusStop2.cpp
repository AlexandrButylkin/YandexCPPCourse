#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

void add_stops(std::map<std::vector<std::string>, int>& map, int& count){
    int i = 0;
    std::cin >> i;
    std::vector<std::string> stops(i);
    for(std::string& str : stops){
        std::cin >> str;
    }
    if(map.find(stops) == map.end()){
        std::cout << "New bus " << count << std::endl;
        map.emplace(stops, count);
        count++;
    } else std::cout << "Already exists for " << map.find(stops)->second << std::endl;
}

int main(){
    int count = 1;
    int n = 0;
    std::cin >> n;
    std::map<std::vector<std::string>, int> map;
    while(n > 0){
        add_stops(map, count);
        n--;
    }
    return 0;
}