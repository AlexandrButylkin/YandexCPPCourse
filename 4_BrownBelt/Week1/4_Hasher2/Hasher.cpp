#include "../../Utils/TestRunner.h"
#include <random>
#include <unordered_set>

using namespace std;

struct Address {
    string city, street;
    int building;

    bool operator==(const Address& other) const {
        return std::tie(city, street, building) ==
               std::tie(other.city, other.street, other.building);
    }
};

struct Person {
    string name;
    int height;
    double weight;
    Address address;

    bool operator==(const Person& other) const {
        return std::tie(name, height, weight, address) ==
               std::tie(other.name, other.height, other.weight, other.address);
    }
};

struct AddressHasher {

    size_t operator() (const Address& addr) const{
        size_t h1 = sHash(addr.city);
        size_t h2 = sHash(addr.street);
        size_t h3 = iHash(addr.building);
        return h1 * CONST * CONST + h2 * CONST + h3;
    }

    const size_t CONST = 514'229;
    const std::hash<int> iHash = {};
    const std::hash<string> sHash = {};

};

struct PersonHasher {

    size_t operator() (const Person& pers) const{
        size_t h1 = sHash(pers.name);
        size_t h2 = iHash(pers.height);
        size_t h3 = dHash(pers.weight);
        size_t h4= aHash(pers.address);

        return  h1 * CONST * CONST * CONST +
                h2 * CONST * CONST +
                h3 * CONST + h4;
    }

    const size_t CONST = 39'916'801;
    const std::hash<int> iHash = {};
    const std::hash<string> sHash = {};
    const std::hash<double> dHash = {};
    const AddressHasher aHash = {};

};

const vector<string> WORDS = {
        "Kieran", "Jong", "Jisheng", "Vickie", "Adam", "Simon", "Lance",
        "Everett", "Bryan", "Timothy", "Daren", "Emmett", "Edwin", "List",
        "Sharon", "Trying", "Dan", "Saad", "Kamiya", "Nikolai", "Del",
        "Casper", "Arthur", "Mac", "Rajesh", "Belinda", "Robin", "Lenora",
        "Carisa", "Penny", "Sabrina", "Ofer", "Suzanne", "Pria", "Magnus",
        "Ralph", "Cathrin", "Phill", "Alex", "Reinhard", "Marsh", "Tandy",
        "Mongo", "Matthieu", "Sundaresan", "Piotr", "Ramneek", "Lynne", "Erwin",
        "Edgar", "Srikanth", "Kimberly", "Jingbai", "Lui", "Jussi", "Wilmer",
        "Stuart", "Grant", "Hotta", "Stan", "Samir", "Ramadoss", "Narendra",
        "Gill", "Jeff", "Raul", "Ken", "Rahul", "Max", "Agatha",
        "Elizabeth", "Tai", "Ellen", "Matt", "Ian", "Toerless", "Naomi",
        "Rodent", "Terrance", "Ethan", "Florian", "Rik", "Stanislaw", "Mott",
        "Charlie", "Marguerite", "Hitoshi", "Panacea", "Dieter", "Randell", "Earle",
        "Rajiv", "Ted", "Mann", "Bobbie", "Pat", "Olivier", "Harmon",
        "Raman", "Justin"
};

void TestSmoke() {
    vector<Person> points = {
            {"John", 180, 82.5, {"London", "Baker St", 221}},
            {"Sherlock", 190, 75.3, {"London", "Baker St", 221}},
    };

    unordered_set<Person, PersonHasher> point_set;
    for (const auto& point : points) {
        point_set.insert(point);
    }

    ASSERT_EQUAL(points.size(), point_set.size());
    for (const auto& point : points) {
        ASSERT_EQUAL(point_set.count(point), static_cast<size_t>(1));
    }
}

void TestPurity() {
    Person person = {"John", 180, 82.5, {"London", "Baker St", 221}};
    PersonHasher hasher;

    auto hash = hasher(person);
    for (size_t t = 0; t < 100; ++t) {
        ASSERT_EQUAL(hasher(person), hash);
    }
};

void TestDistribution() {
    auto seed = 42;
    mt19937 gen(seed);

    uniform_int_distribution<int> height_dist(150, 200);
    uniform_int_distribution<int> weight_dist(100, 240);  // [50, 120]
    uniform_int_distribution<int> building_dist(1, 300);
    uniform_int_distribution<int> word_dist(0, WORDS.size() - 1);

    PersonHasher hasher;
    const size_t num_buckets = 2053;

    const size_t perfect_bucket_size = 50;
    const size_t num_points = num_buckets * perfect_bucket_size;
    vector<size_t> buckets(num_buckets);
    for (size_t t = 0; t < num_points; ++t) {
        Person person;
        person.name = WORDS[word_dist(gen)];
        person.height = height_dist(gen);
        person.weight = weight_dist(gen) * 0.5;
        person.address.city = WORDS[word_dist(gen)];
        person.address.street = WORDS[word_dist(gen)];
        person.address.building = building_dist(gen);
        ++buckets[hasher(person) % num_buckets];
    }

    double pearson_stat = 0;
    for (auto bucket_size : buckets) {
        size_t size_diff = bucket_size - perfect_bucket_size;
        pearson_stat +=
                size_diff * size_diff / static_cast<double>(perfect_bucket_size);
    }

    const double critical_value = 2158.4981036918693;
    ASSERT(pearson_stat < critical_value);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestSmoke);
    RUN_TEST(tr, TestPurity);
    RUN_TEST(tr, TestDistribution);
    return 0;
}
