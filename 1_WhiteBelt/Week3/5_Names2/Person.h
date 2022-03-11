#ifndef INC_5_NAMES2_PERSON_H
#define INC_5_NAMES2_PERSON_H


#include <iostream>
#include <map>
#include <vector>

using std::string;
using std::vector;
using std::map;

class Person final {
public:
    void ChangeFirstName(int year, const string &first_name);
    void ChangeLastName(int year, const string &last_name);
    string GetFullName(int year) const;
    string GetFullNameWithHistory(int year) const;

private:

    static string GetName(const map<int, string>& names, const int year);
    static string GetNameWithHistory(const map<int, string>& names, const int year);
    static vector<string> MakeHistory(const map<int, string>& names, const int year);
    static string JoinNames(const string& first_name, const string& last_name);

private:
    map<int, string> fname;
    map<int, string> lname;
};


#endif //INC_5_NAMES2_PERSON_H
