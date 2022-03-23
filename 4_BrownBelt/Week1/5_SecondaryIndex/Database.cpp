#include "Database.h"

bool Record::operator==(const Record &record) const {
    return std::tie(id, title, user, timestamp, karma) ==
           std::tie(record.id, record.title, record.user, record.timestamp, record.karma);
}


bool Database::Put(const Record &record) {
    auto iter = data.find(record.id);
    if(iter != data.end()) {
        return false;
    }

    auto ptr_record = std::make_shared<Record>(record);
    auto timestamp_iter = timestamps.emplace(record.timestamp, ptr_record);
    auto karma_iter = karmas.emplace(record.karma, ptr_record);
    auto user_iter = users.emplace(record.user, ptr_record);

    data.emplace(record.id, Data{ptr_record, timestamp_iter, karma_iter, user_iter});
    return true;
}

const Record* Database::GetById(const std::string &id) const {
    const auto iter = data.find(id);
    if(iter == data.end()){
        return nullptr;
    }
    return iter->second.record_.get();
}

bool Database::Erase(const std::string &id) {
    const auto iter = data.find(id);
    if(iter == data.end()){
        return false;
    }

    timestamps.erase(iter->second.timestamp_it);
    karmas.erase(iter->second.karma_it);
    users.erase(iter->second.user_it);
    data.erase(iter);
    return true;
}