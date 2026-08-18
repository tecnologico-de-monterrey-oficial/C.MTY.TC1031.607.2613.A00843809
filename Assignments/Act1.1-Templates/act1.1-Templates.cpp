#include <iostream>
#include "List.h"
using namespace std;

int main(){
    cout << "Lista de enteros" << endl;
    List<int> numeros;

    numeros.insert(5);
    numeros.insert(10);
    numeros.insert(15);

    cout << "Lista inicial" << endl;
    numeros.print();
    cout << "Tamaño de la lista: " << numeros.getSize() << endl;
    cout << "Valor maximo: " << numeros.getMax() << endl;

    cout << "Insertar el numero 20 en la posicion 1" << endl;
    numeros.insertAt(1, 20);
    numeros.print();

    cout << "Eliminando elemento en la posicion 2" << endl;
    numeros.removeAt(2);
    numeros.print();

    cout << "Errores intencionales de preba" << endl;
    numeros.insertAt(10, 100);
    numeros.removeAt(-1);

    cout << "Pruebas con strings" << endl;

    List<string> cosas;
    cosas.insert("Laptop");
    cosas.insert("Celular");
    cosas.insert("Tableta");
    cosas.print();

    return 0;
}