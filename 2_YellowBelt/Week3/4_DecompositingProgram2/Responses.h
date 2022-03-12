//
// Created by cobak on 05.03.2022.
//

#ifndef INC_4_DECOMPOSITINGPROGRAM2_RESPONSES_H
#define INC_4_DECOMPOSITINGPROGRAM2_RESPONSES_H


#include <string>
#include <vector>
#include <map>

using namespace std;

struct BusesForStopResponse {
    vector<string > Buses_For_Stop_Response;
};

struct StopsForBusResponse {
    vector <string> Stops_Response;
    vector< vector <string>> Bus_Response;
};

struct AllBusesResponse {
    map<string, vector<string>> All_Buses_Response;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r);
ostream& operator << (ostream& os, const StopsForBusResponse& r);
ostream& operator << (ostream& os, const AllBusesResponse& r);


#endif //INC_4_DECOMPOSITINGPROGRAM2_RESPONSES_H
