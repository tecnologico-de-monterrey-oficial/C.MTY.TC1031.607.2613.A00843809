// Juan Angel Narvaez Torres
// A00843809

#include <iostream>
#include <vector>
using namespace std;

// suma iterativa
int sumarParesIterativo(const vector<int>& numeros){
    int suma = 0;
    for (int num : numeros){
        if (num % 2 == 0){
            suma += num;
        }
    }
    return suma;
}
// suma recursiva
int sumarParesRecursivo(const vector<int>& numeros, int indice = 0){
    if (indice == numeros.size()){
        return 0;
    }

    int valorActual = 0;
    if (numeros[indice] % 2 == 0){
        valorActual = numeros[indice];
    }
    return valorActual + sumarParesRecursivo(numeros, indice + 1);
}

int main(){
    vector <int> numeros = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    cout << "Suma de pares iterativa: " << sumarParesIterativo(numeros) << endl;
    cout << "Suma de pares recursiva> " << sumarParesRecursivo(numeros) << endl;

    return 0;
}