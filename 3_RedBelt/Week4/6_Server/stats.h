#ifndef TASK_6_STATS_H
#define TASK_6_STATS_H

#include "http_request.h"

#include <map>
#include <string>
#include <array>

class PartStats {
public:
    template<typename C>
    PartStats(const C& keys, std::string_view default_key);

    void Add(std::string_view key);

    const std::map<std::string_view, int>& Get() const;
private:
    const std::string_view default_key_;
    std::map<std::string_view, int> keys_count_;
};

class Stats {
public:
    Stats() :
            methods(method_keys, default_method),
            uris(url_keys, default_url) {}


    void AddMethod(string_view method);
    void AddUri(string_view uri);

    const map<string_view, int>& GetMethodStats() const;
    const map<string_view, int>& GetUriStats() const;

private:

    inline static const std::string default_method = "UNKNOWN";
    inline static const std::string default_url = "unknown";

    inline static const std::array<std::string, 4> method_keys = {"GET",
                                                                  "PUT",
                                                                  "POST",
                                                                  "DELETE"};
    inline static const std::array<std::string, 5> url_keys = {"/",
                                                               "/order",
                                                               "/product",
                                                               "/basket",
                                                               "/help"};

    PartStats methods;
    PartStats uris;

};

template<typename C>
PartStats::PartStats(const C& keys, std::string_view default_key) : default_key_(default_key) {
    for(const auto& key : keys){
        keys_count_[key] = 0;
    }
    keys_count_[default_key] = 0;
}

#endif //TASK_6_STATS_H
