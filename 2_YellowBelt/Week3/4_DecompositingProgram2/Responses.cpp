#include "Responses.h"
#include <sstream>

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
    for (const auto& bus : r.Buses_For_Stop_Response) {
        os << bus << " ";
    }
    return os;
}

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
    if (r.Stops_Response.empty()) {
        os << "No bus";
    }
    else {
        int count = 0;
        for (const auto& i : r.Stops_Response) {
            os << "Stop " << i << ": ";
            for (const auto& j : r.Bus_Response[count]) {
                os << j << " ";
            }
            if ( count + 1 != r.Stops_Response.size())
                os << endl;
            ++count;
        }
    }
    return os;
}

ostream& operator << (ostream& os, const AllBusesResponse& r) {
    if (r.All_Buses_Response.empty()) {
        os << "No buses";
    }
    else {
        int count = 0;
        for (const auto& bus_item : r.All_Buses_Response) {
            os << "Bus " << bus_item.first << ": ";
            for (const string& stop : bus_item.second) {
                os << stop << " ";
            }

            if (count + 1 != r.All_Buses_Response.size())
                os << endl;
            ++count;
        }
    }
    return os;
}
