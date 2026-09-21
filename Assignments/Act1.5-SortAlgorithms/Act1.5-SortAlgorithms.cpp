
#include <iostream>
#include <vector>

using namespace std;

template <typename T>
void swap(vector<T> &list, int i, int j) {
    if (i != j){
        // creamos una variable temporal
        T aux = list[i];
        // cambiamos i por j
        list[i] = list[j];
        // cambiamos j por aux
        list[j] = aux;
    }
    
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
        
        while (j > 0 && list[j] > key){
            list[j+1] = list[j];
            j = j- 1;
        }
        list[j + 1] = key;
    }

    
}

template <typename T>
void selectionSort(vector<T> & list){
    for (int i = 0; i < list.size() - 1; i++){
        int minval = i; 

        for (int j = i+1; j < list.size() - 1; j++){
            if (list[j] < list[minval]){
                minval = j;
            }
         }
        swap(list, minval, i);
    }   
}   

template <typename T>
int partition(vector<T> &list, int low, int high) {
    T pivot = list[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (list[j] < pivot) {
            i++;
            swap(list, i, j);
        }
    }
    swap(list, i + 1, high);
    return (i + 1);
}

template <typename T>
void quickSortHelper(vector<T> &list, int low, int high) {
    if (low < high) {
        int pi = partition(list, low, high);

        quickSortHelper(list, low, pi - 1);
        quickSortHelper(list, pi + 1, high);
    }
}


template <typename T>
void quickSort(vector<T> &list) {
    if (!list.empty()) {
        quickSortHelper(list, 0, list.size() - 1);
    }
}


template <typename T>
void merge(vector<T> &list, int left, int mid, int right){
    vector <T> leftList;
    for (int i = left; i <= mid; i++){
        leftList.push_back(list[i]);
    }
    vector <T> rightList;
    for (int j = mid + 1; j <= right; j++){
        rightList.push_back(list[j]);
    }

    int index = left;
    int i = 0;
    int j = 0;

    while (i < leftList.size() && j < rightList.size()){
        if (leftList[i] < rightList[j]){
            list[index] = leftList[i];
            i++;
        } else {
            list[index] = rightList[j];
            j++;
        }
        index++;
    }

    while (i < leftList.size()){
        list[index] = leftList[i];
        i++;
        index++;
    }

    while (j < rightList.size()){
        list[index] = rightList[j];
        j++;
        index++;
    }
}


template <typename T>
void mergeSort(vector<T> &list, int left, int right){
    if (left < right){
        int mid = (left + right) / 2;
        mergeSort(list, left, mid);
        mergeSort(list, mid + 1, right);
        merge(list, left, mid, right);
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
    quickSort(list);
    cout << "Lista ordenada con quickSort: " << endl;
    print(list);
    mergeSort(list, 0, list.size() - 1);
    cout << "Lista ordenada con mergeSort: " << endl;
    print(list);



    return 0;
}