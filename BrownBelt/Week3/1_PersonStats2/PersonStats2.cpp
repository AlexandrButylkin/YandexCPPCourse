#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <map>
#include <set>

using std::string;
using std::map;
using std::set;
using std::istream;
using std::pair;
using std::cout;
using std::cin;
template <typename T>
auto BinarySearch(const std::vector<T>& vec, T value){
    auto first = 0;
    auto last = vec.size() - 1;
    while(true){
        auto mid = first + (last - first) / 2;

        if(value > *mid){//1 2 3 4 5 6 7 8 9     2      8
            first = mid;
        } else if(value < *mid){
            last = mid;
        } else {
            while(*mid == value) {
                if(mid == vec.begin()){
                    return mid;
                }
                --mid;
            }

            return ++mid;
        }

    }
}

class PersonStats{

public:
    explicit PersonStats(istream& input){
        int count;
        input >> count;

        std::string name;
        int age, income;
        char gender;

        ages.reserve(count);
        incomes.reserve(count);

        map<string, int> males;
        map<string, int> females;

        for(int i = 0; i < count; ++i){
            input >> name >> age >> income >> gender;
            ages.emplace_back(age);
            if(gender == 'M'){
                ++males[name];
            } else {
                ++females[name];
            }
            incomes.emplace_back(income);
        }

        std::sort(ages.begin(), ages.end());
        std::sort(incomes.rbegin(),incomes.rend());
        if(!females.empty())
            female_name = MaxElement(females);
        if(!males.empty())
            male_name = MaxElement(males);

    }

    size_t Age(size_t age) const {
        auto iter = std::lower_bound(ages.begin(), ages.end(), age);
        return ages.end() - iter;
    }

    size_t Wealthy(size_t count) const{
        size_t res = 0;
        return std::accumulate(incomes.begin(), incomes.begin() + std::min(incomes.size(), count), res);
    }

    string PopularName(const char sex) const{
        if(sex == 'M'){
            return male_name;
        } else {
            return female_name;
        }
    }


private:

    static string MaxElement(const map<string, int>& container){
        int curr_count = 0;
        string curr_name;
        for (const auto &item: container) {
            if (item.second > curr_count) {
                curr_count = item.second;
                curr_name = item.first;
            }
        }
        return curr_name;
    }

    std::vector<size_t> ages;

    string female_name = "None";
    string male_name = "None";

    std::vector<size_t> incomes;//массив префиксных сумм

};

int main() {

    PersonStats ps(cin);

    for (string command; cin >> command; ) {
        if (command == "AGE") {
            int adult_age;
            cin >> adult_age;
            ps.Age(adult_age);
            cout << "There are " << ps.Age(adult_age)
                 << " adult people for maturity age " << adult_age << '\n';
        } else if (command == "WEALTHY") {
            int count;
            cin >> count;
            cout << "Top-" << count << " people have total income " << ps.Wealthy(count) << '\n';
        } else if (command == "POPULAR_NAME") {
            char gender;
            cin >> gender;
            string name = ps.PopularName(gender);
            if (name == "None") {
                cout << "No people of gender " << gender << '\n';
            } else {

                cout << "Most popular name among people of gender " << gender << " is "
                     << name << '\n';
            }
        }
    }
}


/*
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <numeric>

using namespace std;

template <typename Iterator>
class IteratorRange {
public:
    IteratorRange(Iterator begin, Iterator end)
            : first(begin)
            , last(end)
    {
    }

    Iterator begin() const {
        return first;
    }

    Iterator end() const {
        return last;
    }

private:
    Iterator first, last;
};

template <typename Collection>
auto Head(Collection& v, size_t top) {
    return IteratorRange{v.begin(), next(v.begin(), min(top, v.size()))};
}

struct Person {
    string name;
    int age, income;
    bool is_male;
};

vector<Person> ReadPeople(istream& input) {
    int count;
    input >> count;

    vector<Person> result(count);
    for (Person& p : result) {
        char gender;
        input >> p.name >> p.age >> p.income >> gender;
        p.is_male = gender == 'M';
    }

    return result;
}

int main() {
    const vector<Person> people_age = [](){
        std::vector<Person> vec = ReadPeople(cin);
        sort(begin(vec), end(vec), [](const Person& lhs, const Person& rhs) {
            return lhs.age < rhs.age;
        });
        return vec;
    }();

    const vector<Person> people_income = [people_age](){
        std::vector<Person> vec = people_age;
        sort(begin(vec), end(vec), [](const Person& lhs, const Person& rhs) {
            return lhs.income > rhs.income;
        });
        return vec;
    }();

    for (string command; cin >> command; ) {
        if (command == "AGE") {
            int adult_age;
            cin >> adult_age;

            auto adult_begin = lower_bound(
                    begin(people_age), end(people_age), adult_age, [](const Person& lhs, int age) {
                        return lhs.age < age;
                    }
            );

            cout << "There are " << std::distance(adult_begin, end(people_age))
                 << " adult people for maturity age " << adult_age << '\n';
        } else if (command == "WEALTHY") {
            int count;
            cin >> count;

            auto head = Head(people_income, count);

            int total_income = accumulate(
                    head.begin(), head.end(), 0, [](int cur,const Person& p) {
                        return cur += p.income;
                    }
            );
            cout << "Top-" << count << " people have total income " << total_income << '\n';
        } else if (command == "POPULAR_NAME") {
            char gender;
            cin >> gender;

            std::vector<Person> vec = people_age;
            IteratorRange range{
                    begin(vec),
                    partition(begin(vec), end(vec), [gender](Person& p) {
                        return p.is_male == (gender == 'M');
                    })
            };

            std::vector<Person> vec2(range.begin(), range.end());


            if (range.begin() == range.end()) {
                cout << "No people of gender " << gender << '\n';
            } else {
                sort(range.begin(), range.end(), [](const Person& lhs, const Person& rhs) {
                    return lhs.name < rhs.name;
                });
                const string* most_popular_name = &range.begin()->name;
                int count = 1;
                for (auto i = range.begin(); i != range.end(); ) {
                    auto same_name_end = find_if_not(i, range.end(), [i](const Person& p) {
                        return p.name == i->name;
                    });
                    auto cur_name_count = std::distance(i, same_name_end);
                    if (cur_name_count > count) {
                        count = cur_name_count;
                        most_popular_name = &i->name;
                    }
                    i = same_name_end;
                }
                cout << "Most popular name among people of gender " << gender << " is "
                     << *most_popular_name << '\n';
            }
        }
    }
}



*/
