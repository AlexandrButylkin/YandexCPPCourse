#ifndef TASK_3_SIMPLE_VECTOR_H
#define TASK_3_SIMPLE_VECTOR_H

#include <iostream>

template <typename T>
class SimpleVector {
public:
    SimpleVector() = default;
    explicit SimpleVector(size_t size) : data_(new T[size]), size_(size), capacity_(size) {}

    T& operator[](size_t index){
        return *(data_ + index);
    }

    T* begin() {return data_;}
    T* end() {return data_ + size_;}
    const T* begin() const {return data_;}
    const T* end() const {return data_ + size_;}

    size_t Size() const {
        return size_;
    }

    size_t Capacity() const {
        return capacity_;
    }

    void PushBack(const T& value){
        if(size_ == capacity_){
            size_t new_capacity = capacity_ * 2 + 1;
            auto new_vector = new T[new_capacity];
            std::copy(begin(), end(), new_vector);
            delete[] data_;
            data_ = new_vector;
            capacity_ = new_capacity;
        }
        data_[size_++] = value;
    }

    ~SimpleVector(){ delete[] data_; }

private:
    T* data_ = nullptr;
    size_t capacity_ = 0;
    size_t size_ = 0;
};



#endif //TASK_3_SIMPLE_VECTOR_H
