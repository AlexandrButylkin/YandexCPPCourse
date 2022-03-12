#include "Person.h"

void Person::ChangeFirstName(int year, const std::string &first_name){
    fname[year] = first_name;
}

void Person::ChangeLastName(int year, const std::string &last_name){
    lname[year] = last_name;
}

std::string Person::GetFullName(int year) const {
    std::string last_name = GetName(lname, year);
    std::string first_name = GetName(fname, year);

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

std::string Person::GetName(const std::map<int, std::string>& names, const int& year){
    auto iter_name = names.upper_bound(year);

    if(iter_name == names.begin()){
        return "";
    } else {
        return std::prev(iter_name)->second;
    }
}