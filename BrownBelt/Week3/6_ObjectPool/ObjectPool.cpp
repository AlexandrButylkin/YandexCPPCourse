#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>
#include <memory>
using namespace std;

struct Hash {
    using is_transparent = void;
    template<typename T>
    size_t operator()(const T& ptr) const {
        return hash<T>()(ptr);
    }
};

struct KeyEqual {
    using is_transparent = void;
    template <class P, class Q>
    bool operator()(const P& lhs, const Q& rhs) const {
        return to_address(lhs) == to_address(rhs);
    }
};

template <class T>
class ObjectPool {
public:
    T* Allocate(){
        if(freeing.empty()){
            freeing.push(make_unique<T>());
        }
        auto value = move(freeing.front());
        T* key = value.get();
        freeing.pop();
        giving.emplace(move(value));
        return key;
    }

    T* TryAllocate(){
        if(freeing.empty()) return nullptr;
        else return Allocate();
    }

    void Deallocate(T* object){
        auto iter = giving.find(object);
        if(iter == giving.end()) throw invalid_argument("invalid argument");

        freeing.push(move(giving.extract(iter).value()));
    }

private:
    std::queue<std::unique_ptr<T>> freeing;
    std::unordered_set<std::unique_ptr<T>, Hash, KeyEqual> giving;
};

template <class T>
class ObjectPool3 {//дофиксить
public:
    T* Allocate(){
        if(freeing.empty()){
            freeing.push(make_unique<T>());
        }
        auto value = move(freeing.front());
        T* key = value.get();
        freeing.pop();
        giving.emplace(move(value));
        return key;
    }

    T* TryAllocate(){
        if(freeing.empty()) return nullptr;
        else return Allocate();
    }

    void Deallocate(T* object){
        unique_ptr<T> ptr(object);
        auto iter = giving.find(ptr);
        ptr.release();
        if(iter == giving.end()) throw invalid_argument("invalid argument");

        freeing.push(move(giving.extract(iter).value()));
    }

private:
    std::queue<std::unique_ptr<T>> freeing;
    std::unordered_set<std::unique_ptr<T>> giving;
};

template <class T>
class ObjectPool2 {
public:
    T* Allocate(){
        if(freeing.empty()){
            freeing.push(make_unique<T>());
        }
        auto value = move(freeing.front());
        T* key = value.get();
        freeing.pop();
        giving.emplace(move(value));
        return key;
    }

    T* TryAllocate(){
        if(freeing.empty()) return nullptr;
        else return Allocate();
    }

    void Deallocate(T* object){
        unique_ptr<T> ptr(object);
        auto iter = giving.find(ptr);
        ptr.release();
        if(iter == giving.end()) throw invalid_argument("invalid argument");

        freeing.push(move(giving.extract(iter).value()));
    }

private:
    std::queue<std::unique_ptr<T>> freeing;
    std::unordered_set<std::unique_ptr<T>> giving;
};


template <class T>
class ObjectPool1 {
public:
    T* Allocate(){
        if(freeing.empty()){
            freeing.push(make_unique<T>());
        }
        auto value = move(freeing.front());
        T* key = value.get();
        freeing.pop();
        giving.emplace(key, move(value));
        return key;
    }

    T* TryAllocate(){
        if(freeing.empty()) return nullptr;
        else return Allocate();
    }

    void Deallocate(T* object){
        auto iter = giving.find(object);

        if(iter == giving.end()) throw invalid_argument("invalid argument");

        freeing.push(move(iter->second));
        giving.erase(iter);
    }

private:
    std::queue<std::unique_ptr<T>> freeing;
    std::unordered_map<T*, std::unique_ptr<T>> giving;
};

void TestObjectPool() {
    ObjectPool<string> pool;

    auto p1 = pool.Allocate();
    auto p2 = pool.Allocate();
    auto p3 = pool.Allocate();
    auto p4 = pool.Allocate();
    auto p5 = pool.Allocate();
    auto p6 = pool.Allocate();
    auto p7 = pool.Allocate();
    auto p8 = pool.Allocate();
    auto p9 = pool.Allocate();

    *p1 = "first";
    *p2 = "second";
    *p3 = "third";
    *p4 = "first1";
    *p5 = "second1";
    *p6 = "third1";
    *p7 = "first2";
    *p8 = "second2";
    *p9 = "third2";

    std::cout << *p1 << std::endl;
    std::cout << *p2 << std::endl;
    std::cout << *p3 << std::endl;
    std::cout << *p4 << std::endl;
    std::cout << *p5 << std::endl;
    std::cout << *p6 << std::endl;
    std::cout << *p7 << std::endl;
    std::cout << *p8 << std::endl;
    std::cout << *p9 << std::endl;


    pool.Deallocate(p2);
    ASSERT_EQUAL(*pool.Allocate(), "second");

    pool.Deallocate(p3);
    pool.Deallocate(p1);
    ASSERT_EQUAL(*pool.Allocate(), "third");
    ASSERT_EQUAL(*pool.Allocate(), "first");

    pool.Deallocate(p1);
}

int counter = 0;

class Counter {
public:
    Counter() { ++counter; }
    ~Counter() { --counter; }
};

void run() {
    ObjectPool<Counter> pool;

    try {
        for (int i = 0; i < 1000; ++i) {
            std::cout << "Allocating: " << i << endl;
            pool.Allocate();
        }
        std::cout << "Counter after loop = " << counter << std::endl;
    } catch (const std::bad_alloc& mes){
        std::cout << mes.what() << std::endl;
    }
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestObjectPool);

    run();
    std::cout << "Counter before exit = " << counter << std::endl;
    return 0;

}