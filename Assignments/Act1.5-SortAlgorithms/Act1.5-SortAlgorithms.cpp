// David Alonso Cantú Delgado
// A00189239
#include <iostream>
#include <vector>

using namespace std;

template <typename T>
void swap(vector<T> &list, int i, int j) {
    // creamos una variable temporal
    T aux = list[i];
    // cambiamos i por j
    list[i] = list[j];
    // cambiamos j por aux
    list[j] = aux;
}

template <typename T>
void swapSort(vector<T> &list) {
    // iteramos todos los elementos de la lista hasta el penultimo
    for (int i=0; i < list.size()-1; i++) {
        for (int j=i+1; j<list.size(); j++) {
            // comparamos el valor de j con el valor de i para determinar si es menor
            if (list[j] < list[i]) {
                // si es menor
                // intercambiamos los valores
                swap(list, i, j);
            }
        }
    }
}

template <typename T>
void bubbleSort(vector<T> &list){
    for (int i = list.size()-1; i>0 && change; i--){
        for (int j = 0; j<i; j++){
            if (list[j] > list[j+1]){
                change = true;
                swap(list, j, j+1);
            }
        }
    }
}


void print(vector<int> &list) {
    for (int i=0; i<list.size(); i++) {
        cout << list[i] << " ";
    }
    cout << endl;
}

int main() {

    vector<int> list = {15, 7, 3, 9, 12, 5, 2};
    cout << "Lista original: " << endl;
    print(list);
    swapSort(list);
    cout << "Lista ordenada: " << endl;
    print(list);



    return 0;
}