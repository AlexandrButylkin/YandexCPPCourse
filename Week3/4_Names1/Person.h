#ifndef PERSON_H_
#define PERSON_H_

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

class Person
{
public:
    void ChangeFirstName(int year, const std::string &first_name)
    {
        fname[year] = first_name;
    }

    void ChangeLastName(int year, const std::string &last_name)
    {
        lname[year] = last_name;
    }

    std::string form_str(const std::map<int, std::string>& name, const int& year) const{
        if(name.empty() || year < name.begin()->first)
            return "";
        std::map<int, std::string>::const_iterator it = name.end();
        it--;
        if(it->first <= year){
            return it->second;
        }
        it = name.begin();
        while(it != name.end()){
            if(year < it->first)
                return (--it)->second;
            ++it;
        }
    }

    std::string GetFullName(int year)
    {
        std::string str1 = form_str(lname, year);
        std::string str2 = form_str(fname, year);
        if(str1 == "" && str2 == ""){
            return "Incognito";
        }
        std::string res_str;
        if(str1 == ""){
            res_str = " with unknown last name";
        } else {
            res_str = str1;
        }
        if(str2 == ""){
            res_str += " with unknown first name";
        } else {
            if(res_str[0] == ' '){
                res_str = str2 + res_str;
            } else {
                res_str = str2 + " " + res_str;
            }
        }
        return res_str;
    }
private:
    std::map<int, std::string> fname;
    std::map<int, std::string> lname;
};
#endif