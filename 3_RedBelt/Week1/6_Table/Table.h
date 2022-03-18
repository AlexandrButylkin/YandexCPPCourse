#ifndef TASK_6_TABLE_H
#define TASK_6_TABLE_H

#include <vector>

template <typename T>
class Table{
private:
    using Matrix = std::vector<std::vector<T>>;
    Matrix table;

public:
    Table(size_t n, size_t m) : table(n, std::vector<T>(m)) {}

    std::vector<T>& operator[](int index);
    const std::vector<T>& operator[](int index) const;
    std::pair<size_t, size_t> Size() const;
    void Resize(size_t n, size_t m);

};

template <typename T>
std::vector<T>& Table<T>::operator[](int index){
    return table[index];
}

template <typename T>
const std::vector<T>& Table<T>::operator[](int index) const{
    return table[index];
}

template <typename T>
std::pair<size_t, size_t> Table<T>::Size() const{
    if(!table.empty() && !table[0].empty()){
        return {table.size(), table[0].size()};
    } else return {0, 0};
}

template <typename T>
void Table<T>::Resize(size_t n, size_t m){
    table.resize(n);
    for(std::vector<T>& item : table){
        item.resize(m);
    }
}

#endif //TASK_6_TABLE_H
