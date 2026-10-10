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
    // regresa el nodo que está en el índice dado
    NodeD<T>* getNode(int index);
public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}
    DoublyLinkedList(const DoublyLinkedList<T>& other);
    ~DoublyLinkedList();
    void addFirst(T data);
    void addLast(T data);
    void insert(int index, T data);
    bool deleteAt(int index);
    int findData(T data);
    bool deleteData(T data);
    T getData(int index);
    void updateData(T oldData, T newData);
    void updateAt(int index, T data);
    T& operator[](int index);
    DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>& other);
    void clear();
    void sort();
    void duplicate();
    void removeDuplicates();
    int getSize();
    void print();
};

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& other) : head(nullptr), tail(nullptr), size(0) {
    // reutilizamos el operador =
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
        // si está vacía la lista
        // apunto head a un nuevo nodo con data
        head = new NodeD<T>(data);
        // apunto tail a head
        tail = head;
        // incremento size
        size++;
    } else {
        // la lista no está vacía
        // creamos un nuevo nodo
        NodeD<T>* aux = new NodeD<T>(data);
        // apuntamos el next de aux a head
        aux->next = head;
        // apuntamos el prev de head a aux
        head->prev = aux;
        // apuntamos head a aux
        head = aux;
        // incrementamos size
        size++;
    }
}

template <typename T>
void DoublyLinkedList<T>::addLast(T data) {
    // validamos si la lista está vacía
    if (head == nullptr) {
        // si está vacía la lista
        // apunto head a un nuevo nodo con data
        head = new NodeD<T>(data);
        // apunto tail a head
        tail = head;
        // incremento size
        size++;
    } else {
        // la lista no está vacía
        // creamos un nuevo nodo
        NodeD<T>* aux = new NodeD<T>(data);
        // apuntamos el prev de aux a tail
        aux->prev = tail;
        // apuntamos el next de tail a aux
        tail->next = aux;
        // apuntamos tail a aux
        tail = aux;
        // incrementamos size
        size++;
    }
}

template <typename T>
void DoublyLinkedList<T>::insert(int index, T data) {
    // getNode lanza la excepción si el índice no es válido
    NodeD<T>* aux = getNode(index);
    // validamos si el índice es el último
    if (aux == tail) {
        // insertar a la derecha del último es agregar al final
        addLast(data);
    } else {
        // el index es desde 0 hasta el penúltimo (en medio)
        // creamos un nodo nuevo
        NodeD<T>* auxNew = new NodeD<T>(data);
        // el prev del nuevo lo apuntamos a aux
        auxNew->prev = aux;
        // el next del nuevo lo apuntamos a aux->next
        auxNew->next = aux->next;
        // el prev del siguiente de aux lo apuntamos al nuevo
        aux->next->prev = auxNew;
        // apuntamos aux next al nuevo
        aux->next = auxNew;
        // incrementamos size
        size++;
    }
}

template <typename T>
bool DoublyLinkedList<T>::deleteAt(int index) {
    // validamos si el índice es válido
    if (index < 0 || index >= size) {
        // índice inválido
        return false;
    }
    // validamos si solo hay un elemento
    if (size == 1) {
        // solo hay un elemento
        delete head;
        // apuntamos a nulos head y tail
        head = nullptr;
        tail = nullptr;
    } else if (index == 0) {
        // queremos borrar el primero
        NodeD<T>* aux = head;
        // apuntamos head al siguiente elemento
        head = head->next;
        // actualizamos el apuntador prev de head
        head->prev = nullptr;
        // liberamos aux
        delete aux;
    } else if (index == size - 1) {
        // queremos borrar el último
        NodeD<T>* aux = tail;
        // apuntamos tail al elemento previo
        tail = tail->prev;
        // actualizamos el apuntador next de tail
        tail->next = nullptr;
        // liberamos aux
        delete aux;
    } else {
        // borramos el de en medio
        NodeD<T>* aux = getNode(index);
        // actualizamos el next de aux->prev que apunte a aux->next
        aux->prev->next = aux->next;
        // actualizamos el prev de aux->next que apunte a aux->prev
        aux->next->prev = aux->prev;
        // liberamos aux
        delete aux;
    }
    // decrementamos size
    size--;
    return true;
}

template <typename T>
int DoublyLinkedList<T>::findData(T data) {
    // creamos un apuntador auxiliar
    NodeD<T>* aux = head;
    // inicializamos un índice auxiliar en 0
    int auxIndex = 0;
    // recorremos la lista
    while (aux != nullptr) {
        // validamos si lo encontramos
        if (aux->data == data) {
            return auxIndex;
        }
        // recorremos aux e incrementamos auxIndex
        aux = aux->next;
        auxIndex++;
    }
    // data no se encuentra en la lista
    return -1;
}

template <typename T>
bool DoublyLinkedList<T>::deleteData(T data) {
    // buscamos el dato
    int index = findData(data);
    // validamos si no se encontró
    if (index == -1) {
        return false;
    }
    // lo borramos por su posición
    return deleteAt(index);
}

template <typename T>
T DoublyLinkedList<T>::getData(int index) {
    // getNode lanza la excepción si el índice no es válido
    return getNode(index)->data;
}

template <typename T>
void DoublyLinkedList<T>::updateData(T oldData, T newData) {
    // buscamos el dato
    int index = findData(oldData);
    // validamos si no se encontró
    if (index == -1) {
        throw out_of_range("El dato no se encuentra en la lista");
    }
    // actualizamos el dato
    getNode(index)->data = newData;
}

template <typename T>
void DoublyLinkedList<T>::updateAt(int index, T data) {
    // getNode lanza la excepción si el índice no es válido
    getNode(index)->data = data;
}

template <typename T>
T& DoublyLinkedList<T>::operator[](int index) {
    // regresamos una referencia para poder leer y actualizar
    return getNode(index)->data;
}

template <typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& other) {
    // validamos que no sea la misma lista
    if (this != &other) {
        // limpiamos la lista actual
        clear();
        // recorremos la otra lista y copiamos cada dato
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
    // mientras haya nodos, borramos el primero
    while (head != nullptr) {
        NodeD<T>* aux = head;
        head = head->next;
        delete aux;
    }
    // dejamos la lista vacía
    tail = nullptr;
    size = 0;
}

template <typename T>
void DoublyLinkedList<T>::sort() {
    // ordenamiento burbuja intercambiando los datos de los nodos
    bool changed = true;
    int limit = size - 1;
    while (changed && limit > 0) {
        changed = false;
        NodeD<T>* aux = head;
        int auxIndex = 0;
        while (auxIndex < limit) {
            // si están desordenados, los intercambiamos
            if (aux->next->data < aux->data) {
                T temp = aux->data;
                aux->data = aux->next->data;
                aux->next->data = temp;
                changed = true;
            }
            aux = aux->next;
            auxIndex++;
        }
        // el mayor ya quedó al final
        limit--;
    }
}

template <typename T>
void DoublyLinkedList<T>::duplicate() {
    NodeD<T>* aux = head;
    while (aux != nullptr) {
        // creamos una copia del nodo actual
        NodeD<T>* auxNew = new NodeD<T>(aux->data);
        // el prev de la copia es aux
        auxNew->prev = aux;
        // el next de la copia es el siguiente de aux
        auxNew->next = aux->next;
        // validamos si aux era el último
        if (aux->next != nullptr) {
            aux->next->prev = auxNew;
        } else {
            tail = auxNew;
        }
        // apuntamos aux next a la copia
        aux->next = auxNew;
        size++;
        // saltamos la copia para no duplicarla otra vez
        aux = auxNew->next;
    }
}

template <typename T>
void DoublyLinkedList<T>::removeDuplicates() {
    // primero ordenamos para que los repetidos queden juntos
    sort();
    NodeD<T>* aux = head;
    while (aux != nullptr && aux->next != nullptr) {
        // validamos si el siguiente es igual
        if (aux->data == aux->next->data) {
            // borramos el siguiente
            NodeD<T>* borrar = aux->next;
            aux->next = borrar->next;
            // validamos si borramos el último
            if (borrar->next != nullptr) {
                borrar->next->prev = aux;
            } else {
                tail = aux;
            }
            delete borrar;
            size--;
        } else {
            // avanzamos
            aux = aux->next;
        }
    }
}

template <typename T>
int DoublyLinkedList<T>::getSize() {
    return size;
}

template <typename T>
void DoublyLinkedList<T>::print() {
    NodeD<T>* aux = head;
    while (aux != nullptr) {
        cout << aux->data << " ";
        aux = aux->next;
    }
    cout << endl;
}

#endif /* DoublyLinkedList_h */