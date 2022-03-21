#include "Stats.h"

void PartStats::Add(std::string_view key){
    const auto iter = keys_count_.find(key);
    if(iter != keys_count_.end()){
        ++iter->second;
    } else {
        ++keys_count_[default_key_];
    }
}

void Stats::AddMethod(string_view method){
    methods.Add(method);
}

void Stats::AddUri(string_view uri) {
    uris.Add(uri);
}

const std::map<std::string_view, int>& PartStats::Get() const{
    return keys_count_;
}

const map<string_view, int>& Stats::GetMethodStats() const {
    return methods.Get();
}
const map<string_view, int>& Stats::GetUriStats() const {
    return uris.Get();
}
