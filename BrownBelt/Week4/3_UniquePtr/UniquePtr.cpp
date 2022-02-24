#include "test_runner.h"

#include <cstddef>  // нужно для nullptr_t

using namespace std;

// Реализуйте шаблон класса UniquePtr
template<typename T>
class UniquePtr {
private:

    T *ptr_ = nullptr;

public:
    UniquePtr() : ptr_(nullptr) {}

    explicit UniquePtr(T *ptr) : ptr_(ptr) {}

    UniquePtr(const UniquePtr &) = delete;

    UniquePtr(UniquePtr &&other)  noexcept {
        ptr_ = other.ptr_;
        other.ptr_ = nullptr;
    }

    UniquePtr &operator=(const UniquePtr &) = delete;

    UniquePtr &operator=(nullptr_t) {
        delete ptr_;
        ptr_ = nullptr;
        return *this;
    }

    UniquePtr &operator=(UniquePtr &&other)  noexcept {
        delete ptr_;
        ptr_ = other.ptr_;
        other.ptr_ = nullptr;
        return *this;
    }

    T &operator*() const {
        return *ptr_;
    }

    T *operator->() const {
        return ptr_;
    }

    T *Release(){
        T* ptr = ptr_;
        ptr_ = nullptr;
        return ptr;
    }

    void Reset(T *ptr){
        delete ptr_;
        ptr_ = ptr;
    }

    void Swap(UniquePtr &other){
        T* ptr = ptr_;
        ptr_ = other.ptr_;
        other.ptr_ = ptr;
    }

    T *Get() const{
        return ptr_;
    }


    ~UniquePtr() {
        delete ptr_;
    }

};


struct Item {
    static int counter;
    int value;

    Item(int v = 0) : value(v) {
        ++counter;
    }

    Item(const Item &other) : value(other.value) {
        ++counter;
    }

    ~Item() {
        --counter;
    }
};

int Item::counter = 0;


void TestLifetime() {
    Item::counter = 0;
    {
        UniquePtr<Item> ptr(new Item);
        ASSERT_EQUAL(Item::counter, 1);

        ptr.Reset(new Item);
        ASSERT_EQUAL(Item::counter, 1);
    }
    ASSERT_EQUAL(Item::counter, 0);

    {
        UniquePtr<Item> ptr(new Item);
        ASSERT_EQUAL(Item::counter, 1);

        auto rawPtr = ptr.Release();
        ASSERT_EQUAL(Item::counter, 1);

        delete rawPtr;
        ASSERT_EQUAL(Item::counter, 0);
    }
    ASSERT_EQUAL(Item::counter, 0);
}

void TestGetters() {
    UniquePtr<Item> ptr(new Item(42));
    ASSERT_EQUAL(ptr.Get()->value, 42);
    ASSERT_EQUAL((*ptr).value, 42);
    ASSERT_EQUAL(ptr->value, 42);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestLifetime);
    RUN_TEST(tr, TestGetters);
}
