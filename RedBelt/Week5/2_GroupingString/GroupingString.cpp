#include "test_runner.h"

#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <iostream>

using namespace std;

// Объявляем Group<String> для произвольного типа String
// синонимом vector<String>.
// Благодаря этому в качестве возвращаемого значения
// функции можно указать не малопонятный вектор векторов,
// а вектор групп — vector<Group<String>>.
template <typename String>
using Group = vector<String>;

// Ещё один шаблонный синоним типа
// позволяет вместо громоздкого typename String::value_type
// использовать Char<String>
template <typename String>
using Char = typename String::value_type;

/*template <typename String>
using Key = String;

template <typename String>
Key<String> ComputeStringKey(const String& string) {
    String chars = string;
    sort(begin(chars), end(chars));
    chars.erase(unique(begin(chars), end(chars)), end(chars));
    return chars;
}


template <typename String>
vector<Group<String>> GroupHeavyStrings(vector<String> strings) {
    map<Key<String>, Group<String>> groups_map;
    for (String& string : strings) {
        groups_map[ComputeStringKey(string)].push_back(move(string));
    }
    vector<Group<String>> groups;
    for (auto& [key, group] : groups_map) {
        groups.push_back(move(group));
    }
    return groups;
}*/

/*template <typename String>
vector<Group<String>> GroupHeavyStrings(vector<String> strings) {

    std::vector<Group<String>> res;
    std::map<std::set<Char<String>>, Group<String>> map;
    for (auto &item: strings) map[std::set<Char<String>>(item.begin(), item.end())].push_back(std::move(item));
    for (auto &item: map) res.push_back(std::move(item.second));
    return res;
}*/


template <typename String>
std::set<Char<String>> symbols(String& str){
    return {str.begin(), str.end()};
}

template <typename String>
vector<Group<String>> GroupHeavyStrings(vector<String> strings) {

    std::vector<Group<String>> res;
    uint32_t pos = 0;
    uint32_t res_pos = 0;
    while(true){

        while(strings[pos].empty()) ++pos;
        if(pos >= strings.size()) break;
        auto voc = symbols(strings[pos]);

        res.emplace_back();
        res[res_pos].emplace_back(std::move(strings[pos]));

        for(uint32_t i = pos + 1; i < strings.size(); ++i){

            if(strings[i].empty()) continue;

            if(symbols(strings[i]) == voc) res[res_pos].emplace_back(std::move(strings[i]));

        }
        ++res_pos;
    }
    return res;
}


void TestGroupingABC() {
  vector<string> strings = {"caab", "abc", "cccc", "bacc", "c"};
  auto groups = GroupHeavyStrings(strings);
  ASSERT_EQUAL(groups.size(), 2);
  sort(begin(groups), end(groups));  // Порядок групп не имеет значения
  ASSERT_EQUAL(groups[0], vector<string>({"caab", "abc", "bacc"}));
  ASSERT_EQUAL(groups[1], vector<string>({"cccc", "c"}));
}

void TestGroupingABC1(vector<string>& strings) {
    auto groups = GroupHeavyStrings(strings);
    //ASSERT_EQUAL(groups.size(), 2);
    //sort(begin(groups), end(groups));  // Порядок групп не имеет значения
    //ASSERT_EQUAL(groups[0], vector<string>({"caab", "abc", "bacc"}));
    //ASSERT_EQUAL(groups[1], vector<string>({"cccc", "c"}));
}

void TestGroupingReal() {
  vector<string> strings = {"law", "port", "top", "laptop", "pot", "paloalto", "wall", "awl"};
  auto groups = GroupHeavyStrings(strings);
  ASSERT_EQUAL(groups.size(), 4);
  sort(begin(groups), end(groups));  // Порядок групп не имеет значения
  ASSERT_EQUAL(groups[0], vector<string>({"laptop", "paloalto"}));
  ASSERT_EQUAL(groups[1], vector<string>({"law", "wall", "awl"}));
  ASSERT_EQUAL(groups[2], vector<string>({"port"}));
  ASSERT_EQUAL(groups[3], vector<string>({"top", "pot"}));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestGroupingABC);
  RUN_TEST(tr, TestGroupingReal);

  std::vector<string> str;
  std::string s;
  cin >> s;
  while(s != "0"){
      str.push_back(s);
      cin >> s;
  }


  TestGroupingABC1(str);
  return 0;
}