#if !defined(Queue_h)
#define Queue_h

using namespace std;
#include "Node.h"
#include <iostream>

template <typename T>
class Queue {
private:
    Node<T>* head;
    Node<T>* tail;
    int size;
    
public:
    Queue() : head(nullptr), tail(nullptr), size(0) {}
    void push(T data);
    void pop();
    T front();
    void print();
};

template <typename T>
void Queue<T>::pop() {
    if (head != nullptr) {
        if (head == tail) {
            Node<T>* aux = head;
            delete aux;
            head = nullptr;
            tail = nullptr;
        } else {
            Node<T>* aux = head;
            
            head = head->next;
            
            delete aux;
        }
        size--;
    }
}

template <typename T>
void Queue<T>::push(T data) {

    if (head != nullptr){
        tail -> next = new Node<T>(data);
        tail = tail -> next;
    } else {
        head = new Node<T>(data);
        tail = head;
    }
    
}

#endif