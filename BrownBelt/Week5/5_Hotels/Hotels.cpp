#include <iostream>
#include <iomanip>
//#include "hotels.h"

#include <map>
#include <deque>
#include <string>
#include <set>
#include <queue>
using std::string;

struct Client{
    int id;
    int rooms = 0;
    std::string hotel_name;
    int64_t time = 0;
};

struct Hotel{
    int rooms = 0 ;
    std::map<int, int> ids;
};

bool operator==(const Client& lhs, const Client& rhs){
    return std::tie(lhs.id, lhs.rooms)
           == std::tie(rhs.id, rhs.rooms);
}

bool operator<(const Client& lhs, const Client& rhs){
    return std::tie(lhs.id, lhs.rooms)
           < std::tie(rhs.id, rhs.rooms);
}

class Hotels{
private:
    std::map<string, Hotel> hotel_data;
    std::deque<Client> data;


    void RefactorData(){

        while(data.front().time + 86400 <= data.back().time){
            hotel_data[data.front().hotel_name].rooms -= data.front().rooms;
            hotel_data[data.front().hotel_name].ids[data.front().id] -= data.front().rooms;
            if(hotel_data[data.front().hotel_name].ids[data.front().id] == 0){
                hotel_data[data.front().hotel_name].ids.erase(data.front().id);
            }
            data.pop_front();
        }
    }

public:

    void Add(const Client& client){
        data.emplace_back(client);
        hotel_data[client.hotel_name].rooms += client.rooms;
        hotel_data[client.hotel_name].ids[client.id] += client.rooms;

        RefactorData();
    }

    int GetRooms(const std::string& hotel_name){
        return hotel_data[hotel_name].rooms;
    }

    size_t GetClients(const std::string& hotel_name){
        return hotel_data[hotel_name].ids.size();
    }

};


using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Hotels manager;

    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;

        if (query_type == "BOOK") {

            Client client;
            cin >> client.time >> client.hotel_name >> client.id >> client.rooms;
            manager.Add(client);

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






/*#include <cstdint>
#include <iostream>
#include <map>
#include <queue>

using namespace std;


class HotelManager {
public:
  void Book(int64_t time, const string& hotel_name,
            int client_id, int room_count) {
    current_time_ = time;
    hotels_[hotel_name].Book({time, client_id, room_count});
  }
  int ComputeClientCount(const string& hotel_name) {
    return hotels_[hotel_name].ComputeClientCount(current_time_);
  }
  int ComputeRoomCount(const string& hotel_name) {
    return hotels_[hotel_name].ComputeRoomCount(current_time_);
  }

private:
  struct Booking {
    int64_t time;
    int client_id;
    int room_count;
  };

  class HotelInfo {
  public:
    void Book(const Booking& booking) {
      last_bookings_.push(booking);
      room_count_ += booking.room_count;
      ++client_booking_counts_[booking.client_id];
    }
    int ComputeClientCount(int64_t current_time) {
      RemoveOldBookings(current_time);
      return client_booking_counts_.size();
    }
    int ComputeRoomCount(int64_t current_time) {
      RemoveOldBookings(current_time);
      return room_count_;
    }
  private:
    static const int TIME_WINDOW_SIZE = 86400;
    queue<Booking> last_bookings_;
    int room_count_ = 0;
    map<int, int> client_booking_counts_;

    void PopBooking() {
      const Booking& booking = last_bookings_.front();
      room_count_ -= booking.room_count;
      const auto client_stat_it =
          client_booking_counts_.find(booking.client_id);
      if (--client_stat_it->second == 0) {
        client_booking_counts_.erase(client_stat_it);
      }
      last_bookings_.pop();
    }
    void RemoveOldBookings(int64_t current_time) {
      while (
          !last_bookings_.empty()
          && last_bookings_.front().time <= current_time - TIME_WINDOW_SIZE
      ) {
        PopBooking();
      }
    }
  };

  int64_t current_time_ = 0;
  map<string, HotelInfo> hotels_;
};


int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  HotelManager manager;

  int query_count;
  cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id) {
    string query_type;
    cin >> query_type;

    if (query_type == "BOOK") {
      int64_t time;
      cin >> time;
      string hotel_name;
      cin >> hotel_name;
      int client_id, room_count;
      cin >> client_id >> room_count;
      manager.Book(time, hotel_name, client_id, room_count);
    } else {
      string hotel_name;
      cin >> hotel_name;
      if (query_type == "CLIENTS") {
        cout << manager.ComputeClientCount(hotel_name) << "\n";
      } else if (query_type == "ROOMS") {
        cout << manager.ComputeRoomCount(hotel_name) << "\n";
      }
    }
  }

  return 0;
}*/