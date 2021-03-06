#include "Person.h"

void Person::ChangeFirstName(int year, const string &first_name){
    fname[year] = first_name;
}

void Person::ChangeLastName(int year, const string &last_name){
    lname[year] = last_name;
}

string Person::GetFullName(int year) const {
    return JoinNames(GetName(fname, year), GetName(lname, year));
}

string Person::GetName(const map<int, string>& names, const int year){
    auto iter_name = names.upper_bound(year);

    if(iter_name == names.begin()){
        return "";
    } else {

        return std::prev(iter_name)->second;
    }
}

string Person::GetFullNameWithHistory(int year) const{
    return JoinNames(GetNameWithHistory(fname, year), GetNameWithHistory(lname, year));
}

string Person::GetNameWithHistory(const map<int, string>& names, const int year){
    auto history = MakeHistory(names, year);
    if(history.empty()) {
        return "";
    }
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
    auto iter_name = names.upper_bound(year);

    vector<string> history;
    for(auto iter = names.begin(); iter != iter_name; ++iter){
        if(history.empty() || history.back() != iter->second){
            history.emplace_back(iter->second);
        }
    }
    return history;
}

string Person::JoinNames(const string& first_name, const string& last_name){
    if(last_name.empty() && first_name.empty()){
        return "Incognito";
    } else if (last_name.empty() && !first_name.empty()){
        return first_name + " with unknown last name";
    } else if (!last_name.empty() && first_name.empty()){
        return last_name + " with unknown first name";
    } else {
        return first_name + " " + last_name;
    }
}