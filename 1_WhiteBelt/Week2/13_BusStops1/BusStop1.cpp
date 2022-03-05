#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

void NEW_BUS(std::vector<std::pair<std::string, std::vector<std::string>>>& map){
    std::string bus;
    int count_stop = 0;
    std::cin >> bus >> count_stop;
    std::vector<std::string> bus_stop(count_stop);
    for(std::string& str : bus_stop)
        std::cin >> str;
    std::pair<std::string, std::vector<std::string>> pair(bus, bus_stop);
    map.push_back(pair);
}

void BUSES_FOR_STOP(const std::vector<std::pair<std::string, std::vector<std::string>>>& map){
    std::string stop;
    std::cin >> stop;
    bool flag = false;
    for(const std::pair<std::string, std::vector<std::string>>& buses : map){
        for(const std::string& stops : buses.second){
            if(stop == stops){
                std::cout << buses.first << " ";
                flag = true;
                break;
            }
        }
    }
    if(!flag){
        std::cout << "No stop";
    }
    std::cout << std::endl;
}

void BUSES_FOR_STOP(const std::vector<std::pair<std::string, std::vector<std::string>>>& map, const std::string& stop, const std::string& bus){
    bool flag = false;
    for(const std::pair<std::string, std::vector<std::string>>& buses : map){
        for(const std::string& stops : buses.second){
            if(stop == stops && buses.first != bus){
                std::cout << buses.first << " ";
                flag = true;
                break;
            }
        }
    }
    if(!flag){
        std::cout << "no interchange";
    }
    std::cout << std::endl;
}

void STOPS_FOR_BUS(const std::vector<std::pair<std::string, std::vector<std::string>>>& map){
    std::string bus;
    std::cin >> bus;
    bool flag = false;

    for(const std::pair<std::string, std::vector<std::string>>& buses : map){
        if(buses.first == bus){
            flag = true;
            for(const std::string& stops : buses.second){
                std::cout << "Stop " << stops << ": ";
                BUSES_FOR_STOP(map, stops, bus);
            }
        }
    } 
    if(!flag) std::cout << "No bus" << std::endl;
}

void ALL_BUSES(const std::vector<std::pair<std::string, std::vector<std::string>>>& map){
    if(!map.empty()){
        std::vector<std::pair<std::string, std::vector<std::string>>> new_map = map;
        std::sort(new_map.begin(), new_map.end());
        for(const std::pair<std::string, std::vector<std::string>>& buses : new_map){
            std::cout << "Bus " << buses.first << ": ";
            for(const std::string& stops : buses.second){
                std::cout << stops << " ";
            }
            std::cout << std::endl;
        }
    } else std::cout << "No buses" << std::endl;
}

int main(){
    int n = 0;
    std::cin >> n;
    std::vector<std::pair<std::string, std::vector<std::string>>> map;
    while(n > 0){
        std::string str;
        std::cin >> str;
        if(str == "NEW_BUS"){
            NEW_BUS(map);
        }
        else if(str == "BUSES_FOR_STOP"){
            BUSES_FOR_STOP(map);
        }
        else if(str == "STOPS_FOR_BUS"){
            STOPS_FOR_BUS(map);
        }
        else if(str == "ALL_BUSES"){
            ALL_BUSES(map);
        }
        n--;
    }
    return 0;
}