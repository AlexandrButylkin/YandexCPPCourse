#include <iostream>
#include "Deque.h"

void foo(Deque<int> const& my_deque) {
    for (size_t i = 0; i < my_deque.Size(); ++i) {
        int a = my_deque.At(i);
        std::cout << a << " ";
    }
    puts("\n1 2 3    expected \n");

}


int main() {
    Deque<int> my_deque;
    my_deque.PushBack(1);
    my_deque.PushFront(2);
    my_deque.PushBack(3);
    my_deque.PushFront(4);
    my_deque.PushFront(5);
    my_deque.PushBack(6);
    my_deque.PushBack(7);
    my_deque.PushBack(8);
    my_deque.PushFront(33);

    for(int i = 0; i < my_deque.Size(); ++i){
        std::cout << my_deque[i] << " ";
    }
    std::cout << std::endl;
    for(int i = 0; i < my_deque.Size(); ++i){
        std::cout << my_deque.At(i) << " ";
    }

    return 0;
}
