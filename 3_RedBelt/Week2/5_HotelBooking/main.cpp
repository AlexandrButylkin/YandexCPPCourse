#include "HotelDatabase.h"

#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    HotelDatabase manager;

    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;

        if (query_type == "BOOK") {

            int64_t time;
            string hotel_name;
            int client_id, room_count;

            cin >> time >> hotel_name >> client_id >> room_count;
            manager.Book(time, hotel_name, client_id, room_count);

        } else if (query_type == "CLIENTS") {
            std::string hotel_name;
            cin >> hotel_name;
            cout << manager.GetClients(hotel_name) << std::endl;
        } else if (query_type == "ROOMS"){
            std::string hotel_name;
            cin >> hotel_name;
            cout << manager.GetRooms(hotel_name) << std::endl;
        }
    }
    return 0;
}