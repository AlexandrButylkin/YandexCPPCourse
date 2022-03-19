#ifndef TASK_6_HOTELDATABASE_H
#define TASK_6_HOTELDATABASE_H

#include <map>
#include <deque>
#include <string>
#include <set>
#include <vector>
#include <memory>

struct Client final {
    int id;
    int64_t time;
    int rooms;
};

class Hotel final {
public:
    void AddClient(const Client& client);
    int GetRooms(int64_t time);
    size_t GetClients(int64_t time);


private:
    void UpdateClients(int64_t time);
    void PopFront();

    static const size_t MAX_TIME = 86400;
    std::map<int, int> clients_id;
    std::deque<Client> clients_;
    int room_count;
};


class HotelDatabase final {
public:
    HotelDatabase() = default;

    void Book(int64_t time, const std::string& hotel_name,
              int client_id, int room_count);
    int GetRooms(const std::string& hotel_name);
    size_t GetClients(const std::string& hotel_name);

private:
    int64_t curr_time = 0;
    std::map<std::string, Hotel> hotels_;
};
#endif //TASK_6_HOTELDATABASE_H
