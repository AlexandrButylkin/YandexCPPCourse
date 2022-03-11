#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

using std::map;
using std::string;
using std::vector;

using Stop = string;
using Bus = string;
using Stops = map<Stop, vector<string>>;
using Buses = map<Bus, vector<string>>;

void NEW_BUS(Stops& buses, Buses& stops,
             const string& bus_name, const vector<string>& stops_name){
    buses[bus_name] = stops_name;
    for(const auto& stop : stops_name){
        stops[stop].emplace_back(bus_name);
    }
}

void BUSES_FOR_STOP(const Stops& stops, const string& stop_name) {

    const auto &stop = stops.find(stop_name);
    if (stop == stops.end()) {
        std::cout << "No stop";
    }
    for (const auto &bus: stop->second) {
        std::cout << bus << " ";
    }

    std::cout << std::endl;
}

void STOPS_FOR_BUS(const Buses& buses, const string& bus_name, const Stops& stops){

    const auto bus = buses.find(bus_name);

    if(bus == buses.end()) {
        std::cout << "No bus" << std::endl;
    } else {
        for(const auto& stop : bus->second){
            std::cout << "Stop " << stop << ": ";
            if (stops.at(stop).size() == 1) {
                std::cout << "no interchange";
            } else {
                for (const auto &other_bus: stops.at(stop)) {
                    if (other_bus != bus_name) {
                        std::cout << other_bus << " ";
                    }
                }
            }
            std::cout << std::endl;
        }
    }
}

void ALL_BUSES(const Buses& buses){

    if(buses.empty()){
        std::cout << "No buses";
    }

    for(const auto& bus : buses){
        std::cout << "Bus " << bus.first << ": ";
        for(const auto& stop : bus.second){
            std::cout << stop << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}



int main(){
    int n = 0;
    std::cin >> n;

    Stops stops;
    Buses buses;

    while(n > 0){
        std::string request;
        std::cin >> request;
        if(request == "NEW_BUS"){

            string bus_name;
            size_t count = 0;
            std::cin >> bus_name >> count;

            vector<string> stops_for_bus;
            stops_for_bus.reserve(count);

            for(auto i = 0; i < count; ++i){
                string stop;
                std::cin >> stop;
                stops_for_bus.emplace_back(std::move(stop));
            }

            NEW_BUS(buses, stops, bus_name, stops_for_bus);
        }
        else if(request == "BUSES_FOR_STOP"){

            string stop;
            std::cin >> stop;

            BUSES_FOR_STOP(stops, stop);
        }
        else if(request == "STOPS_FOR_BUS"){
            string bus;
            std::cin >> bus;

            STOPS_FOR_BUS(buses, bus, stops);
        }
        else if(request == "ALL_BUSES"){
            ALL_BUSES(buses);
        }
        n--;
    }
    return 0;
}