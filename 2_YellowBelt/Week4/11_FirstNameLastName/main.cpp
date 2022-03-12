#include <iostream>
#include "Person.h"

using namespace std;

/*class Person {
public:
    void ChangeFirstName(int year, const std::string &first_name){
        fname[year] = first_name;
    }

    void ChangeLastName(int year, const std::string &last_name){
        lname[year] = last_name;
    }

    std::string GetFullName(int year) const {
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

private:
    static std::string GetName(const std::map<int, std::string>& names, const int& year){
        auto iter_name = names.upper_bound(year);

        if(iter_name == names.begin()){
            return "";
        } else {

            return std::prev(iter_name)->second;
        }
    }

private:
    std::map<int, std::string> fname;
    std::map<int, std::string> lname;
};*/


int main() {

    {
        Person person;

        person.ChangeFirstName(1965, "Polina");
        person.ChangeLastName(1967, "Sergeeva");
        for (int year : {1900, 1965, 1990}) {
            cout << person.GetFullName(year) << endl;
        }

        person.ChangeFirstName(1970, "Appolinaria");
        for (int year : {1969, 1970}) {
            cout << person.GetFullName(year) << endl;
        }

        person.ChangeLastName(1968, "Volkova");
        for (int year : {1969, 1970}) {
            cout << person.GetFullName(year) << endl;
        }
    }
    std::cout << std::endl;
    {
        Person person;

        cout << person.GetFullName(2000) << endl;
        person.ChangeLastName(1968, "1968_2nd");
        person.ChangeLastName(1967, "1967_2nd");
        person.ChangeLastName(1965, "1965_2nd");
        person.ChangeLastName(1966, "1966_2nd");

        for (int year: {1900, 1920, 1950, 1965, 1966, 1967, 1968}) {
            cout << person.GetFullName(year) << endl;
        }

        person.ChangeFirstName(1920, "1920_1st");
        person.ChangeFirstName(1900, "1900_1st");
        person.ChangeFirstName(1965, "1965_1st");
        person.ChangeFirstName(1950, "1950_1st");

        for (int year: {1965, 1966, 1967, 1968}) {
            cout << person.GetFullName(year) << endl;
        }
    }
    return 0;
}