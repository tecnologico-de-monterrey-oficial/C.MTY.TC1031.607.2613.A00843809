#include <iostream>
#include "LinkedList.h"
#include <cstdlib>
#include <ctime>
using namespace std;

template <typename T>
void operacionesMenu(LinkedList<T>& list) {
    int opcion = -1;
    T dato, nuevoDato;
    int indice;
    LinkedList<T> listaCopia;

    while (opcion != 0) {
        cout << "MENU DE OPERACIONES";
        cout << "1. addFirst (Insertar al inicio)\n";
        cout << "2. addLast (Insertar al final)\n";
        cout << "3. insert (Insertar en indice)\n";
        cout << "4. deleteData (Borrar elemento por valor)\n";
        cout << "5. deleteAt (Borrar en indice)\n";
        cout << "6. getData (Leer elemento en indice)\n";
        cout << "7. updateData (Actualizar un elemento)\n";
        cout << "8. updateAt (Actualizar elemento en indice)\n";
        cout << "9. findData (Buscar elemento)\n";
        cout << "10. Sobrecarga [] (Leer elemento en indice)\n";
        cout << "11. Sobrecarga = (Igualar a otra lista)\n";
        cout << "12. Imprimir lista\n";
        cout << "0. Salir\n";
        cout << "Elige una opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            cout << "Dato a insertar: ";
            cin >> dato;
            list.push_front(dato);
            list.print();
        } 
        else if (opcion == 2) {
            cout << "Dato a insertar: ";
            cin >> dato;
            list.push_back(dato);
            list.print();
        } 
        else if (opcion == 3) {
            cout << "Indice donde insertar: ";
            cin >> indice;
            cout << "Dato: ";
            cin >> dato;
            list.insert(indice, dato);
            list.print();
        } 
        else if (opcion == 4) {
            cout << "Dato a borrar: ";
            cin >> dato;
            if (list.deleteData(dato)) {
                cout << "Dato borrado exitosamente";
            } else {
                cout << "El dato no se encontro en la lista.";
            }
            list.print();
        } 
        else if (opcion == 5) {
            cout << "Indice a borrar: ";
            cin >> indice;
            if (list.deleteAt(indice)) {
                cout << "Dato borrado exitosamente.";
            } else {
                cout << "Error: Indice invalido.";
            }
            list.print();
        } 
        else if (opcion == 6) {
            cout << "Indice a leer: ";
            cin >> indice;
            cout << "El dato es: " << list.getData(indice) << "\n";
        } 
        else if (opcion == 7) {
            cout << "Dato viejo a buscar: ";
            cin >> dato;
            cout << "Nuevo dato de reemplazo: ";
            cin >> nuevoDato;
            list.updateData(dato, nuevoDato);
            list.print();
        } 
        else if (opcion == 8) {
            cout << "Indice a actualizar: ";
            cin >> indice;
            cout << "Nuevo dato: ";
            cin >> nuevoDato;
            list.updateAt(indice, nuevoDato);
            list.print();
        } 
        else if (opcion == 9) {
            cout << "Dato a buscar: ";
            cin >> dato;
            indice = list.findData(dato);
            if (indice != -1) {
                cout << "Dato encontrado en el indice: " << indice << "\n";
            } else {
                cout << "Dato no encontrado (Regresa -1).";
            }
        } 
        else if (opcion == 10) {
            cout << "Indice a leer (usando operador []): ";
            cin >> indice;
            cout << "El dato es: " << list[indice] << "\n";
        } 
        else if (opcion == 11) {
            listaCopia = list;
            cout << "Lista duplicada con exito.\n";
            cout << "Imprimiendo lista original: ";
            list.print();
            cout << "Imprimiendo lista copia:    ";
            listaCopia.print();
        } 
        else if (opcion == 12) {
            list.print();
        } 
        else if (opcion == 0) {
            cout << "Saliendo del programa...";
        } 
        else {
            cout << "Opcion invalida, intenta de nuevo.";
        }
    }
}

int main() {
    srand(time(0)); 
    int tipoDato, tipoLlenado, cantidad;

    cout << "CREACION DE LISTA ENLAZADA\n";
    cout << "Selecciona el tipo de datos para tu lista:\n";
    cout << "1. Enteros (int)\n";
    cout << "2. Letras (char)\n";
    cout << "Opcion: ";
    cin >> tipoDato;

    cout << "\nSelecciona como llenar la lista inicialmente:\n";
    cout << "1. Generar datos aleatorios\n";
    cout << "2. Capturar datos manualmente\n";
    cout << "Opcion: ";
    cin >> tipoLlenado;

    cout << "\n¿Cuantos elementos quieres que tenga la lista para empezar?: ";
    cin >> cantidad;

    if (tipoDato == 1) { 
        LinkedList<int> listaEnteros;
        if (tipoLlenado == 1) {
            for (int i = 0; i < cantidad; i++) {
                listaEnteros.push_back(rand() % 100); 
            }
        } else {
            for (int i = 0; i < cantidad; i++) {
                int val;
                cout << "Ingresa el entero " << i + 1 << ": ";
                cin >> val;
                listaEnteros.push_back(val);
            }
        }
        cout << "\nLista inicial creada: ";
        listaEnteros.print();
        operacionesMenu(listaEnteros); 

    } else { 
        LinkedList<char> listaLetras;
        if (tipoLlenado == 1) {
            for (int i = 0; i < cantidad; i++) {
                listaLetras.push_back('A' + (rand() % 26)); 
            }
        } else {
            for (int i = 0; i < cantidad; i++) {
                char val;
                cout << "Ingresa la letra " << i + 1 << ": ";
                cin >> val;
                listaLetras.push_back(val);
            }
        }
        cout << "\nLista inicial creada: ";
        listaLetras.print();
        operacionesMenu(listaLetras); 
    }

    return 0;
}