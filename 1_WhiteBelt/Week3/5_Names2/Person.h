#ifndef INC_4_NAMES1_PERSON_H
#define INC_4_NAMES1_PERSON_H


#include <iostream>
#include <map>

class Person
{
public:
    void ChangeFirstName(int year, const std::string &first_name);
    void ChangeLastName(int year, const std::string &last_name);
    std::string GetFullName(int year) const;

private:

    static std::string GetName(const std::map<int, std::string>& names, const int& year);

private:
    std::map<int, std::string> fname;
    std::map<int, std::string> lname;
};


#endif //INC_4_NAMES1_PERSON_H
