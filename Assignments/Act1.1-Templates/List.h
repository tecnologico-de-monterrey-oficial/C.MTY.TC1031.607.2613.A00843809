#ifndef List_h
#define List_h

using namespace std;
#include <iostream>
#include <vector>

template <typename T>


class List{
private:
    vector<T> data;
    int size;
public:
    List();
    void insert(T data);
    void removeLast();
    T getData(int pos);
    int getSize();
    T getMax();
    void print();
    void insertAt(int pos, T val);
    void removeAt(int pos);
};

template <typename T>
List<T>::List(){
    size = 0;
    cout << "Constructor por default" << endl;
}

template <typename T>
void List<T>::insert(T data){
    data.push_back(val);
    size++;
}

template <typename T>
void List<T>::removeLast(){
    if (size == 0){
        cout << "No hay elementos en la lista" << endl;
    } else {
        data.pop_back();
        size--;
    }
}

template <typename T>
T List<T>::getData(int pos){
    retrun data[pos];
}

template <typename T>
int List<T>::getSize(){
    return size;
}

template <typename T>
T List<T>::getMax(){
    if (size == 0) return T();

    T maxVal = data[0];
    for (int i = 1; i < size; i++){
        if (data[i] > maxVal){
            maxVal = data[i];
        }
    }
}

template <typename T>
void List<T>::print(){
    for (int i = 0; i < size; i++){
        cout << data[i] << " ";
    }
    cout << endl;
}

template <typename T>
void List<T>::insertAt(int pos, T val){
    if (pos < 0 || pos > size){
        cout << "Posición invalida" << endl;
        return;
    }
    data.insert(data.begin() + pos, val);
    size++;
}

template <typename T>
void List<T>::removeAt(int pos){
    if (size == 0){
        cout << "No hay elementos en la lista" << endl;
    } else if (pos < 0 || pos >= size){
        cout << "Posición invalida" << endl;
    } else {
        T removedVal = data[pos];
        data.erase(data.begin() + pos);
        size--;
        cout << "Elemento eliminado: " << removedVal << endl;
    }
}


#endif /** List_h */