//
// Created by cobak on 05.03.2022.
//

#include "BusManager.h"

istream& operator >> (istream& is, Query& q) {
    string typeStr;
    is >> typeStr;
    if (typeStr == "NEW_BUS") {
        q.type = QueryType::NewBus;
        is >> q.bus;
        int stop_count = 0;
        is >> stop_count;
        q.stops.resize(stop_count);
        for (auto& stop : q.stops) {
            is >> stop;
        }
    } else if (typeStr == "BUSES_FOR_STOP") {
        q.type = QueryType::BusesForStop;
        is >> q.stop;
    } else if (typeStr == "STOPS_FOR_BUS") {
        q.type = QueryType::StopsForBus;
        is >> q.bus;
    } else if (typeStr == "ALL_BUSES") {
        q.type = QueryType::AllBuses;
    }

    return is;
}

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
    if (r.buses.empty()) {
        os << "No stop";
    } else {
        for (const auto& bus : r.buses) {
            os << bus << " ";
        }
    }
    return os;
}

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
    if (r.stops_for_buses.empty()) {
        os << "No bus";
    } else {
        bool first = true;
        for (const auto& stop_and_buses : r.stops_for_buses) {
            if (!first) {
                os << endl;
            }
            first = false;
            os << "Stop " << stop_and_buses.first << ":";
            if (stop_and_buses.second.size() == 1) {
                os << " no interchange";
            } else {
                for (const auto& bus : stop_and_buses.second) {
                    if (bus != r.bus) {
                        os << " " << bus;
                    }
                }
            }
        }
    }
    return os;
}

ostream& operator << (ostream& os, const AllBusesResponse& r) {
    if (r.buses_to_stops.empty()) {
        os << "No buses";
    } else {
        bool first = true;
        for (const auto& bus_and_stops : r.buses_to_stops) {
            if (!first) {
                os << endl;
            }
            first = false;
            os << "Bus " << bus_and_stops.first << ":";
            for (const auto& stop : bus_and_stops.second) {
                os << " " << stop;
            }
        }
    }
    return os;
}


void BusManager::AddBus(const string& bus, const vector<string>& stops) {
    buses_to_stops.insert(make_pair(bus, stops));
    for (const auto& stop : stops) {
        stops_to_buses[stop].push_back(bus);
    }
}

BusesForStopResponse BusManager::GetBusesForStop(const string& stop) const {
    if (stops_to_buses.count(stop) == 0) {
        return BusesForStopResponse{vector<string>()};
    } else {
        return BusesForStopResponse{stops_to_buses.at(stop)};
    }
}

StopsForBusResponse BusManager::GetStopsForBus(const string& bus) const {
    vector<pair<string, vector<string>>> result;

    if (buses_to_stops.count(bus) > 0) {
        for (const auto& stop : buses_to_stops.at(bus)) {
            result.emplace_back(stop, stops_to_buses.at(stop));
        }
    }
    return StopsForBusResponse{bus, result};
}

AllBusesResponse BusManager::GetAllBuses() const {
    return AllBusesResponse{buses_to_stops};
}
