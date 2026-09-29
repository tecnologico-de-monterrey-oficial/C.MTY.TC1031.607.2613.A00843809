#ifndef Stack_h
#define Stack_h

using namespace std;
#include "Node.h"
#include <iostream>

template <typename T>
class Stack {
private:
    Node<T>* top;
    int size;
    
public:
    Stack() : top(nullptr), size(0) {}
    void push(T data);
    void pop();
    T getTop();
    void print();
};

template <typename T>
void Stack<T>::push(T data) {
    Node<T>* node = new Node<T>(data);
    
    node->next = top;
    top = node;
    size++;
}

template <typename T>
void Stack<T>::pop() {
    if (top == nullptr) return;
    
    Node<T>* temp = top;
    top = top->next;
    
    delete temp;
    size--;
}

template <typename T>
T Stack<T>::getTop() {
    if (top != nullptr) {
        return top->data;
    }
    return T();
}

template <typename T>
void Stack<T>::print() {
    Node<T>* temp = top;
    cout << "Stack: ";
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

#endif