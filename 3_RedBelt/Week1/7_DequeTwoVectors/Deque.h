#ifndef TASK_7_DEQUE_H
#define TASK_7_DEQUE_H

#include <vector>
#include <stdexcept>
#include <iostream>

template <typename T>
class Deque{
public:
    Deque() = default;;

    bool Empty() const;
    size_t Size() const;

    const T& operator[] (size_t index) const;
    T& operator[] (size_t index);

    const T& At(size_t index) const;
    T& At(size_t index);

    const T& Back() const;
    T& Back();

    const T& Front() const;
    T& Front();

    void PushBack(const T& val);
    void PushFront(const T& val);

    void PushBack(T&& val);
    void PushFront(T&& val);

private:


    std::vector<T> back;
    std::vector<T> front;

};

template <typename T>
bool Deque<T>::Empty() const {
    return back.empty() && front.empty();
}

template <typename T>
size_t Deque<T>::Size() const{
    return back.size() + front.size();
}

template <typename T>
const T& Deque<T>::operator[] (size_t index) const {
    if(index >= front.size()) {
        return back[index - front.size()];
    }
    else return front[front.size() - index - 1];
}

template <typename T>
T& Deque<T>::operator[] (size_t index) {
    return const_cast<T&>(static_cast<const Deque&>(*this)[index]);
}

template <typename T>
const T& Deque<T>::At(size_t index) const{
    if(index >= back.size() + front.size()) {
        throw std::out_of_range{"Out of range, size: " + Size()};
    }
    else {
        return static_cast<const Deque&>(*this)[index];
    }
}

template <typename T>
T& Deque<T>::At(size_t index){
    return const_cast<T&>(static_cast<const Deque&>(*this).At(index));
}

template <typename T>
const T& Deque<T>::Back() const {
    if(back.empty())
        return front.front();
    else
        return back.back();
}

template <typename T>
T& Deque<T>::Back() {
    return const_cast<T&>(static_cast<const Deque&>(*this).Back());
}

template <typename T>
const T& Deque<T>::Front() const {
    if(front.empty())
        return back.front();
    else
        return front.back();
}

template <typename T>
T& Deque<T>::Front() {
    return const_cast<T&>(static_cast<const Deque&>(*this).Front());
}

template <typename T>
void Deque<T>::PushBack(const T& val){
    back.push_back(val);
}

template <typename T>
void Deque<T>::PushFront(const T& val){
    front.push_back(val);
}

template <typename T>
void Deque<T>::PushBack(T&& val){
    back.push_back(std::move(val));
}

template <typename T>
void Deque<T>::PushFront(T&& val){
    front.push_back(std::move(val));
}

#endif //TASK_7_DEQUE_H
