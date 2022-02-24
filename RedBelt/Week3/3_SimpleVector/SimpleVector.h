#ifndef TASK_3_SIMPLE_VECTOR_H
#define TASK_3_SIMPLE_VECTOR_H

#include <iostream>

template <typename T>
class SimpleVector {
public:
    SimpleVector() : begin_(nullptr), size_(0), capacity_(0) {}

    explicit SimpleVector(size_t size) : size_(size), capacity_(size) {
        begin_ = new T[size];
    }

    T& operator[](size_t index){
        return *(begin_ + index);
    }

    T* begin() {return begin_;}
    T* end() {return begin_ + size_;}

    const T* begin() const {return begin_;}
    const T* end() const {return begin_ + size_;}

    [[nodiscard]] size_t Size() const {
        return size_;
    }

    [[nodiscard]] size_t Capacity() const {
        return capacity_;
    }

    void PushBack(const T& value){
        if(capacity_ == 0) {
            begin_ = new T[1];
            capacity_ = 1;
        } else if(size_ == capacity_){
            auto new_vector = new T[capacity_ * 2];
            std::move(begin(), end(), new_vector);
            delete[] begin_;
            begin_ = new_vector;
            capacity_ *= 2;
        }
        begin_[size_] = value;
        size_++;
    }

    ~SimpleVector(){
        delete[] begin_;
    }

private:
    T* begin_;
    size_t capacity_;
    size_t size_;
};



#endif //TASK_3_SIMPLE_VECTOR_H