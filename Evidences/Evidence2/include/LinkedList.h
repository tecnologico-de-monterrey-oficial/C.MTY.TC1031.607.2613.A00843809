#ifndef LinkedList_h
#define LinkedList_h

#include <iostream>
#include <stdexcept>
#include "Node.h"

using namespace std;

template <typename T>
class LinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    int size;
public:
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}
    LinkedList(const LinkedList<T>& other);
    ~LinkedList();
    void push_front(T data);
    void push_back(T data);
    T pop_front();
    T getFront();
    T getBack();
    void insert(int index, T data);
    bool deleteData(T data);
    bool deleteAt(int index);
    T getData(int index);
    void updateData(T data, T newData);
    void updateAt(int index, T newData);
    int findData(T data);
    T& operator[](int index);
    LinkedList<T>& operator=(const LinkedList<T>& other);
    int getSize();
    bool isEmpty();
    void clear();
    void print();
};

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& other) : head(nullptr), tail(nullptr), size(0) {
    *this = other;
}

template <typename T>
LinkedList<T>::~LinkedList() {
    clear();
}

// Insertar al inicio en O(1)
template <typename T>
void LinkedList<T>::push_front(T data) {
    Node<T>* node = new Node<T>(data);
    if (head == nullptr) {
        head = node;
        tail = node;
    } else {
        node->next = head;
        head = node;
    }
    size++;
}

// Insertar al final en O(1) usando tail
template <typename T>
void LinkedList<T>::push_back(T data) {
    Node<T>* node = new Node<T>(data);
    if (head == nullptr) {
        head = node;
        tail = node;
    } else {
        tail->next = node;
        tail = node;
    }
    size++;
}

// Eliminar al inicio en O(1)
template <typename T>
T LinkedList<T>::pop_front() {
    if (head == nullptr) {
        throw runtime_error("Error: La estructura está vacía, no se puede eliminar al inicio.");
    }
    Node<T>* aux = head;
    T valor = aux->data;
    head = head->next;
    if (head == nullptr) {
        tail = nullptr;
    }
    delete aux;
    size--;
    return valor;
}

template <typename T>
T LinkedList<T>::getFront() {
    if (head == nullptr) {
        throw runtime_error("Error: La estructura está vacía, no hay elemento al inicio.");
    }
    return head->data;
}

template <typename T>
T LinkedList<T>::getBack() {
    if (tail == nullptr) {
        throw runtime_error("Error: La estructura está vacía, no hay elemento al final.");
    }
    return tail->data;
}

template <typename T>
void LinkedList<T>::insert(int index, T data) {
    if (index < 0 || index > size) {
        throw out_of_range("Índice fuera de rango");
    }
    if (index == 0) {
        push_front(data);
        return;
    }
    if (index == size) {
        push_back(data);
        return;
    }
    Node<T>* node = new Node<T>(data);
    Node<T>* aux = head;
    for (int i = 0; i < index - 1; i++) {
        aux = aux->next;
    }
    node->next = aux->next;
    aux->next = node;
    size++;
}

template <typename T>
bool LinkedList<T>::deleteData(T data) {
    if (head == nullptr) return false;

    if (head->data == data) {
        pop_front();
        return true;
    }

    Node<T>* aux = head;
    while (aux->next != nullptr) {
        if (aux->next->data == data) {
            Node<T>* nodeToDelete = aux->next;
            aux->next = nodeToDelete->next;
            if (nodeToDelete == tail) {
                tail = aux;
            }
            delete nodeToDelete;
            size--;
            return true;
        }
        aux = aux->next;
    }
    return false;
}

template <typename T>
bool LinkedList<T>::deleteAt(int index) {
    if (index < 0 || index >= size) {
        return false;
    }
    if (index == 0) {
        pop_front();
        return true;
    }
    Node<T>* aux = head;
    for (int i = 0; i < index - 1; i++) {
        aux = aux->next;
    }
    Node<T>* nodeToDelete = aux->next;
    aux->next = nodeToDelete->next;
    if (nodeToDelete == tail) {
        tail = aux;
    }
    delete nodeToDelete;
    size--;
    return true;
}

template <typename T>
T LinkedList<T>::getData(int index) {
    if (index < 0 || index >= size) {
        throw out_of_range("Índice fuera de rango");
    }
    Node<T>* aux = head;
    for (int i = 0; i < index; i++) {
        aux = aux->next;
    }
    return aux->data;
}

template <typename T>
void LinkedList<T>::updateData(T data, T newData) {
    Node<T>* aux = head;
    while (aux != nullptr) {
        if (aux->data == data) {
            aux->data = newData;
            return;
        }
        aux = aux->next;
    }
    throw out_of_range("El dato no se encuentra en la lista");
}

template <typename T>
void LinkedList<T>::updateAt(int index, T newData) {
    if (index < 0 || index >= size) {
        throw out_of_range("Índice fuera de rango");
    }
    Node<T>* aux = head;
    for (int i = 0; i < index; i++) {
        aux = aux->next;
    }
    aux->data = newData;
}

template <typename T>
int LinkedList<T>::findData(T data) {
    Node<T>* aux = head;
    int index = 0;
    while (aux != nullptr) {
        if (aux->data == data) {
            return index;
        }
        aux = aux->next;
        index++;
    }
    return -1;
}

template <typename T>
T& LinkedList<T>::operator[](int index) {
    if (index < 0 || index >= size) {
        throw out_of_range("Índice fuera de rango");
    }
    Node<T>* aux = head;
    for (int i = 0; i < index; i++) {
        aux = aux->next;
    }
    return aux->data;
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other) {
    if (this != &other) {
        clear();
        Node<T>* auxOther = other.head;
        while (auxOther != nullptr) {
            this->push_back(auxOther->data);
            auxOther = auxOther->next;
        }
    }
    return *this;
}

template <typename T>
int LinkedList<T>::getSize() {
    return size;
}

template <typename T>
bool LinkedList<T>::isEmpty() {
    return size == 0;
}

template <typename T>
void LinkedList<T>::clear() {
    while (head != nullptr) {
        Node<T>* aux = head;
        head = head->next;
        delete aux;
    }
    tail = nullptr;
    size = 0;
}

template <typename T>
void LinkedList<T>::print() {
    if (head == nullptr) {
        cout << "[Lista vacía]" << endl;
        return;
    }
    Node<T>* aux = head;
    while (aux != nullptr) {
        cout << aux->data;
        aux = aux->next;
        if (aux != nullptr) {
            cout << " -> ";
        }
    }
    cout << endl;
}

#endif