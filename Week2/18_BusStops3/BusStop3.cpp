#include <iostream>
#include <algorithm>
#include <set>
#include <map>

void add_stops(std::map<std::set<std::string>, int>& map, int& count){
    int i = 0;
    std::cin >> i;
    std::set<std::string> stops;
    while (i > 0){
        std::string stop;
        std::cin >> stop;
        stops.emplace(stop);
        i--;
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
    std::map<std::set<std::string>, int> map;
    while(n > 0){
        add_stops(map, count);
        n--;
    }
    return 0;
}