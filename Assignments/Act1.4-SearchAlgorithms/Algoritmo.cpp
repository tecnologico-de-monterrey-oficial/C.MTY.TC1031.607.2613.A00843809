// Juan Angel Narvaez Torres
// A00843809

//hecho en clase

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;



int algoritmoBusquedaSecuencial(const vector<int>& lista, int objetivo){
    for (int i = 0; i < lista.size(); i++){
        if (lista[i] == objetivo){
            return i;
        }
    }
    return -1;
}

template <typename T>

int algoritmoBusquedaBinaria(const vector<T>& lista, T objetivo){
    int left = 0;
    int right = lista.size() - 1;

    while (left <= right){
        int mid = (left + right)/2;
        
        if (lista[mid] == objetivo){
            return mid;
        }

        else if (lista[mid] < objetivo){
            left = mid +1;
        }

        else{
            right = mid - 1;
        }
    }
    return -1;
}

int main(){

    vector<int> nums = {35, 11, 6, 27, 12, 5, 16, 3, 13, 8};

    // Busqueda secuencial

    int busquedaSec = algoritmoBusquedaBinaria(nums, 14);
    if (busquedaSec != -1){
        cout << "El numero fue encontrado en: " << busquedaSec << endl;
    }

    else {
        cout << "El numero no esta en la lista" << endl;
    }


    // Busqueda binaria

    sort(nums.begin(), nums.end());
    int busquedaBin = algoritmoBusquedaBinaria(nums, 14);
    if (busquedaBin != -1){
        cout << "El numero fue encontrado en: " << busquedaBin << endl;
    }

    else {
        cout << "El numero no esta en la lista" << endl;
    }

}
