// Juan Angel Narvaez Torres
// A00843809

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

template <class T>
bool busquedaSecuencialNum(vector<T> v, T objetivo) {
    for (int i = 0; i < v.size(); i++) {
        if (v[i] == objetivo) {
            return true;
        }
    }
    return false;
}

template <class T>
bool busquedaBinariaNum(vector<T> v, T objetivo) {
    int inicio = 0;
    int fin = v.size() - 1;
    
    while (inicio <= fin) {
        int medio = (inicio + fin) / 2;
        
        if (v[medio] == objetivo) {
            return true;
        }
        if (v[medio] < objetivo) {
            inicio = medio + 1;
        } else {
            fin = medio - 1;
        }
    }
    return false;
}

// Programa 2 

int busquedaSecuencialString(string s, char &unico) {
    int comparaciones = 0;
    int i = 0;
    
    while (i < s.length() - 1) {
        comparaciones++;
        if (s[i] != s[i + 1]) {
            unico = s[i];
            return comparaciones;
        }
        i += 2;
    }
    unico = s[s.length() - 1];
    return comparaciones;
}

int busquedaBinariaString(string s, char &unico) {
    int inicio = 0;
    int fin = s.length() - 1;
    int comparaciones = 0;
    
    if (s.length() == 1) {
        unico = s[0];
        return 0;
    }

    while (inicio < fin) {
        comparaciones++;
        int medio = (inicio + fin) / 2;
        
        if (medio % 2 != 0) {
            medio--;
        }
        
        if (s[medio] == s[medio + 1]) {
            inicio = medio + 2;
        } else {
            fin = medio;
        }
    }
    
    unico = s[inicio];
    return comparaciones;
}

int main() {
    cout << "Programa 1 de busqueda de numeros" << endl;
    
    srand(time(0)); 
    vector<int> numeros(10000);
    
    for (int i = 0; i < 10000; i++) {
        numeros[i] = (rand() % 1000000) + 1; 
    }

    sort(numeros.begin(), numeros.end());
    cout << "Vector de 10,000 numeros generado y ordenado." << endl;

    int objetivo;
    while (true) {
        cout << "Ingrese el numero a buscar (Teclee 0 para pasar al Programa 2): ";
        cin >> objetivo;
        
        if (objetivo == 0) {
            break;
        }

        // Medir tiempo de Búsqueda Secuencial
        clock_t inicio_sec = clock();
        bool encontrado_sec = busquedaSecuencialNum(numeros, objetivo);
        clock_t fin_sec = clock();
        double tiempo_sec = double(fin_sec - inicio_sec) / CLOCKS_PER_SEC;

        // Medir tiempo de Búsqueda Binaria
        clock_t inicio_bin = clock();
        bool encontrado_bin = busquedaBinariaNum(numeros, objetivo);
        clock_t fin_bin = clock();
        double tiempo_bin = double(fin_bin - inicio_bin) / CLOCKS_PER_SEC;

        if (encontrado_sec) {
            cout << "-> El numero SI se encuentra en la lista.\n";
        } else {
            cout << "-> El numero NO se encuentra en la lista.\n";
        }

        // Mostrado en milisegundos
        cout << "   Tiempo B. Secuencial: " << tiempo_sec * 1000 << " milisegundos.\n";
        cout << "   Tiempo B. Binaria:    " << tiempo_bin * 1000 << " milisegundos.\n\n";
    }

    // --- INICIO DEL PROGRAMA 2 ---
    cout << "Programa 2 de caracteres unicos" << endl;
    
    int n;
    cout << "Cantidad de strings (n):";
    cin >> n;

    vector<string> strings(n);
    for (int i = 0; i < n; i++) {
        cin >> strings[i];
    }

    cout << "Salida:" << endl;
    for (int i = 0; i < n; i++) {
        char charSec, charBin;
        
        int compSec = busquedaSecuencialString(strings[i], charSec);
        int compBin = busquedaBinariaString(strings[i], charBin);
        
        cout << charSec << " " << compSec << " " << charBin << " " << compBin << endl;
    }

    return 0;
}