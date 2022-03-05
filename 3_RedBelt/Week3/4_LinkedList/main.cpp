#include <iostream>
//#include "LinkedList.h"

template <typename T>
class LinkedList {

public:
    struct Node {
        T value;
        Node* next = nullptr;

        explicit Node(const T& value) : value(value), next(nullptr) {}

    };

    void PushFront(const T& value) {
        Node* new_node = new Node(value);

        if(head == nullptr){
            head = new_node;
        } else {
            new_node->next = head;
            head = new_node;
        }
    };

    void InsertAfter(Node* node, const T& value){
        if(node == nullptr) PushFront(value);
        else {
            Node *new_node = new Node(value);
            new_node->next = node->next;
            node->next = new_node;
        }
    }

    void PopFront(){
        if(head != nullptr) {
            auto item = head;
            head = head->next;
            delete item;
        }
    }

    void RemoveAfter(Node* node){
        if(node == nullptr) PopFront();
        else if(node->next != nullptr){
            auto item = node->next;
            node->next = node->next->next;
            delete item;
        }
    }




    Node* GetHead() { return head; }
    const Node* GetHead() const { return head; }


    ~LinkedList(){
        while(head != nullptr){
            auto item = head->next;
            delete head;
            head = item;
        }
    }


private:
    Node* head = nullptr;
};



/*int main() {
    LinkedList<int> list;
    list.PushFront(1);
    list.PushFront(2);
    list.PushFront(3);
    list.PushFront(4);
    list.PushFront(5);

    list.RemoveAfter(list.GetHead());
    list.RemoveAfter(list.GetHead());
    list.RemoveAfter(list.GetHead());
    list.RemoveAfter(list.GetHead());
    list.RemoveAfter(list.GetHead());



    list.PopFront();
    list.PopFront();
    list.PopFront();
    list.PopFront();
    list.PopFront();

    list.InsertAfter(list.GetHead(), 10);
    list.InsertAfter(list.GetHead(), 11);

    list.RemoveAfter(nullptr);
    list.RemoveAfter(nullptr);

    return 0;
}*/
