//
// Created by cobak on 05.03.2022.
//

#ifndef INC_4_DECOMPOSITINGPROGRAM2_BUSMANAGER_H
#define INC_4_DECOMPOSITINGPROGRAM2_BUSMANAGER_H

#include "Query.h"
#include "Responses.h"

class BusManager final {
private:
    map<string, vector<string>> buses_to_stops, stops_to_buses;

public:
    void AddBus(const string& bus, const vector<string>& stops);
    BusesForStopResponse GetBusesForStop(const string& stop) const;
    StopsForBusResponse GetStopsForBus(const string& bus) const;
    AllBusesResponse GetAllBuses() const;
};


#endif //INC_4_DECOMPOSITINGPROGRAM2_BUSMANAGER_H
