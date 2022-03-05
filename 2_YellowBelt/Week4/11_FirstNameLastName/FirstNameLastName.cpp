#include <iostream>
#include <map>

using std::cin;
using std::cout;
using std::endl;

std::string FindNameByYear(const std::map<int, std::string>& names, int year) {
    auto iter = names.upper_bound(year);

    if(iter != names.begin()){
        return (--iter)->second;
    } return {};
}

class Person{
public:

    void ChangeFirstName(int year, const std::string& first_name) {
        first_name_data[year] = first_name;
    }

    void ChangeLastName(int year, const std::string& last_name) {
        last_name_data[year] = last_name;
    }

    std::string GetFullName(int year) {
        auto first = FindNameByYear(first_name_data, year);
        auto last = FindNameByYear(last_name_data, year);

        if(!first.empty() && !last.empty()){
            return first + " " + last;
        } else if (!first.empty() && last.empty()) {
            return first + " with unknown last name";
        } else if (first.empty() && !last.empty()) {
            return last + " with unknown first name";
        } else {
            return "Incognito";
        }
    }
private:

    using FirstName = std::string;
    using LastName = std::string;

    std::map<int, FirstName> first_name_data;
    std::map<int, LastName > last_name_data;
};



int main() {
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

    return 0;
}
