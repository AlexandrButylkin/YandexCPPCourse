#ifndef INC_4_DECOMPOSITINGPROGRAM2_QUERY_H
#define INC_4_DECOMPOSITINGPROGRAM2_QUERY_H


#include <string>
#include <vector>
#include <sstream>
using namespace std;

enum class QueryType final {
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses
};

struct Query {
    QueryType type;
    string bus;
    int stop_count;
    string stop;
    vector<string> stops;
};

istream& operator >> (istream& is, Query& q);


#endif //INC_4_DECOMPOSITINGPROGRAM2_QUERY_H
