#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
using namespace std;

template <class T>
class ObjectPool {
public:
    T* Allocate(){
        if(!freeing.empty()){
            return RealocateFreengToGiving();
        } else {
            return *(giving.emplace(new T).first);
        }
    }

    T* TryAllocate(){
        if(!freeing.empty()){
            return RealocateFreengToGiving();
        } else {
            return nullptr;
        }
    }

    void Deallocate(T* object){

        auto iter = giving.find(object);
        if(iter != giving.end()) {
            RealocateGivingToFreeing(iter);
        } else throw invalid_argument("invalid argument");
    }

    ~ObjectPool(){
        for (auto& item : giving){
            delete item;
        }

        while(!freeing.empty()){
            delete freeing.front();
            freeing.pop();
        }
    }

private:
    std::queue<T*> freeing;
    std::set<T*> giving;

    T* RealocateFreengToGiving(){
        T* obj = freeing.front();
        freeing.pop();
        giving.emplace(obj);
        return obj;
    }

    void RealocateGivingToFreeing(typename std::set<T*>::iterator & iter){
        T *obj = *iter;
        giving.erase(iter);
        freeing.push(obj);
    }

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

    pool.Deallocate(p2);
    ASSERT_EQUAL(*pool.Allocate(), "second");

    pool.Deallocate(p3);
    pool.Deallocate(p1);
    ASSERT_EQUAL(*pool.Allocate(), "third");
    ASSERT_EQUAL(*pool.Allocate(), "first");

    pool.Deallocate(p1);
}

int main() {
    ObjectPool<string> pool;

    for(int i = 0; i < 100; ++i){
        auto p1 = pool.Allocate();
    }

    TestRunner tr;
    RUN_TEST(tr, TestObjectPool);
    return 0;
}