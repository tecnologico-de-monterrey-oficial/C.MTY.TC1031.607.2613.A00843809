#ifndef DoublyLinkedList_h
#define DoublyLinkedList_h

#include <iostream>
#include <stdexcept>
#include "NodeD.h"

using namespace std;

template <typename T>
class DoublyLinkedList {
private:
    NodeD<T>* head;
    NodeD<T>* tail;
    int size;

    // Regresa el nodo que está en el índice dado
    NodeD<T>* getNode(int index);

    // Métodos auxiliares para Merge Sort directamente sobre los nodos de la lista
    NodeD<T>* split(NodeD<T>* source);
    NodeD<T>* mergeLists(NodeD<T>* first, NodeD<T>* second, long long& comparisons);
    NodeD<T>* mergeSortRec(NodeD<T>* node, int currentDepth, int& maxDepth, long long& comparisons);

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}
    DoublyLinkedList(const DoublyLinkedList<T>& other);
    ~DoublyLinkedList();

    void addFirst(T data);
    void addLast(T data);
    void insert(int index, T data);
    void insertAfter(NodeD<T>* prevNode, T data);
    bool deleteAt(int index);
    bool deleteNode(NodeD<T>* target);
    int findData(T data);
    bool deleteData(T data);
    T getData(int index);
    void updateData(T oldData, T newData);
    void updateAt(int index, T data);
    T& operator[](int index);
    DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>& other);
    void clear();
    void sort(); // Burbuja visto en clase
    void mergeSort(long long& comparisons, int& maxDepth); // Merge Sort Parte B
    bool isSorted();
    void duplicate();
    void removeDuplicates();
    int getSize();
    bool isEmpty();
    NodeD<T>* getHead() const { return head; }
    NodeD<T>* getTail() const { return tail; }
    void print();
    void printForward();
    void printBackward();
};

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& other) : head(nullptr), tail(nullptr), size(0) {
    *this = other;
}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    clear();
}

template <typename T>
NodeD<T>* DoublyLinkedList<T>::getNode(int index) {
    // validamos que el índice sea válido
    if (index < 0 || index >= size) {
        throw out_of_range("Índice inválido");
    }
    NodeD<T>* aux;
    // revisamos por donde empezamos a recorrer la lista
    if (index <= (size - 1) / 2) {
        // recorremos por la izquierda
        aux = head;
        int auxIndex = 0;
        while (auxIndex < index) {
            aux = aux->next;
            auxIndex++;
        }
    } else {
        // recorremos por la derecha
        aux = tail;
        int auxIndex = size - 1;
        while (auxIndex > index) {
            aux = aux->prev;
            auxIndex--;
        }
    }
    return aux;
}

template <typename T>
void DoublyLinkedList<T>::addFirst(T data) {
    // validamos si la lista está vacía
    if (head == nullptr) {
        head = new NodeD<T>(data);
        tail = head;
        size++;
    } else {
        NodeD<T>* aux = new NodeD<T>(data);
        aux->next = head;
        head->prev = aux;
        head = aux;
        size++;
    }
}

template <typename T>
void DoublyLinkedList<T>::addLast(T data) {
    // validamos si la lista está vacía
    if (head == nullptr) {
        head = new NodeD<T>(data);
        tail = head;
        size++;
    } else {
        NodeD<T>* aux = new NodeD<T>(data);
        aux->prev = tail;
        tail->next = aux;
        tail = aux;
        size++;
    }
}

template <typename T>
void DoublyLinkedList<T>::insert(int index, T data) {
    // getNode lanza la excepción si el índice no es válido
    NodeD<T>* aux = getNode(index);
    insertAfter(aux, data);
}

// Inserta un nuevo elemento inmediatamente después de un nodo dado en O(1)
template <typename T>
void DoublyLinkedList<T>::insertAfter(NodeD<T>* prevNode, T data) {
    if (prevNode == nullptr) {
        throw invalid_argument("Error: El nodo de referencia no puede ser nulo.");
    }
    if (prevNode == tail) {
        addLast(data);
    } else {
        NodeD<T>* auxNew = new NodeD<T>(data);
        auxNew->prev = prevNode;
        auxNew->next = prevNode->next;
        prevNode->next->prev = auxNew;
        prevNode->next = auxNew;
        size++;
    }
}

// Elimina un nodo dado directamente mediante su puntero en O(1)
template <typename T>
bool DoublyLinkedList<T>::deleteNode(NodeD<T>* target) {
    if (head == nullptr || target == nullptr) {
        return false;
    }
    if (size == 1 && target == head) {
        delete head;
        head = nullptr;
        tail = nullptr;
    } else if (target == head) {
        head = head->next;
        head->prev = nullptr;
        delete target;
    } else if (target == tail) {
        tail = tail->prev;
        tail->next = nullptr;
        delete target;
    } else {
        target->prev->next = target->next;
        target->next->prev = target->prev;
        delete target;
    }
    size--;
    return true;
}

template <typename T>
bool DoublyLinkedList<T>::deleteAt(int index) {
    if (index < 0 || index >= size) {
        return false;
    }
    NodeD<T>* aux = getNode(index);
    return deleteNode(aux);
}

template <typename T>
int DoublyLinkedList<T>::findData(T data) {
    NodeD<T>* aux = head;
    int auxIndex = 0;
    while (aux != nullptr) {
        if (aux->data == data) {
            return auxIndex;
        }
        aux = aux->next;
        auxIndex++;
    }
    return -1;
}

template <typename T>
bool DoublyLinkedList<T>::deleteData(T data) {
    int index = findData(data);
    if (index == -1) {
        return false;
    }
    return deleteAt(index);
}

template <typename T>
T DoublyLinkedList<T>::getData(int index) {
    return getNode(index)->data;
}

template <typename T>
void DoublyLinkedList<T>::updateData(T oldData, T newData) {
    int index = findData(oldData);
    if (index == -1) {
        throw out_of_range("El dato no se encuentra en la lista");
    }
    getNode(index)->data = newData;
}

template <typename T>
void DoublyLinkedList<T>::updateAt(int index, T data) {
    getNode(index)->data = data;
}

template <typename T>
T& DoublyLinkedList<T>::operator[](int index) {
    return getNode(index)->data;
}

template <typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& other) {
    if (this != &other) {
        clear();
        NodeD<T>* aux = other.head;
        while (aux != nullptr) {
            addLast(aux->data);
            aux = aux->next;
        }
    }
    return *this;
}

template <typename T>
void DoublyLinkedList<T>::clear() {
    while (head != nullptr) {
        NodeD<T>* aux = head;
        head = head->next;
        delete aux;
    }
    tail = nullptr;
    size = 0;
}

template <typename T>
void DoublyLinkedList<T>::sort() {
    bool changed = true;
    int limit = size - 1;
    while (changed && limit > 0) {
        changed = false;
        NodeD<T>* aux = head;
        int auxIndex = 0;
        while (auxIndex < limit) {
            if (aux->next->data < aux->data) {
                T temp = aux->data;
                aux->data = aux->next->data;
                aux->next->data = temp;
                changed = true;
            }
            aux = aux->next;
            auxIndex++;
        }
        limit--;
    }
}

// Divide la sublista en dos mitades usando punteros slow y fast
template <typename T>
NodeD<T>* DoublyLinkedList<T>::split(NodeD<T>* source) {
    NodeD<T>* fast = source->next;
    NodeD<T>* slow = source;

    while (fast != nullptr && fast->next != nullptr) {
        fast = fast->next->next;
        slow = slow->next;
    }

    NodeD<T>* secondHalf = slow->next;
    slow->next = nullptr;
    if (secondHalf != nullptr) {
        secondHalf->prev = nullptr;
    }
    return secondHalf;
}

// Fusiona dos sublistas ordenadas re-enlazando next y prev de forma iterativa y estable
template <typename T>
NodeD<T>* DoublyLinkedList<T>::mergeLists(NodeD<T>* first, NodeD<T>* second, long long& comparisons) {
    if (first == nullptr) return second;
    if (second == nullptr) return first;

    NodeD<T>* mergedHead = nullptr;
    NodeD<T>* mergedTail = nullptr;

    while (first != nullptr && second != nullptr) {
        comparisons++;
        NodeD<T>* chosen = nullptr;
        // Usamos <= para conservar el orden de llegada cuando tienen la misma fecha y hora
        if (first->data <= second->data) {
            chosen = first;
            first = first->next;
        } else {
            chosen = second;
            second = second->next;
        }

        chosen->prev = mergedTail;
        chosen->next = nullptr;

        if (mergedHead == nullptr) {
            mergedHead = chosen;
            mergedTail = chosen;
        } else {
            mergedTail->next = chosen;
            mergedTail = chosen;
        }
    }

    NodeD<T>* remainder = (first != nullptr) ? first : second;
    if (remainder != nullptr) {
        remainder->prev = mergedTail;
        if (mergedTail != nullptr) {
            mergedTail->next = remainder;
        } else {
            mergedHead = remainder;
        }
    }

    return mergedHead;
}

template <typename T>
NodeD<T>* DoublyLinkedList<T>::mergeSortRec(NodeD<T>* node, int currentDepth, int& maxDepth, long long& comparisons) {
    if (currentDepth > maxDepth) {
        maxDepth = currentDepth;
    }
    if (node == nullptr || node->next == nullptr) {
        return node;
    }

    NodeD<T>* second = split(node);

    node = mergeSortRec(node, currentDepth + 1, maxDepth, comparisons);
    second = mergeSortRec(second, currentDepth + 1, maxDepth, comparisons);

    return mergeLists(node, second, comparisons);
}

// Ordena la lista doblemente ligada in-place con Merge Sort
template <typename T>
void DoublyLinkedList<T>::mergeSort(long long& comparisons, int& maxDepth) {
    comparisons = 0;
    maxDepth = 0;
    if (head == nullptr || head->next == nullptr) {
        return;
    }

    head = mergeSortRec(head, 1, maxDepth, comparisons);

    // Reconstruimos tail y aseguramos consistencia de punteros prev
    NodeD<T>* aux = head;
    aux->prev = nullptr;
    while (aux->next != nullptr) {
        aux->next->prev = aux;
        aux = aux->next;
    }
    tail = aux;
}

// Verifica si la lista ya está ordenada de menor a mayor
template <typename T>
bool DoublyLinkedList<T>::isSorted() {
    if (head == nullptr || head->next == nullptr) {
        return true;
    }
    NodeD<T>* aux = head;
    while (aux->next != nullptr) {
        if (aux->next->data < aux->data) {
            return false;
        }
        aux = aux->next;
    }
    return true;
}

template <typename T>
void DoublyLinkedList<T>::duplicate() {
    NodeD<T>* aux = head;
    while (aux != nullptr) {
        NodeD<T>* auxNew = new NodeD<T>(aux->data);
        auxNew->prev = aux;
        auxNew->next = aux->next;
        if (aux->next != nullptr) {
            aux->next->prev = auxNew;
        } else {
            tail = auxNew;
        }
        aux->next = auxNew;
        size++;
        aux = auxNew->next;
    }
}

template <typename T>
void DoublyLinkedList<T>::removeDuplicates() {
    sort();
    NodeD<T>* aux = head;
    while (aux != nullptr && aux->next != nullptr) {
        if (aux->data == aux->next->data) {
            NodeD<T>* borrar = aux->next;
            aux->next = borrar->next;
            if (borrar->next != nullptr) {
                borrar->next->prev = aux;
            } else {
                tail = aux;
            }
            delete borrar;
            size--;
        } else {
            aux = aux->next;
        }
    }
}

template <typename T>
int DoublyLinkedList<T>::getSize() {
    return size;
}

template <typename T>
bool DoublyLinkedList<T>::isEmpty() {
    return size == 0;
}

template <typename T>
void DoublyLinkedList<T>::print() {
    printForward();
}

template <typename T>
void DoublyLinkedList<T>::printForward() {
    if (head == nullptr) {
        cout << "[Lista doblemente ligada vacía]" << endl;
        return;
    }
    NodeD<T>* aux = head;
    while (aux != nullptr) {
        cout << aux->data;
        aux = aux->next;
        if (aux != nullptr) {
            cout << " <-> ";
        }
    }
    cout << endl;
}

template <typename T>
void DoublyLinkedList<T>::printBackward() {
    if (tail == nullptr) {
        cout << "[Lista doblemente ligada vacía]" << endl;
        return;
    }
    NodeD<T>* aux = tail;
    while (aux != nullptr) {
        cout << aux->data;
        aux = aux->prev;
        if (aux != nullptr) {
            cout << " <-> ";
        }
    }
    cout << endl;
}

#endif /* DoublyLinkedList_h */