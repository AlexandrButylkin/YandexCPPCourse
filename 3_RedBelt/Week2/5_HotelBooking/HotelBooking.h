#ifndef TASK_6_HOTELS_H
#define TASK_6_HOTELS_H

#include <map>
#include <deque>
#include <string>
#include <set>

struct Client{
    int id;
    int time;
    std::string hotel_name;
    int rooms;
};

bool operator==(const Client& lhs, const Client& rhs){
    return std::tie(lhs.id, lhs.time, lhs.hotel_name, lhs.rooms)
    == std::tie(rhs.id, rhs.time, rhs.hotel_name, rhs.rooms);
}

bool operator<(const Client& lhs, const Client& rhs){
    return std::tie(lhs.id, lhs.time, lhs.hotel_name, lhs.rooms)
           < std::tie(rhs.id, rhs.time, rhs.hotel_name, rhs.rooms);
}

class Hotels{
public:
    void Add(Client& client){
        data.emplace(client);
        hotel_client[client.hotel_name].emplace_back(client.id);
        hotel_rooms[client.hotel_name] += client.rooms;

        update(client.time - 86400);

    }

    int getRooms(const std::string& hotel_name){
        return hotel_rooms[hotel_name];
    }

    size_t getClients(const std::string& hotel_name){
        return hotel_client[hotel_name].size();
    }

private:
    std::set<Client> data;
    std::map<std::string, std::deque<int>> hotel_client;
    std::map<std::string, int> hotel_rooms;

    void update(int dur){

        auto begin = data.begin();
        auto end = data.end();

        while(begin->time <= dur && begin != end){
            hotel_client[begin->hotel_name].pop_front();
            hotel_rooms[begin->hotel_name] -= begin->rooms;
            begin = data.erase(begin);
        }
    }

};

#endif //TASK_6_HOTELS_H
