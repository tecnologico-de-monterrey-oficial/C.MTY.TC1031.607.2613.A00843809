#ifndef Queue_h
#define Queue_h

#include <iostream>
#include <stdexcept>
#include "LinkedList.h"

using namespace std;

template <typename T>
class Queue {
private:
    LinkedList<T> list;
public:
    Queue() {}
    void enqueue(T data);
    T dequeue();
    T front();
    bool isEmpty();
    int size();
    void clear();
    void print();
};

// Encolar al final de la fila en O(1)
template <typename T>
void Queue<T>::enqueue(T data) {
    list.push_back(data);
}

// Desencolar del frente de la fila en O(1)
template <typename T>
T Queue<T>::dequeue() {
    if (isEmpty()) {
        throw runtime_error("Error: No se puede hacer dequeue sobre una Fila vacía.");
    }
    return list.pop_front();
}

// Consultar el frente de la fila en O(1)
template <typename T>
T Queue<T>::front() {
    if (isEmpty()) {
        throw runtime_error("Error: No se puede consultar front sobre una Fila vacía.");
    }
    return list.getFront();
}

template <typename T>
bool Queue<T>::isEmpty() {
    return list.isEmpty();
}

template <typename T>
int Queue<T>::size() {
    return list.getSize();
}

template <typename T>
void Queue<T>::clear() {
    list.clear();
}

template <typename T>
void Queue<T>::print() {
    list.print();
}

#endif