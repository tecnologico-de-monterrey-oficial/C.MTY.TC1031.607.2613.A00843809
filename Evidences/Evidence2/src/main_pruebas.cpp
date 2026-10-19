#include <iostream>
#include "../include/LinkedList.h"
#include "../include/Stack.h"
#include "../include/Queue.h"
#include "../include/DoublyLinkedList.h"

using namespace std;

int main() {
    cout << "     PARTE A: PROGRAMA DE PRUEBAS DE ESTRUCTURAS BASE     " << endl;

    // 1. PRUEBAS DE LISTA LIGADA SIMPLE (LinkedList)
    cout << "\n--- 1. PRUEBAS DE LISTA LIGADA SIMPLE (head y tail O(1)) ---" << endl;
    LinkedList<int> lista;
    cout << "Estado inicial (tamaño " << lista.getSize() << "): ";
    lista.print();

    cout << "Intentando eliminar al inicio en lista vacía:" << endl;
    try {
        lista.pop_front();
    } catch (const exception& e) {
        cout << "  [Excepción controlada] " << e.what() << endl;
    }

    cout << "Insertando un solo elemento al inicio (10):" << endl;
    lista.push_front(10);
    cout << "  Lista (tamaño " << lista.getSize() << "): ";
    lista.print();

    cout << "Eliminando el único elemento al inicio:" << endl;
    cout << "  Elemento eliminado: " << lista.pop_front() << " | Tamaño actual: " << lista.getSize() << endl;
    lista.print();

    cout << "Insertando en extremos: push_front(20), push_front(10), push_back(30), push_back(40):" << endl;
    lista.push_front(20);
    lista.push_front(10);
    lista.push_back(30);
    lista.push_back(40);
    cout << "  Lista actual (tamaño " << lista.getSize() << "): ";
    lista.print();

    cout << "Eliminando al inicio (pop_front): " << lista.pop_front() << endl;
    cout << "  Lista resultante (tamaño " << lista.getSize() << "): ";
    lista.print();

    // 2. PRUEBAS DE PILA (Stack - LIFO)
    cout << "\n--- 2. PRUEBAS DE PILA (Stack sobre LinkedList - LIFO) ---" << endl;
    Stack<string> pila;
    cout << "¿Pila vacía?: " << (pila.isEmpty() ? "Sí" : "No") << " | Tamaño: " << pila.size() << endl;

    cout << "Intentando hacer pop() y peek() en Pila vacía:" << endl;
    try {
        pila.pop();
    } catch (const exception& e) {
        cout << "  [Excepción controlada] " << e.what() << endl;
    }
    try {
        pila.peek();
    } catch (const exception& e) {
        cout << "  [Excepción controlada] " << e.what() << endl;
    }

    cout << "Caso de un solo elemento: push(\"Evento_A\")" << endl;
    pila.push("Evento_A");
    cout << "  Tope actual (peek): " << pila.peek() << " | Tamaño: " << pila.size() << endl;
    cout << "  Haciendo pop(): " << pila.pop() << " | ¿Quedó vacía?: " << (pila.isEmpty() ? "Sí" : "No") << endl;

    cout << "Insertando 3 elementos: push(\"Log_1\"), push(\"Log_2\"), push(\"Log_3\"):" << endl;
    pila.push("Log_1");
    pila.push("Log_2");
    pila.push("Log_3");
    cout << "  Tamaño de la pila: " << pila.size() << " | Peek: " << pila.peek() << endl;
    cout << "  Vaciando pila para comprobar orden LIFO (último en entrar, primero en salir):" << endl;
    while (!pila.isEmpty()) {
        cout << "    pop() -> " << pila.pop() << endl;
    }

    // 3. PRUEBAS DE FILA (Queue - FIFO)
    cout << "\n--- 3. PRUEBAS DE FILA (Queue sobre LinkedList - FIFO) ---" << endl;
    Queue<string> fila;
    cout << "¿Fila vacía?: " << (fila.isEmpty() ? "Sí" : "No") << " | Tamaño: " << fila.size() << endl;

    cout << "Intentando hacer dequeue() y front() en Fila vacía:" << endl;
    try {
        fila.dequeue();
    } catch (const exception& e) {
        cout << "  [Excepción controlada] " << e.what() << endl;
    }
    try {
        fila.front();
    } catch (const exception& e) {
        cout << "  [Excepción controlada] " << e.what() << endl;
    }

    cout << "Caso de un solo elemento: enqueue(\"Linea_1\")" << endl;
    fila.enqueue("Linea_1");
    cout << "  Frente actual (front): " << fila.front() << " | Tamaño: " << fila.size() << endl;
    cout << "  Haciendo dequeue(): " << fila.dequeue() << " | ¿Quedó vacía?: " << (fila.isEmpty() ? "Sí" : "No") << endl;

    cout << "Encolando 3 elementos: enqueue(\"Primero\"), enqueue(\"Segundo\"), enqueue(\"Tercero\"):" << endl;
    fila.enqueue("Primero");
    fila.enqueue("Segundo");
    fila.enqueue("Tercero");
    cout << "  Tamaño de la fila: " << fila.size() << " | Frente: " << fila.front() << endl;
    cout << "  Desencolando todo para comprobar orden FIFO (primero en entrar, primero en salir):" << endl;
    while (!fila.isEmpty()) {
        cout << "    dequeue() -> " << fila.dequeue() << endl;
    }


    // PRUEBAS DE LISTA DOBLEMENTE LIGADA (DoublyLinkedList)

    cout << "\n--- 4. PRUEBAS DE LISTA DOBLEMENTE LIGADA ---" << endl;
    DoublyLinkedList<int> listaDoble;
    cout << "Estado inicial (tamaño " << listaDoble.getSize() << "): ";
    listaDoble.printForward();

    cout << "Caso un solo elemento: addFirst(100)" << endl;
    listaDoble.addFirst(100);
    cout << "  Recorrido hacia adelante: ";
    listaDoble.printForward();
    cout << "  Recorrido hacia atrás:    ";
    listaDoble.printBackward();

    cout << "Eliminando ese único nodo (deleteNode(head)):" << endl;
    listaDoble.deleteNode(listaDoble.getHead());
    cout << "  Tamaño actual: " << listaDoble.getSize() << " | ";
    listaDoble.printForward();

    cout << "Insertando al inicio y al final: addFirst(20), addFirst(10), addLast(40), addLast(50)" << endl;
    listaDoble.addFirst(20);
    listaDoble.addFirst(10);
    listaDoble.addLast(40);
    listaDoble.addLast(50);
    cout << "  Adelante (tamaño " << listaDoble.getSize() << "): ";
    listaDoble.printForward();

    cout << "Insertando 30 después del segundo nodo (nodo con valor 20) usando insertAfter:" << endl;
    NodeD<int>* segundoNodo = listaDoble.getHead()->next;
    listaDoble.insertAfter(segundoNodo, 30);
    cout << "  Recorrido hacia adelante: ";
    listaDoble.printForward();
    cout << "  Recorrido hacia atrás:    ";
    listaDoble.printBackward();

    cout << "Eliminando nodo intermedio (valor 30) y extremos (head=10 y tail=50):" << endl;
    listaDoble.deleteNode(segundoNodo->next); // borra el 30
    listaDoble.deleteNode(listaDoble.getHead()); // borra el 10
    listaDoble.deleteNode(listaDoble.getTail()); // borra el 50
    cout << "  Adelante (tamaño " << listaDoble.getSize() << "): ";
    listaDoble.printForward();
    cout << "  Atrás    (tamaño " << listaDoble.getSize() << "): ";
    listaDoble.printBackward();

    cout << "     TODAS LAS PRUEBAS FINALIZARON SIN CERRAR LA APP      " << endl;
   

    return 0;
}