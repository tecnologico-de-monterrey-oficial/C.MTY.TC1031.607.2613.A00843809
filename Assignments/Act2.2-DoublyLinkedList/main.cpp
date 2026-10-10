#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "DoublyLinkedList.h"

using namespace std;

void mostrarMenu() {
    cout << "\n===== MENU =====" << endl;
    cout << "1. Agregar al principio" << endl;
    cout << "2. Agregar al final" << endl;
    cout << "3. Insertar a la derecha de un indice" << endl;
    cout << "4. Borrar un elemento dado" << endl;
    cout << "5. Borrar un elemento en una posicion" << endl;
    cout << "6. Obtener el elemento de una posicion" << endl;
    cout << "7. Actualizar un elemento dado" << endl;
    cout << "8. Actualizar el elemento de una posicion" << endl;
    cout << "9. Encontrar un elemento" << endl;
    cout << "10. Obtener elemento de una posicion (operador [])" << endl;
    cout << "11. Actualizar elemento de una posicion (operador [])" << endl;
    cout << "12. Igualar con otra lista (operador =)" << endl;
    cout << "13. Limpiar la lista" << endl;
    cout << "14. Ordenar la lista" << endl;
    cout << "15. Duplicar la lista" << endl;
    cout << "16. Remover elementos duplicados" << endl;
    cout << "0. Salir" << endl;
    cout << "Opcion: ";
}

template <typename T>
void menu(DoublyLinkedList<T>& lista) {
    int opcion, indice;
    T dato, datoNuevo;

    do {
        cout << "\nLista: ";
        lista.print();
        mostrarMenu();
        cin >> opcion;

        // si el indice es invalido, la lista lanza una excepcion
        try {
            switch (opcion) {
                case 1:
                    cout << "Dato: ";
                    cin >> dato;
                    lista.addFirst(dato);
                    break;
                case 2:
                    cout << "Dato: ";
                    cin >> dato;
                    lista.addLast(dato);
                    break;
                case 3:
                    cout << "Indice: ";
                    cin >> indice;
                    cout << "Dato: ";
                    cin >> dato;
                    lista.insert(indice, dato);
                    break;
                case 4:
                    cout << "Dato a borrar: ";
                    cin >> dato;
                    if (lista.deleteData(dato)) {
                        cout << "Dato borrado" << endl;
                    } else {
                        cout << "No se encontro el dato" << endl;
                    }
                    break;
                case 5:
                    cout << "Posicion a borrar: ";
                    cin >> indice;
                    if (lista.deleteAt(indice)) {
                        cout << "Elemento borrado" << endl;
                    } else {
                        cout << "Posicion invalida" << endl;
                    }
                    break;
                case 6:
                    cout << "Posicion: ";
                    cin >> indice;
                    cout << "Elemento: " << lista.getData(indice) << endl;
                    break;
                case 7:
                    cout << "Dato a buscar: ";
                    cin >> dato;
                    cout << "Dato nuevo: ";
                    cin >> datoNuevo;
                    lista.updateData(dato, datoNuevo);
                    break;
                case 8:
                    cout << "Posicion: ";
                    cin >> indice;
                    cout << "Dato nuevo: ";
                    cin >> dato;
                    lista.updateAt(indice, dato);
                    break;
                case 9:
                    cout << "Dato a encontrar: ";
                    cin >> dato;
                    indice = lista.findData(dato);
                    if (indice == -1) {
                        cout << "No se encontro el dato" << endl;
                    } else {
                        cout << "Esta en la posicion " << indice << endl;
                    }
                    break;
                case 10:
                    cout << "Posicion: ";
                    cin >> indice;
                    cout << "Elemento: " << lista[indice] << endl;
                    break;
                case 11:
                    cout << "Posicion: ";
                    cin >> indice;
                    cout << "Dato nuevo: ";
                    cin >> dato;
                    lista[indice] = dato;
                    break;
                case 12: {
                    DoublyLinkedList<T> copia;
                    copia = lista;
                    cout << "Lista copiada: ";
                    copia.print();
                    break;
                }
                case 13:
                    lista.clear();
                    break;
                case 14:
                    lista.sort();
                    break;
                case 15:
                    lista.duplicate();
                    break;
                case 16:
                    lista.removeDuplicates();
                    break;
                case 0:
                    cout << "Adios" << endl;
                    break;
                default:
                    cout << "Opcion invalida" << endl;
            }
        } catch (out_of_range& e) {
            cout << "Error: " << e.what() << endl;
        }
    } while (opcion != 0);
}

int main() {
    srand(time(0));

    int tipo, forma, cantidad;
    cout << "Tipo de dato: 1. int  2. string" << endl;
    cin >> tipo;
    cout << "Crear lista: 1. aleatoria  2. capturada" << endl;
    cin >> forma;
    cout << "Cuantos elementos? ";
    cin >> cantidad;

    if (tipo == 1) {
        DoublyLinkedList<int> lista;
        for (int i = 0; i < cantidad; i++) {
            int dato;
            if (forma == 1) {
                dato = rand() % 100;
            } else {
                cout << "Dato " << i + 1 << ": ";
                cin >> dato;
            }
            lista.addLast(dato);
        }
        menu(lista);
    } else {
        string palabras[] = {"casa", "perro", "gato", "sol", "luna", "mesa"};
        DoublyLinkedList<string> lista;
        for (int i = 0; i < cantidad; i++) {
            string dato;
            if (forma == 1) {
                dato = palabras[rand() % 6];
            } else {
                cout << "Dato " << i + 1 << ": ";
                cin >> dato;
            }
            lista.addLast(dato);
        }
        menu(lista);
    }

    return 0;
}