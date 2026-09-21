#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class Registro {
private:
    string mes; int dia; int anio; string hora; string ip; string razon; string lineaCompleta;
    long long fechaValor;

    int mesANumero(const string& m) const {
        if (m == "Jan") return 1; if (m == "Feb") return 2; if (m == "Mar") return 3;
        if (m == "Apr") return 4; if (m == "May") return 5; if (m == "Jun") return 6;
        if (m == "Jul") return 7; if (m == "Aug") return 8; if (m == "Sep") return 9;
        if (m == "Oct") return 10; if (m == "Nov") return 11; if (m == "Dec") return 12;
        return 0;
    }

    void calcularFechaValor() {
        int m = mesANumero(mes);
        int h = 0, min = 0, s = 0; char sep;
        stringstream ss(hora);
        ss >> h >> sep >> min >> sep >> s;
        fechaValor = (long long)anio * 10000000000LL + (long long)m * 100000000LL + (long long)dia * 1000000LL + h * 10000 + min * 100 + s;
    }

public:
    Registro() { dia = 0; anio = 0; fechaValor = 0; }
    Registro(const string& linea) {
        lineaCompleta = linea;
        stringstream ss(linea);
        ss >> mes >> dia >> anio >> hora >> ip;
        getline(ss, razon);
        if (!razon.empty() && razon[0] == ' ') razon = razon.substr(1);
        calcularFechaValor();
    }
    Registro(string m, int d, int a, string h) {
        mes = m; dia = d; anio = a; hora = h;
        calcularFechaValor();
    }
    long long getFechaValor() const { return fechaValor; }
    string getLineaCompleta() const { return lineaCompleta; }

    bool operator<(const Registro& otro) const { return this->fechaValor < otro.fechaValor; }
    bool operator>(const Registro& otro) const { return this->fechaValor > otro.fechaValor; }
    bool operator<=(const Registro& otro) const { return this->fechaValor <= otro.fechaValor; }
    bool operator>=(const Registro& otro) const { return this->fechaValor >= otro.fechaValor; }
};

template <typename T>
void swapElements(vector<T> &list, int i, int j) {
    if (i != j) {
        T aux = list[i]; list[i] = list[j]; list[j] = aux;
    }
}

template <typename T>
void swapSort(vector<T> &list) {
    for (int i=0; i < list.size()-1; i++) {
        for (int j=i+1; j<list.size(); j++) {
            if (list[j] < list[i]) swapElements(list, i, j);
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
                swapElements(list, j, j+1);
            }
        }
    }
}

template <typename T>
void insertionSort(vector<T> &list){
    for (int i = 1; i < list.size(); i++){
        T key = list[i];
        int j = i-1;
        while (j >= 0 && list[j] > key){
            list[j+1] = list[j];
            j = j - 1;
        }
        list[j + 1] = key;
    }
}

template <typename T>
void selectionSort(vector<T> & list){
    for (int i = 0; i < list.size() - 1; i++){
        int minval = i; 
        for (int j = i+1; j < list.size(); j++){
            if (list[j] < list[minval]) minval = j;
        }
        swapElements(list, minval, i);
    }   
}

template <typename T>
int partitionAlgo(vector<T> &list, int low, int high) {
    T pivot = list[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (list[j] < pivot) {
            i++;
            swapElements(list, i, j);
        }
    }
    swapElements(list, i + 1, high);
    return (i + 1);
}

template <typename T>
void quickSortHelper(vector<T> &list, int low, int high) {
    if (low < high) {
        int pi = partitionAlgo(list, low, high);
        quickSortHelper(list, low, pi - 1);
        quickSortHelper(list, pi + 1, high);
    }
}

template <typename T>
void quickSort(vector<T> &list) {
    if (!list.empty()) quickSortHelper(list, 0, list.size() - 1);
}

template <typename T>
void mergeList(vector<T> &list, int left, int mid, int right){
    vector <T> leftList;
    for (int i = left; i <= mid; i++) leftList.push_back(list[i]);
    vector <T> rightList;
    for (int j = mid + 1; j <= right; j++) rightList.push_back(list[j]);

    int index = left, i = 0, j = 0;
    while (i < leftList.size() && j < rightList.size()){
        if (leftList[i] < rightList[j]) list[index++] = leftList[i++];
        else list[index++] = rightList[j++];
    }
    while (i < leftList.size()) list[index++] = leftList[i++];
    while (j < rightList.size()) list[index++] = rightList[j++];
}

template <typename T>
void mergeSort(vector<T> &list, int left, int right){
    if (left < right){
        int mid = (left + right) / 2;
        mergeSort(list, left, mid);
        mergeSort(list, mid + 1, right);
        mergeList(list, left, mid, right);
    }
}

int main() {
    ifstream archivo("../data/log607-1.txt");
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo." << endl;
        return 1;
    }
    vector<Registro> listaLogs;
    string linea;
    while (getline(archivo, linea)) {
        if (!linea.empty()) listaLogs.push_back(Registro(linea));
    }
    archivo.close();
    cout << "Parsing exitoso. Total de registros: " << listaLogs.size() << endl;
    return 0;
}