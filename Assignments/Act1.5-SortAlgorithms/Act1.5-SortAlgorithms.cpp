
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
    bool change = true;
    for (int i = list.size()-1; i>0 && change; i--){
        change = false;
        for (int j = 0; j<i; j++){
            if (list[j] > list[j+1]){
                change = true;
                swap(list, j, j+1);
            }
        }
    }
}

template <typename T>
void insertionSort(vector<T> &list){
    
    for (int i = 1; i <list.size(); i++){
        T key = list[i];
        int j = i-1;
        
        while (j >=0 && list[j] > key){
            list[j+1] = list[j];
            j = j- 1;
        }
        list[j + 1] = key;
    }

    
}

template <typename T>
void selectionSort(vector<T> & list){
    for (int i = 0; i < list.size - 1; i++){
        int minval = i; 

        for (int j = i+1; j < list.size() - 1; j++){
            if (list[j] < list[minval]){
                minval = j;
            }
        }
        if (minval != i){
        swap(list, minval, i);
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
    cout << "Lista ordenada con swapSort: " << endl;
    print(list);
    bubbleSort(list);
    cout << "Lista ordenada con bubbleSort: " << endl;
    print(list);
    insertionSort(list);
    cout << "Lista ordenada con insertionSort: " << endl;
    print(list);
    selectionSort(list);
    cout << "Lista ordenada con selectionSort: " << endl;
    print(list);




    return 0;
}