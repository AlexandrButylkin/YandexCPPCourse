#include "HotelDatabase.h"

void Hotel::AddClient(const Client& client){
    clients_.push_back(client);
    ++clients_id[client.id];
    room_count += client.rooms;
}

int Hotel::GetRooms(int64_t time){
    UpdateClients(time);
    return room_count;
}

size_t Hotel::GetClients(int64_t time){
    UpdateClients(time);
    return clients_id.size();
}

void Hotel::UpdateClients(int64_t time){
    while(!clients_.empty() && time - clients_.front().time >= MAX_TIME){
        PopFront();
    }
}

void Hotel::PopFront(){
    auto& curr_client = clients_.front();
    auto client_id_iter = clients_id.find(curr_client.id);

    if(--client_id_iter->second == 0){
        clients_id.erase(client_id_iter);
    }
    room_count -= curr_client.rooms;

    clients_.pop_front();
}

void HotelDatabase::Book(int64_t time, const std::string& hotel_name,
          int client_id, int room_count){
    curr_time = time;
    hotels_[hotel_name].AddClient({client_id, time, room_count});

}

int HotelDatabase::GetRooms(const std::string& hotel_name){
    return hotels_[hotel_name].GetRooms(curr_time);
}

size_t HotelDatabase::GetClients(const std::string& hotel_name){
    return hotels_[hotel_name].GetClients(curr_time);
}