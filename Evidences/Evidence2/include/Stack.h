#ifndef Stack_h
#define Stack_h

#include <iostream>
#include <stdexcept>
#include "LinkedList.h"

using namespace std;

template <typename T>
class Stack {
private:
    LinkedList<T> list;
public:
    Stack() {}
    void push(T data);
    T pop();
    T peek();
    bool isEmpty();
    int size();
    void clear();
    void print();
};

// Insertar al tope de la pila en O(1)
template <typename T>
void Stack<T>::push(T data) {
    list.push_front(data);
}

// Eliminar y regresar el tope de la pila en O(1)
template <typename T>
T Stack<T>::pop() {
    if (isEmpty()) {
        throw runtime_error("Error: No se puede hacer pop sobre una Pila vacía.");
    }
    return list.pop_front();
}

// Consultar el tope de la pila sin eliminarlo en O(1)
template <typename T>
T Stack<T>::peek() {
    if (isEmpty()) {
        throw runtime_error("Error: No se puede hacer peek sobre una Pila vacía.");
    }
    return list.getFront();
}

template <typename T>
bool Stack<T>::isEmpty() {
    return list.isEmpty();
}

template <typename T>
int Stack<T>::size() {
    return list.getSize();
}

template <typename T>
void Stack<T>::clear() {
    list.clear();
}

template <typename T>
void Stack<T>::print() {
    list.print();
}

#endif