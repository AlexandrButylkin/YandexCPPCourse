#include <iostream>
#include "Deque.h"
#include "../../Utils/TestRunner.h"

void foo(Deque<int> const& my_deque) {
    for (size_t i = 0; i < my_deque.Size(); ++i) {
        int a = my_deque.At(i);
        std::cout << a << " ";
    }
    puts("\n1 2 3    expected \n");

}

void TestEmptySize(){
    Deque<int> deque;
    ASSERT_EQUAL(deque.Empty(), true);
    deque.PushBack(1);
    ASSERT_EQUAL(deque.Empty(), false);
    ASSERT_EQUAL(deque.Size(), 1);
    deque.PushBack(1);
    ASSERT_EQUAL(deque.Size(), 2);
}

void TestBackFront(){
    Deque<int> deque;
    deque.PushBack(1);
    deque.PushFront(-1);
    ASSERT_EQUAL(deque.Size(), 2);
    ASSERT_EQUAL(deque.Back(), 1);
    ASSERT_EQUAL(deque.Front(), -1);

    deque.PushBack(2);
    deque.PushBack(3);
    ASSERT_EQUAL(deque.Size(), 4);
    ASSERT_EQUAL(deque.Back(), 3);
    ASSERT_EQUAL(deque.Front(), -1);

    deque.PushFront(-2);
    deque.PushFront(-3);
    ASSERT_EQUAL(deque.Size(), 6);
    ASSERT_EQUAL(deque.Back(), 3);
    ASSERT_EQUAL(deque.Front(), -3);
}

void TestAt() {
    Deque<int> deque;

    deque.PushBack(1);
    deque.PushBack(2);
    deque.PushBack(3);

    deque.PushFront(-1);
    deque.PushFront(-2);
    deque.PushFront(-3);

    ASSERT_EQUAL(deque.Size(), 6);
    ASSERT_EQUAL(deque[0], -3);
    ASSERT_EQUAL(deque[1], -2);
    ASSERT_EQUAL(deque[2], -1);
    ASSERT_EQUAL(deque[3], 1);
    ASSERT_EQUAL(deque[4], 2);
    ASSERT_EQUAL(deque[5], 3);

    ASSERT_EQUAL(deque.At(0), -3);
    ASSERT_EQUAL(deque.At(1), -2);
    ASSERT_EQUAL(deque.At(2), -1);
    ASSERT_EQUAL(deque.At(3), 1);
    ASSERT_EQUAL(deque.At(4), 2);
    ASSERT_EQUAL(deque.At(5), 3);
}

void TestRvalue(){
    Deque<std::string> deque;
    std::string str = "test";

    deque.PushBack(str);
    ASSERT_EQUAL(deque.Size(), 1);
    ASSERT_EQUAL(deque.Back(), "test");
    ASSERT_EQUAL(str, "test");

    deque.PushBack(std::move(str));
    ASSERT_EQUAL(deque.Size(), 2);
    ASSERT_EQUAL(deque.Back(), "test");
    ASSERT_EQUAL(str, "");
}

void RunTests(){
    TestRunner tr;
    RUN_TEST(tr, TestEmptySize);
    RUN_TEST(tr, TestBackFront);
    RUN_TEST(tr, TestAt);
    RUN_TEST(tr, TestRvalue);
}

int main() {
    RunTests();

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
