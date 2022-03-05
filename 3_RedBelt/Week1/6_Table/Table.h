#ifndef TASK_6_TABLE_H
#define TASK_6_TABLE_H

#include <vector>
#include <map>

template <typename It>
class myIterator{
private:
    It it;
public:
    myIterator(It it_) : it(std::move(it_)){};

    auto& operator[] (size_t index){
        return *(it->begin() + index);
    }

    auto& operator[] (size_t index) const{
        return *(it->begin() + index);
    }
};

template <typename T>
class Table{
private:
    std::vector<std::vector<T>> table;

public:
    Table(size_t n, size_t m){
        table.resize(n);
        for(std::vector<T>& item : table){
            item.resize(m);
        }
    }

    /*std::vector<T>& operator[](size_t index){
        return table[index];
    }

    const std::vector<T>& operator[](size_t index) const{
        return table[index];
    }*/

    myIterator<typename std::vector<std::vector<T>>::iterator> operator[](int index){
        return (table.begin() + index);
    }

    myIterator<typename std::vector<std::vector<T>>::iterator> operator[](int index) const{
        return (table.begin() + index);
    }

    std::pair<size_t, size_t> Size() const{
        if(!table.empty() && !table[0].empty()){
            return {table.size(), table[0].size()};
        } else return {0, 0};
    }

    void Resize(size_t n, size_t m){
        table.resize(n);
        for(std::vector<T>& item : table){
            item.resize(m);
        }
    }

};



#endif //TASK_6_TABLE_H
