//
// Created by cobak on 05.03.2022.
//

#ifndef INC_1_DECOMPOSITIONPROGRAM_BUSMANAGER_H
#define INC_1_DECOMPOSITIONPROGRAM_BUSMANAGER_H


#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

enum class QueryType {
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses
};

struct Query final {
    QueryType type;
    string bus;
    string stop;
    vector<string> stops;
};

struct BusesForStopResponse final {
    vector<string> buses;
};

struct StopsForBusResponse final {
    string bus;
    vector<pair<string, vector<string>>> stops_for_buses;
};

struct AllBusesResponse final {
    map<string, vector<string>> buses_to_stops;
};

istream& operator >> (istream& is, Query& q);
ostream& operator << (ostream& os, const BusesForStopResponse& r);
ostream& operator << (ostream& os, const StopsForBusResponse& r);
ostream& operator << (ostream& os, const AllBusesResponse& r);

class BusManager final {
public:

    void AddBus(const string& bus, const vector<string>& stops);
    BusesForStopResponse GetBusesForStop(const string& stop) const;
    StopsForBusResponse GetStopsForBus(const string& bus) const;
    AllBusesResponse GetAllBuses() const;

private:
    map<string, vector<string>> buses_to_stops;
    map<string, vector<string>> stops_to_buses;
};



#endif //INC_1_DECOMPOSITIONPROGRAM_BUSMANAGER_H
