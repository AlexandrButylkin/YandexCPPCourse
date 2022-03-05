#include <iostream>
#include <vector>
using namespace std;

enum class Gender {
    FEMALE,
    MALE
};

struct Person {
    int age;  // возраст
    Gender gender;  // пол
    bool is_employed;  // имеет ли работу
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

void PrintStats(vector<Person> persons){

    std::vector<Person> females;
    std::vector<Person> males;

    for(const auto& item : persons){
        if(item.gender == Gender::FEMALE){
            females.push_back(item);
        } else males.push_back(item);
    }

    sort(females.begin(), females.end());
    sort(males.begin(), males.end());

    auto empFemale = find_if(females.begin(), females.end(), [](const Person& person){return person.is_employed;});
    auto empMale = find_if(males.begin(), males.end(), [](const Person& person){return person.is_employed;});

    std::cout << "Median age = " << ComputeMedianAge(persons.begin(), persons.end()) << std::endl;
    std::cout << "Median age for females = " << ComputeMedianAge(females.begin(), females.end()) << std::endl;
    std::cout << "Median age for males = " << ComputeMedianAge(males.begin(), males.end()) << std::endl;
    std::cout << "Median age for employed females = " << ComputeMedianAge(empFemale, females.end()) << std::endl;
    std::cout << "Median age for unemployed females = " << ComputeMedianAge(females.begin(), empFemale) << std::endl;
    std::cout << "Median age for employed males = " << ComputeMedianAge(empMale, males.end()) << std::endl;
    std::cout << "Median age for unemployed males = " << ComputeMedianAge(males.begin(), empMale) << std::endl;

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