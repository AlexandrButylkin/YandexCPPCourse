#ifndef TASK_7_DEQUE_H
#define TASK_7_DEQUE_H

#include <vector>
#include <stdexcept>
#include <iostream>

template <typename T>
class Deque{
private:
    std::vector<T> back1;
    std::vector<T> front1;
public:
    Deque(){};

    bool Empty() const {
        if(back1.empty() && front1.empty()){
            return true;
        } else return false;
    }

    size_t Size() const{
        return back1.size() + front1.size();
    }

    const T& operator[] (size_t index) const {
        if(index >= front1.size()) {
            return back1[index - front1.size()];
        }
        else return front1[front1.size() - index - 1];
    }

    T& operator[] (size_t index) {
        return const_cast<T&>(static_cast<const Deque&>(*this)[index]);
    }

    const T& At(size_t index) const{
        if(index >= back1.size() + front1.size()) throw std::out_of_range{"out of range"};
        else return static_cast<const Deque&>(*this)[index];
    }

    T& At(size_t index){
        return const_cast<T&>(static_cast<const Deque&>(*this).At(index));
    }

    const T& Back() const {
        if(!back1.empty())
            return back1.back();
        else if(!front1.empty()) return front1.front();
    }

    T& Back() {
        return const_cast<T&>(static_cast<const Deque&>(*this).Back());
    }

    const T& Front() const {
        if(!front1.empty())
            return front1.back();
        else if(!back1.empty()) return  back1.front();
    }

    T& Front() {
        return const_cast<T&>(static_cast<const Deque&>(*this).Front());
    }

    void PushBack(const T val){
        back1.push_back(std::move(val));
    }

    void PushFront(const T val){
        front1.push_back(std::move(val));
    }

};

#endif //TASK_7_DEQUE_H
