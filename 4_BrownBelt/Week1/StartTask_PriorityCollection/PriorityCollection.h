#ifndef TASK_6_PRIORITYCOLLECTION_H
#define TASK_6_PRIORITYCOLLECTION_H

#include <vector>
#include <set>
#include <map>

template <typename T>
class PriorityCollection {
public:
    using Id = size_t;

    PriorityCollection() = default;

    Id Add(T object){
        data.emplace_back(ObjectWithPriority{std::move(object), 0});
        ids.emplace(std::make_pair(0, curr_id));
        return curr_id++;
    }

    template <typename ObjInputIt, typename IdOutputIt>
    void Add(ObjInputIt range_begin, ObjInputIt range_end,
             IdOutputIt ids_begin){
        while(range_begin != range_end) {
            *ids_begin++ = Add(std::move(*range_begin++));
        }
    }

    bool IsValid(Id id) const{
        if(id >= 0 && id < data.size()){
            return data[id].priority_ != NONE_OBJECT;
        }
        return false;
    }

    const T& Get(Id id) const{
        return data[id].value_;
    }

    void Promote(Id id){

        auto& item = data[id];
        ids.erase({item.priority_, id});

        ++item.priority_;
        ids.emplace(std::pair<size_t, Id>(item.priority_, id));

    }

    pair<const T&, int> GetMax() const{
        auto iter = std::prev(ids.end());
        return {data[iter->second].value_, data[iter->second].priority_};
    }

    pair<T, int> PopMax(){

        auto iter = std::prev(ids.end());

        T object = std::move(data[iter->second].value_);
        size_t priority = iter->first;

        std::pair<T, int> p = std::make_pair(std::move(object), priority);
        data[iter->second].priority_ = NONE_OBJECT;
        ids.erase(std::prev(ids.end()));

        return p;
    }

private:

    struct ObjectWithPriority{
        T value_;
        size_t priority_ = 0;
    };

    const size_t NONE_OBJECT = -1;

    std::vector<ObjectWithPriority> data;
    std::set<std::pair<size_t, Id>> ids;

    Id curr_id = 0;
};


#endif //TASK_6_PRIORITYCOLLECTION_H
