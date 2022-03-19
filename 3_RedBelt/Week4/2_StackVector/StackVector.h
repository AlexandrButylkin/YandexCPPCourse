#ifndef TASK_2_STACKVECTOR_H
#define TASK_2_STACKVECTOR_H

#include <stdexcept>
#include <array>

using namespace std;

template <typename T, size_t N>
class StackVector {
public:
    explicit StackVector(size_t a_size = 0) : size_(a_size) {
        if(a_size > N) {
            throw invalid_argument("Invalid Argument");
        }
    }

    const T& operator[](size_t index) const { return data_[index]; }
    T& operator[](size_t index) {
        return const_cast<T&>(static_cast<const StackVector&>(*this)[index]);
    }

    const T* begin() const { return data_; }
    const T* end() const { return data_ + size; }
    T* begin() { return data_; }
    T* end() { return data_ + size_; }

    size_t Size() const { return size_; }
    size_t Capacity() const { return N; }

    void PushBack(const T& value) {
        if(size_ >= N) {
            throw overflow_error("Overflow error");
        }
        else {
            data_[size_++] = value;
        }

    }

    T PopBack(){
        if(size_ == 0) {
            throw underflow_error("Underflow error");
        }
        else {
            return data_[--size_];
        }
    }

private:
    std::array<T, N> data_;
    size_t size_;
};


#endif //TASK_2_STACKVECTOR_H
