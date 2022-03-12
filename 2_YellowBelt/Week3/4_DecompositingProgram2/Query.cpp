#include "Query.h"

istream& operator>> (istream& is, Query& q) {
    string operation_code;
    is >> operation_code;

    if (operation_code == "NEW_BUS") {

        q.stops.clear();
        q.type = QueryType::NewBus;
        is >> q.bus;
        is >> q.stop_count;
        for (int i = 0; i < q.stop_count; ++i) {
            string stop_1;
            is >> stop_1;
            q.stops.push_back(stop_1);
        }
    }

    else if (operation_code == "BUSES_FOR_STOP") {
        q.type = QueryType::BusesForStop;
        is >> q.stop;
    }
    else if (operation_code == "STOPS_FOR_BUS") {
        q.type = QueryType::StopsForBus;
        is >> q.bus;
    }

    else if (operation_code == "ALL_BUSES") {
        q.type = QueryType::AllBuses;
    }
    return is;
}