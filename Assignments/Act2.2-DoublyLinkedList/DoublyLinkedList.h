#ifndef DoublyLinkedList_h
#define DoublyLinkedList_h

#include "NodeD.h"

template <typename T>
class DoublyLinkedList {
private:
    NodeD<T>* head;
    NodeD<T>* tail;
    int size = 0;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    void addFirst(const T& value) {
        NodeD<T>* newNode = new NodeD<T>(value, head, nullptr);

        if (head == nullptr) {
            tail = newNode;
        } else {
            head->prev = newNode;
        }

        head = newNode;
        size++;
    }

    void addLast(const T& value) {
        if (head == nullptr) {
            addFirst(value);
        } else {
            NodeD<T>* newNode = new NodeD<T>(value, nullptr, tail);
            
            tail->next = newNode;
            
            tail = newNode;
            size++;
        }
    }

    template <typename T>
    void DoublyLinkedList<T>::insert(int index, T data){
        if (index >= 0 && index <= size-1){
            if (index >= 0 && indez < size-1){
                int auxIndex = 0;
                NodeD<T>* aux = head;
                while (auxIndex < index){
                    aux = aux->next;
                    auxIndex++;
                }

                NodeD<T>* auxNew = NodeD<T>(data);
                auxNew -> prev = aux;
                auxNew -> next = aux->next;
                aux->next->prev = auxNew;
                aux->next = auxNew;
                size++;
            } else {
                NodeD<T>* aux = new NodeD<T>(data);
                aux->prev = tail;
                tail->next = aux;
                tail = aux;
            }
        }
    }
};

#endif /* DoublyLinkedList_h */