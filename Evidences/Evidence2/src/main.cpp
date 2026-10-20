#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <cmath>
#include <iomanip>

#include "../include/Queue.h"
#include "../include/DoublyLinkedList.h"
#include "../include/Log.h"

using namespace std;

int main() {
    cout << "=== SISTEMA PROCESADOR DE LOGS ===" << endl;
    cout << "Ingrese el archivo a cargar (ej. data/log607-1.txt): ";
    string ruta;
    getline(cin, ruta);

    ifstream archivoEntrada(ruta);
    if (!archivoEntrada.is_open()) {
        cout << "Error: No se pudo abrir el archivo." << endl;
        return 0;
    }

    Queue<string> bufferLectura;
    string linea;
    while (getline(archivoEntrada, linea)) {
        if (!linea.empty() && linea.back() == '\r') linea.pop_back();
        bufferLectura.enqueue(linea);
    }
    archivoEntrada.close();

    DoublyLinkedList<Log> listaLogs;
    int numeroLinea = 0, registrosCargados = 0, lineasOmitidas = 0;

    while (!bufferLectura.isEmpty()) {
        numeroLinea++;
        string lineaActual = bufferLectura.dequeue();
        try {
            listaLogs.addLast(Log::parseLine(lineaActual));
            registrosCargados++;
        } catch (const exception& e) {
            lineasOmitidas++;
            cout << "Línea " << numeroLinea << " omitida: " << e.what() << endl;
        }
    }

    cout << "Registros cargados: " << registrosCargados << " | Omitidos: " << lineasOmitidas << endl;

    int opcion = 0;
    while (opcion != 5) {
        cout << "\n1. Ordenar por fecha y hora\n5. Salir\nOpción: ";
        cin >> opcion;
        if (opcion == 1) {
            long long comparaciones = 0;
            int profundidadMax = 0;
            listaLogs.mergeSort(comparaciones, profundidadMax);
            cout << "Lista ordenada. Comparaciones: " << comparaciones
                 << " | Profundidad: " << profundidadMax << endl;
        }
    }
    return 0;
}