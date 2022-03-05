#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <vector>
#include <list>
#include <map>
#include <optional>

using namespace std;

template <typename T>
class PriorityCollection {
public:
    using Id = size_t;

    PriorityCollection() : curr_id(0) {}


    // Добавить объект с нулевым приоритетом
    // с помощью перемещения и вернуть его идентификатор
    Id Add(T object){
        data.emplace_back(ObjectWithPriority{std::move(object), 0});
        ids.emplace(std::make_pair(0, curr_id));
        return curr_id++;
    }

    // Добавить все элементы диапазона [range_begin, range_end)
    // с помощью перемещения, записав выданные им идентификаторы
    // в диапазон [ids_begin, ...)
    template <typename ObjInputIt, typename IdOutputIt>
    void Add(ObjInputIt range_begin, ObjInputIt range_end,
             IdOutputIt ids_begin){
        while(range_begin != range_end) {
            *ids_begin++ = Add(std::move(*range_begin++));
        }
    }

    // Определить, принадлежит ли идентификатор какому-либо
    // хранящемуся в контейнере объекту
    bool IsValid(Id id) const{
        if(id >= 0 && id < data.size()){
            return data[id].priority_.has_value();
        }
        return  false;
    }

    // Получить объект по идентификатору
    const T& Get(Id id) const{
        return data[id].value_;
    }

    // Увеличить приоритет объекта на 1
    void Promote(Id id){

        auto& item = data[id];
        ids.erase({item.priority_.value(), id});
        ++item.priority_.value();
        ids.emplace(std::pair<size_t, Id>(item.priority_.value(), id));

    }

    // Получить объект с максимальным приоритетом и его приоритет
    pair<const T&, int> GetMax() const{
        auto iter = std::prev(ids.end());
        return {data[iter->second].value_, data[iter->second].priority_.value()};
    }

    // Аналогично GetMax, но удаляет элемент из контейнера
    pair<T, int> PopMax(){

        auto iter = std::prev(ids.end());

        T object = std::move(data[iter->second].value_);
        size_t priority = iter->first;


        std::pair<T, int> p = std::make_pair(std::move(object), priority);
        data[iter->second].priority_ = std::optional<size_t>();
        ids.erase(std::prev(ids.end()));

        return p;
    }

private:

    struct ObjectWithPriority{
        T value_;
        std::optional<size_t> priority_ = 0;
    };

    std::vector<ObjectWithPriority> data;
    std::set<std::pair<size_t, Id>> ids;

    Id curr_id;
};

template <typename T>
class PriorityCollection1 {
public:
    using Id = size_t;

    PriorityCollection1() : curr_id(0), curr_priority(0) {
        data.emplace_back();
    }


    // Добавить объект с нулевым приоритетом
    // с помощью перемещения и вернуть его идентификатор
    Id Add(T object){
        ids.emplace_back(data[0].emplace(curr_id, ObjectWithPriority({std::move(object), 0})).first);
        return curr_id++;
    }

    // Добавить все элементы диапазона [range_begin, range_end)
    // с помощью перемещения, записав выданные им идентификаторы
    // в диапазон [ids_begin, ...)
    template <typename ObjInputIt, typename IdOutputIt>
    void Add(ObjInputIt range_begin, ObjInputIt range_end,
             IdOutputIt ids_begin){
        while(range_begin != range_end) {
            *ids_begin++ = Add(std::move(*range_begin++));
        }
    }

    // Определить, принадлежит ли идентификатор какому-либо
    // хранящемуся в контейнере объекту
    bool IsValid(Id id) const{
        if(id < ids.size()){
            return ids[id].has_value();
        }
        return  false;
    }

    // Получить объект по идентификатору
    const T& Get(Id id) const{
        auto iter = ids[id].value();
        return iter->second.value_;
    }

    // Увеличить приоритет объекта на 1
    void Promote(Id id){
        if(curr_priority == ids[id].value()->second.priority_){
            data.emplace_back();
            ++curr_priority;
        }

        auto iter = ids[id].value();
        ObjectWithPriority object = std::move(iter->second);
        data[object.priority_].erase(id);

        ++object.priority_;
        ids[id] = data[object.priority_].emplace(id, std::move(object)).first;

    }

    // Получить объект с максимальным приоритетом и его приоритет
    pair<const T&, int> GetMax() const{
        return {std::prev(data.back().end())->second.value_, data.size() - 1};
    }

    // Аналогично GetMax, но удаляет элемент из контейнера
    pair<T, int> PopMax(){
        size_t key = std::prev(data.back().end())->first;
        T value = std::move(std::prev(data.back().end())->second.value_);

        std::pair<T, int> p = std::make_pair(std::move(value), data.size() - 1);
        data.back().erase(std::prev(data.back().end()));
        ids[key] = std::optional<typename std::map<Id, ObjectWithPriority>::iterator>();

        DellEmptyPrioritiesMaps();

        return p;
    }

private:
    void DellEmptyPrioritiesMaps(){
        while(data.back().size() == 0 && data.size() > 1){
            data.pop_back();
            --curr_priority;
        }
    }

    struct ObjectWithPriority{
        T value_;
        size_t priority_ = 0;
    };

    std::vector<std::map<Id, ObjectWithPriority>> data;
    std::vector<std::optional<typename std::map<Id, ObjectWithPriority>::iterator>> ids;

    Id curr_id;
    size_t curr_priority;
};


class StringNonCopyable : public string {
public:
    using string::string;  // Позволяет использовать конструкторы строки
    StringNonCopyable(const StringNonCopyable&) = delete;
    StringNonCopyable(StringNonCopyable&&) = default;
    StringNonCopyable& operator=(const StringNonCopyable&) = delete;
    StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

void TestNoCopy() {
    PriorityCollection<StringNonCopyable> strings;
    const auto white_id = strings.Add("white");
    const auto yellow_id = strings.Add("yellow");
    const auto red_id = strings.Add("red");

    bool flag1 = strings.IsValid(white_id);
    bool flag2 = strings.IsValid(yellow_id);
    bool flag3 = strings.IsValid(red_id);
    bool flag4 = strings.IsValid(6);

    auto& a = strings.Get(white_id);
    auto& b = strings.Get(yellow_id);
    auto& c = strings.Get(red_id);

    strings.Promote(yellow_id);
    auto d = strings.GetMax();
    for (int i = 0; i < 2; ++i) {
        strings.Promote(red_id);
    }
    strings.Promote(yellow_id);
    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "red");
        ASSERT_EQUAL(item.second, 2);
    }
    bool flag6 = strings.IsValid(red_id);
    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "yellow");
        ASSERT_EQUAL(item.second, 2);
    }
    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "white");
        ASSERT_EQUAL(item.second, 0);
    }
}

/*void TestNoCopy1() {
    PriorityCollection<StringNonCopyable> strings;
    std::string str = "gg";
    std::vector<size_t> ids;
    ids.reserve(100);
    for(int i = 0; i < 100; ++i){
        ids.push_back(strings.Add("str"));
    }
    for(auto& item : ids){
        auto a = strings.GetMax();
        auto b = strings.PopMax();
    }

}*/

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestNoCopy);
    return 0;
}





