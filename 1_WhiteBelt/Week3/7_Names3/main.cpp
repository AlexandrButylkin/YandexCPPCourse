#include <iostream>
#include "Person.h"


using namespace std;

int main() {
    {
        Person person("Polina", "Sergeeva", 1960);
        for (int year: {1959, 1960}) {
            cout << person.GetFullNameWithHistory(year) << endl;
        }

        person.ChangeFirstName(1965, "Appolinaria");
        person.ChangeLastName(1967, "Ivanova");
        for (int year: {1965, 1967}) {
            cout << person.GetFullNameWithHistory(year) << endl;
        }
    }

    {
        Person person("Polina", "Sergeeva", 1960);
        person.ChangeFirstName(1965, "Polina");
        person.ChangeLastName(1967, "Sergeeva");
        for (int year : {1900, 1965, 1990}) {
            cout << person.GetFullNameWithHistory(year) << endl;
        }

        person.ChangeFirstName(1970, "Appolinaria");
        for (int year : {1969, 1970}) {
            cout << person.GetFullNameWithHistory(year) << endl;
        }

        person.ChangeLastName(1968, "Volkova");
        for (int year : {1969, 1970}) {
            cout << person.GetFullNameWithHistory(year) << endl;
        }

        person.ChangeFirstName(1990, "Polina");
        person.ChangeLastName(1990, "Volkova-Sergeeva");
        cout << person.GetFullNameWithHistory(1990) << endl;

        person.ChangeFirstName(1966, "Pauline");
        cout << person.GetFullNameWithHistory(1966) << endl;

        person.ChangeLastName(1960, "Sergeeva");
        for (int year : {1960, 1967}) {
            cout << person.GetFullNameWithHistory(year) << endl;
        }

        person.ChangeLastName(1961, "Ivanova");
        cout << person.GetFullNameWithHistory(1967) << endl;
    }

    return 0;
}
