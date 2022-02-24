//
// Created by cobak on 11.01.2022.
//

#ifndef TASK_6_STATS_H
#define TASK_6_STATS_H

#include "http_request.h"

#include <string_view>
#include <map>
#include <vector>
#include <sstream>



using namespace std;

class Stats {
public:
    Stats() :
            methods({
                {"GET", 0},
                {"PUT", 0},
                {"POST", 0},
                {"DELETE", 0},
                {"UNKNOWN", 0}}),
            URLs({
                {"/", 0},
                {"/order", 0},
                {"/product", 0},
                {"/basket", 0},
                {"/help", 0},
                {"unknown", 0}}) {}



    void AddMethod(string_view method);

    void AddUri(string_view uri);

    const map<string_view, int>& GetMethodStats() const { return methods; }
    const map<string_view, int>& GetUriStats() const {return URLs; }

private:
    std::map<std::string_view , int> methods;
    std::map<std::string_view , int> URLs;
};

HttpRequest ParseRequest(string_view line);

#endif //TASK_6_STATS_H
