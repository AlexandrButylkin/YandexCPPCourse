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
        if(name.empty() || year < name.begin()->first){
            return "";
        }
        std::map<int, std::string>::const_iterator it = name.end();
        it--;
        if(it->first <= year){
            return it->second;
        }
        it = name.begin();
        while(it != name.end()){
            if(year < it->first){
                return (--it)->second;
            }
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

    std::string form_history(const std::map<int, std::string>& name, const std::map<int, std::string>::const_iterator& end) const {
        std::map<int, std::string>::const_iterator it = end;
        std::string history;
        while(it != name.begin()){
            --it;
            history += it->second + ", ";
            if(history == end->second + ", "){
                history = "";
            }
            if(it == name.begin() && history != ""){
                history.pop_back();
                history.pop_back();
                if(history == end->second){
                    return "";
                }
                history  = "(" + history;
                history += ")";
                return history;
            }
        }
        return "";
    }

    std::string form_str_history(const std::map<int, std::string>& name, const int& year) const{
        if(name.empty() || year < name.begin()->first)
            return "";
        std::map<int, std::string>::const_iterator it = name.end();
        it--;
        if(it->first <= year){
            if(it != name.begin()){
                return it->second + " " + form_history(name, it);
            } else return it->second;
        }
        it = name.begin();
        int count = 0;
        while(it != name.end()){
            count++;
            if(year < it->first)
                if(it != name.begin()){
                    std::string a = form_history(name, --it);
                    return it->second + " " + form_history(name, --it);
                }
            ++it;
        }
        std::cout << "! " << it->first << ": " << it->second << "\n";
        return (--it)->second;
    }

    std::string GetFullNameWithHistory(int year)
    {
        std::string str1 = form_str_history(lname, year);
        std::string str2 = form_str_history(fname, year);
        if(str1 == "" && str2 == ""){
            return "Incognito";//"###############\nIncognito\n###############";
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
        for(size_t i = 0; i < res_str.size() - 2; ++i){
            if(res_str[i] == ' ' && res_str[i + 1] == ' '){
                res_str.erase(i, 1);
            }
        }
        if(res_str[res_str.size() - 1] == ' '){
            res_str.pop_back();
        }
        return res_str;//"###############\n" + res_str + "\n###########";

    }

private:
    std::map<int, std::string> fname;
    std::map<int, std::string> lname;
};
#endif