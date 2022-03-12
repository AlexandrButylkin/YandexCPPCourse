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
    map<int, string> fname;
    map<int, string> lname;
};

string GetName(const map<int, string>& names, const int year);
string GetNameWithHistory(const map<int, string>& names, const int year);
vector<string> MakeHistory(const map<int, string>& names, const int year);
string JoinNames(const string& first_name, const string& last_name);

#endif //INC_5_NAMES2_PERSON_H
