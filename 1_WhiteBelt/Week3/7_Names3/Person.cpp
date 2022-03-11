#include "Person.h"

void Person::ChangeFirstName(int year, const string &first_name){
    if(year >= year_birth){
        fname[year] = first_name;
    }
}

void Person::ChangeLastName(int year, const string &last_name){
    if(year >= year_birth){
        lname[year] = last_name;
    }
}

string Person::GetFullName(int year) const {
    if(year < year_birth){
        return "No person";
    }
    return JoinNames(GetName(fname, year), GetName(lname, year));
}

string Person::GetName(const map<int, string>& names, const int year){
    return std::prev(names.upper_bound(year))->second;
}

string Person::GetFullNameWithHistory(int year) const{
    if(year < year_birth){
        return "No person";
    }
    return JoinNames(GetNameWithHistory(fname, year), GetNameWithHistory(lname, year));
}

string Person::GetNameWithHistory(const map<int, string>& names, const int year){
    auto history = MakeHistory(names, year);
    std::reverse(history.begin(), history.end());
    string name = std::move(history[0]);
    for(int i = 1, size = history.size(); i < size; ++i){
        if(i == 1){
            name += " (";
        } else {
            name += ", ";
        }
        name += history[i];
    }

    if(history.size() > 1){
        name += ")";
    }
    return name;
}

vector<string> Person::MakeHistory(const map<int, string>& names, const int year){
    vector<string> history;
    for(auto iter = names.begin(); iter != names.upper_bound(year); ++iter){
        if(history.empty() || history.back() != iter->second){
            history.emplace_back(iter->second);
        }
    }
    return history;
}

string Person::JoinNames(const string& first_name, const string& last_name){
    return first_name + " " + last_name;
}