





#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <vector>
#include <list>
using namespace std;

template <typename T>
using Element = std::pair<T, int>;

//const std::_List_iterator<std::pair<StringNonCopyable, int>>
//const std::_List_iterator<std::pair<StringNonCopyable, int>>
template <typename T>
class PriorityCollection {
public:
    using Id = int;
    using Iterator = typename std::map<Element<T>, Id>::iterator;



    // Добавить объект с нулевым приоритетом
    // с помощью перемещения и вернуть его идентификатор
    Id Add(T object) {
        std::cerr << "Add\n";
        Element<T> obj(std::move(object), 0);
        auto it = pool.find(obj);
        if(it != pool.end()){
            iterators[it->second] = it;
            return it->second;
        } else {
            iterators[last_id] = pool.emplace(std::move(obj), last_id).first;
            last_id++;
            return last_id;
        }

        /*
        ++priority_map[0];
        pool.emplace_back(Element<T>(std::move(object), 0));
        auto it = std::prev(pool.end());
        Iterators.emplace(it);
        return it;*/
    }


    // Добавить все элементы диапазона [range_begin, range_end)
    // с помощью перемещения, записав выданные им идентификаторы
    // в диапазон [ids_begin, ...)
    template <typename ObjInputIt, typename IdOutputIt>
    void Add(ObjInputIt range_begin, ObjInputIt range_end,
             IdOutputIt ids_begin){
        std::cerr << "Add_\n";
        for(; range_begin != range_end; ++range_begin){
            auto obj = Element<T>(std::move(*range_begin), 0);
            auto it = pool.find(obj);
            if(it != pool.end()){
                iterators[it->second] = it;
                *ids_begin = it->second;
            } else {
                iterators[last_id] = pool.emplace(std::move(obj), last_id).first;
                *ids_begin = last_id;
                ++ids_begin;
                ++last_id;
            }
        }


        /*for(range_begin; range_begin != std::next(range_end); range_begin = std::next(range_begin)){
            //pool.insert(ids_begin, Element<T>(std::move(*range_begin), 0));

            Iterators.emplace(pool.emplace(ids_begin, Element<T>(std::move(*range_begin), 0)));
            ++priority_map[0];
        }*/
    }

    // Определить, принадлежит ли идентификатор какому-либо
    // хранящемуся в контейнере объекту
    bool IsValid(Id id) const{
        std::cerr << "IsValid\n";
        if(iterators.find(id) != iterators.end()) {
            return true;
        } else return false;
    }

    // Получить объект по идентификатору
    const T& Get(Id id) const{
        std::cerr << "Get\n";
        return iterators.at(id)->first;
    }

    // Увеличить приоритет объекта на 1
    void Promote(Id id){
        std::cerr << "Promote\n" << id << "\n";
        auto iter = iterators[id];

        if(iter->first.second > 0) --priority_map[iter->first.second];
        ++(iter->second);
        ++priority_map[iter->first.second];

        if(max_priority < iter->first.second){
            ++max_priority;
        }


        /*--priority_map[id->second];
        ++(id->second);
        ++priority_map[id->second];
        if(id->second > max_priority){
            ++max_priority;
        }*/
    }

    // Получить объект с максимальным приоритетом и его приоритет
    pair<const T&, int> GetMax() const{
        std::cerr << "GetMax\n";
        return *(iterators.at(find_max_priority()));
    }

    // Аналогично GetMax, но удаляет элемент из контейнера
    pair<T, int> PopMax(){
        std::cerr << "PopMax\n";
        auto id = find_max_priority();
        auto obj_iter = iterators[id];

        //pool.erase(obj_iter);

        iterators.erase(id);

        //std::cerr << " iterators.erase(id);\n";
        --priority_map[obj_iter->second];
        //std::cerr << "--priority_map[obj.second];\n";
        form_max_priority();
        //std::cerr << "form_max_priority();\n";
        return std::move(obj_iter->first);

        /* auto iter = find_max_priority();
         --priority_map[max_priority];
         if(priority_map[max_priority] == 0){
             --max_priority;
         }
         auto iter2 = Iterators.find(iter);
         Iterators.erase(Iterators.find(iter));

         auto obj = std::move(*iter);
         pool.erase(iter);
         return obj;
     */}

private:

    Id find_max_priority() const {
        //std::cerr << "find_max_priority()\n";
        auto iter = std::prev(iterators.end());
        //std::cerr << " auto iter = iterators.end();\n";
        while(iter->second->first.second != max_priority){
            --iter;
            //std::cerr << "--iter;\n";
        }
        //std::cerr << "end\n";
        return iter->first;
        std::cerr << "return iter->first;\n";
        /*auto curr_iter = pool.end();
        while(curr_iter->second != max_priority){
            if(curr_iter->second != max_priority && curr_iter == pool.begin()){
                --max_priority;
                curr_iter = pool.end();
            } else --curr_iter;
        }
        return curr_iter;*/
    }

    void form_max_priority(){
        if(max_priority == 0) return;
        else if(priority_map[max_priority] == 0){
            --max_priority;
            form_max_priority();
            return;
        }
    }

    //std::list<Element<T>> pool;

    std::map<Id, Iterator> iterators;

    std::map<Element<T>, Id> pool;

    std::map<int, int> priority_map;

    int last_id = 0;

    int max_priority= 0;



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

    strings.Promote(yellow_id);
    for (int i = 0; i < 2; ++i) {
        strings.Promote(red_id);
    }
    strings.Promote(yellow_id);
    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "red");
        ASSERT_EQUAL(item.second, 2);
    }
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

int main() {
    //TestRunner tr;
    //RUN_TEST(tr, TestNoCopy);




    //strings.Add(a.begin(), a.end(), id);

    return 0;
}