#include <iostream>
#include <vector>
using namespace std;

enum class Gender {
    FEMALE,
    MALE
};

struct Person final {
    int age;
    Gender gender;
    bool is_employed;
};

template <typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end) {
    if (range_begin == range_end) {
        return 0;
    }
    vector<typename InputIt::value_type> range_copy(range_begin, range_end);
    auto middle = begin(range_copy) + range_copy.size() / 2;
    nth_element(
            begin(range_copy), middle, end(range_copy),
            [](const Person& lhs, const Person& rhs) {
                return lhs.age < rhs.age;
            }
    );
    return middle->age;
}

bool operator<(const Person& lhs, const Person& rhs){
    return lhs.is_employed < rhs.is_employed;
}

struct PersonIters final {
    vector<Person>::iterator female_end;
    vector<Person>::iterator female_employ_end;
    vector<Person>::iterator male_employ_end;
};

PersonIters PartitionVector(vector<Person> &persons) {
    auto female_end = std::partition(
            persons.begin(),
            persons.end(),
            [](const Person &first) {
                return first.gender == Gender::FEMALE;
            });

    auto female_employ_end = std::partition(
            persons.begin(),
            female_end,
            [](const Person &first) {
                return first.is_employed;
            });

    auto male_employ_end = std::partition(
            female_end,
            persons.end(),
            [](const Person &first) {
                return first.is_employed;
            });
    return {female_end, female_employ_end, male_employ_end};
}

void PrintStats(vector<Person> persons) {

    PersonIters iters = PartitionVector(persons);

    std::cout << "Median age = " <<
    ComputeMedianAge(persons.begin(), persons.end()) << "\n";

    std::cout << "Median age for females = " <<
    ComputeMedianAge(persons.begin(), iters.female_end) << "\n";

    std::cout << "Median age for males = "
    << ComputeMedianAge(iters.female_end, persons.end()) << "\n";

    std::cout << "Median age for employed females = " <<
    ComputeMedianAge(persons.begin(), iters.female_employ_end) << "\n";

    std::cout << "Median age for unemployed females = " <<
    ComputeMedianAge(iters.female_employ_end, iters.female_end) << "\n";

    std::cout << "Median age for employed males = " <<
    ComputeMedianAge(iters.female_end, iters.male_employ_end) << "\n";

    std::cout << "Median age for unemployed males = ";
    ComputeMedianAge(iters.male_employ_end, persons.end());
}


int main() {
    vector<Person> persons = {
            {31, Gender::MALE, false},
            {40, Gender::FEMALE, true},
            {24, Gender::MALE, true},
            {20, Gender::FEMALE, true},
            {80, Gender::FEMALE, false},
            {78, Gender::MALE, false},
            {10, Gender::FEMALE, false},
            {55, Gender::MALE, true},
    };
    PrintStats(persons);
    return 0;
}