#include "BusManager.h"

void BusManager::AddBus(const string& bus, const vector<string>& stops) {
    // Реализуйте этот метод
    buses_to_stops[bus] = stops;
    for (const auto& stop : stops) {
        stops_to_buses[stop].push_back(bus);
    }
}

BusesForStopResponse BusManager::GetBusesForStop(const string& stop) const {
    BusesForStopResponse a;
    if (stops_to_buses.count(stop) == 0) {
        a.Buses_For_Stop_Response.push_back ("No stop");
    }
    else {
        a.Buses_For_Stop_Response = stops_to_buses.at(stop);
    }
    return a;
}

StopsForBusResponse BusManager::GetStopsForBus(const string& bus) const {
    StopsForBusResponse a;
    if (buses_to_stops.count(bus) != 0)
    {
        for (const string& stop : buses_to_stops.at(bus)) {
            a.Stops_Response.push_back(stop);
            if (stops_to_buses.at(stop).size() == 1) {
                a.Bus_Response.push_back({ "no interchange" });
            }
            else {

                vector <string> b;
                for (const string& other_bus : stops_to_buses.at(stop)) {
                    if (bus != other_bus) {
                        b.push_back(other_bus);
                    }
                }
                a.Bus_Response.push_back(b);
            }
        }
    }

    return a;
}


AllBusesResponse BusManager::GetAllBuses() const {
    // Реализуйте этот метод
    AllBusesResponse a;
    if (!buses_to_stops.empty()) {
        for (const auto& bus_item : buses_to_stops) {
            for (const string& stop : bus_item.second) {
                a.All_Buses_Response[bus_item.first].push_back(stop);
            }
        }
    }
    return a;
}