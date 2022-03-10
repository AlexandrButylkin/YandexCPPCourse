#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

using std::string;
using std::vector;

using Buses = std::map<std::vector<std::string>, int>;

void AddBus(Buses& dict, int& count, vector<string>& stops){

    const auto bus = dict.find(stops);

    if(bus != dict.end()){
        std::cout << "Already exists for " << bus->second << std::endl;
    } else {
        std::cout << "New bus " << count << std::endl;
        dict.emplace(std::move(stops), count);
        ++count;
    }
}

int main(){
    Buses dict;
    int count = 1;

    int n = 0;
    std::cin >> n;
    while(n > 0){

        size_t size = 0;
        std::cin >> size;
        vector<string> stops;
        stops.reserve(size);

        for(auto i = 0; i < size; ++i){
            string stop;
            std::cin >> stop;
            stops.emplace_back(std::move(stop));
        }

        AddBus(dict, count, stops);
        n--;
    }
    return 0;
}