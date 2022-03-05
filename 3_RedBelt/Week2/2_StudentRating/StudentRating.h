#pragma once

#include <map>
#include <string>
#include "C:\Users\cobak\CLionProjects\red_belt\profiler\MyProfiler.h"

using namespace std;

struct Student {
    string first_name;
    string last_name;
    map<string, double> marks;
    double rating;

    bool operator<(const Student &other) const {
        return GetName() < other.GetName();
    }

    bool Less(const Student &other) const {
        //LOG_DURATION("Less")
        return rating > other.rating;
    }

    string GetName() const {
        return first_name + " " + last_name;
    }
};