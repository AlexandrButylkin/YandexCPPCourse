#ifndef TASK_1_OBJECTPOOL_H
#define TASK_1_OBJECTPOOL_H

#include <queue>
#include <set>
#include <stdexcept>

template <typename T>
class ObjectPool {
public:
    T* Allocate();
    T* TryAllocate();
    void Deallocate(T* object);
    ~ObjectPool();

private:
    std::queue<T*> freeing;
    std::set<T*> giving;
};

template <typename T>
T* ObjectPool<T>::Allocate(){
    if(freeing.empty()){
        freeing.push(new T);
    }
    auto obj = freeing.front();
    freeing.pop();
    giving.insert(obj);
    return obj;
}

template <typename T>
T* ObjectPool<T>::TryAllocate(){
    if(freeing.empty()){
        return nullptr;
    }
    return Allocate();
}

template <typename T>
void ObjectPool<T>::Deallocate(T* object){
    const auto obj_iter = giving.find(object);
    if(obj_iter == giving.end()){
        throw std::invalid_argument("Invalid argument");
    }

    giving.erase(obj_iter);
    freeing.push(object);
}

template <typename T>
ObjectPool<T>::~ObjectPool(){
    for (auto& item : giving){
        delete item;
    }

    while(!freeing.empty()){
        delete freeing.front();
        freeing.pop();
    }
}

#endif //TASK_1_OBJECTPOOL_H
