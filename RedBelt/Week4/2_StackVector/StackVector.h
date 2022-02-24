//
// Created by cobak on 10.01.2022.
//

#ifndef TASK_2_STACK_VECTOR_H
#define TASK_2_STACK_VECTOR_H

#include <stdexcept>
using namespace std;

template <typename T, size_t N>
class StackVector {
public:
    explicit StackVector(size_t a_size = 0) : capacity(N) {
        if(a_size > capacity) throw invalid_argument("invalid argument");
        else size = a_size;
    }

    T& operator[](size_t index) { return data[index]; }
    const T& operator[](size_t index) const { return data[index]; }

    T* begin() { return data; }
    T* end() { return data + size; }
    const T* begin() const { return data; }
    const T* end() const { return data + size; }

    [[nodiscard]] size_t Size() const { return size; }
    [[nodiscard]] size_t Capacity() const { return capacity; }

    void PushBack(const T& value) {
        if(size == capacity) throw overflow_error("overflow error");
        else {
            data[size] = value;
            ++size;
        }

    }

    T PopBack(){
        if(size == 0) throw underflow_error("underflow error");
        else {
            --size;
            return data[size];
        }
    }

private:
    size_t size;
    size_t capacity;
    T data[N];
};


#endif //TASK_2_STACK_VECTOR_H
