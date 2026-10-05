#ifndef LinkedList_h
#define LinkedList_h
#include <iostream>
using namespace std;

#include "Node.h"

template <typename T>
class LinkedList {
private:
    Node<T>* head;
    int size;
public:
    LinkedList() : head(nullptr), size(0) {}
    void push_front(T data);
    void push_back(T data);
    void insert(int index, T data);
    bool deleteData(T data);
    bool deleteAt(int index);
    T getData(int index);
    void updateData(T data, T newData);
    void updateAt(int index, T newData);
    int findData(T data);
    T& operator[](int index);
    void operator=(const LinkedList<T>& other);
    void print();
};

template <typename T>
void LinkedList<T>::push_front(T data) {
    // crear un nodo nuevo
    Node<T>* node = new Node<T>(data);

    node ->next = head;
    head = node;
    size++;

}

template <typename T>
void LinkedList<T>::push_back(T data) {
    Node<T>* node = new Node<T>(data);

    if (head != nullptr) {
        Node<T>* aux = head;
        while (aux->next != nullptr) {
            aux = aux->next;
        }
        aux->next = new Node<T>(data);
    } else {
        head = new Node<T>(data);
        size++;
    }
}

template <typename T>
void LinkedList<T>::insert(int index, T data){
    if (index < 0 || index > size) {
        cout << "Out of range" << endl;
    }

    if (index == 0) {
        push_front(data);
    }

    if (index == size) {
        push_back(data);
    }

    Node<T>* node = new Node<T>(data);
    Node<T>* aux = head;

    for (int i = 0; i < index - 1; i++){
        aux = aux -> next;
    }
    node -> next = aux -> next;
    aux -> next = node;

    size++;
}

template <typename T>
bool LinkedList<T>::deleteData(T data) {
    if (head == nullptr) return false;

    if (head->data == data) {
        Node<T>* aux = head;
        head = head->next;
        delete aux;
        size--;
        return true;
    }

    Node<T>* aux = head;
    while (aux->next != nullptr) {
        if (aux->next->data == data) {
            Node<T>* nodeToDelete = aux->next;
            aux->next = aux->next->next;
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
        Node<T>* aux = head;
        head = head->next;
        delete aux;
        size--;
        return true;
    }

    Node<T>* aux = head;
    for (int i = 0; i < index - 1; i++) {
        aux = aux->next;
    }
    
    Node<T>* nodeToDelete = aux->next;
    aux->next = aux->next->next;
    delete nodeToDelete;
    size--;
    return true;
}

template <typename T>
T LinkedList<T>::getData(int index) {
    if (index < 0 || index >= size) {
        cout << "Out_Of_Range" << endl;
        return T(); // Regresa un valor por defecto vacío
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
    cout << "Out_Of_Range" << endl; 
}

template <typename T>
void LinkedList<T>::updateAt(int index, T newData) {
    if (index < 0 || index >= size) {
        cout << "Out_Of_Range" << endl;
        return;
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
        cout << "Out_Of_Range" << endl;
        static T dummy; 
        return dummy;
    }
    Node<T>* aux = head;
    for (int i = 0; i < index; i++) {
        aux = aux->next;
    }
    return aux->data; 
}

template <typename T>
void LinkedList<T>::operator=(const LinkedList<T>& other) {
    while (head != nullptr) {
        Node<T>* aux = head;
        head = head->next;
        delete aux;
    }
    size = 0;

    Node<T>* auxOther = other.head;
    while (auxOther != nullptr) {
        this->push_back(auxOther->data);
        auxOther = auxOther->next;
    }
}

template <typename T>
void LinkedList<T>::print() {
    Node<T>* aux = head;
    while (aux != nullptr) {
        cout << aux->data;
        aux = aux->next;
        if (aux != nullptr) {
            cout << "-";
        }
    }
    cout << endl;
}

#endif LinkedList_h