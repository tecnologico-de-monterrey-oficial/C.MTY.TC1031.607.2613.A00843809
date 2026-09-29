#ifndef LinkedList_h
#define LinkedList_h
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