#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <cmath>
#include <map>
#include <iomanip>

#include "../include/Queue.h"
#include "../include/Stack.h"
#include "../include/DoublyLinkedList.h"
#include "../include/Log.h"

using namespace std;

// Intenta abrir el archivo buscando en la ruta dada, en ./data/ o en ../data/
bool abrirArchivoLog(const string& nombreInput, ifstream& archivo, string& rutaEfectiva) {
    string candidatos[] = {
        nombreInput,
        "data/" + nombreInput,
        "../data/" + nombreInput
    };
    for (int i = 0; i < 3; i++) {
        archivo.open(candidatos[i]);
        if (archivo.is_open()) {
            rutaEfectiva = candidatos[i];
            return true;
        }
        archivo.clear();
    }
    return false;
}

// Guarda los registros ordenados en output608.out (y en out/output608.out si existe la carpeta)
void guardarArchivoSalida(const DoublyLinkedList<Log>& logs, const string& nombreSalida) {
    ofstream out1(nombreSalida);
    if (out1.is_open()) {
        NodeD<Log>* aux = logs.getHead();
        while (aux != nullptr) {
            out1 << aux->data.toString() << "\n";
            aux = aux->next;
        }
        out1.close();
    }

    ofstream out2("out/" + nombreSalida);
    if (out2.is_open()) {
        NodeD<Log>* aux = logs.getHead();
        while (aux != nullptr) {
            out2 << aux->data.toString() << "\n";
            aux = aux->next;
        }
        out2.close();
    }
}

// Busca todos los registros de un día aprovechando que la lista está ordenada
int buscarPorDia(DoublyLinkedList<Log>& logs, int targetDayKey, Stack<Log>& pilaResultados, bool imprimirEnPantalla) {
    pilaResultados.clear();
    int encontrados = 0;
    NodeD<Log>* aux = logs.getHead();

    while (aux != nullptr) {
        // Aprovechamos el orden: si ya pasamos el día buscado, detenemos el recorrido
        if (aux->data.dayKey > targetDayKey) {
            break;
        }
        if (aux->data.dayKey == targetDayKey) {
            if (imprimirEnPantalla) {
                cout << "  " << aux->data << endl;
            }
            pilaResultados.push(aux->data);
            encontrados++;
        }
        aux = aux->next;
    }
    return encontrados;
}

int main() {
    cout << "        SISTEMA PROCESADOR DE LOGS DE EVENTOS DE RED      " << endl;

    ifstream archivoEntrada;
    string nombreArchivo = "";
    string rutaReal = "";

    // Selección y validación de archivo de entrada
    while (true) {
        cout << "\nSeleccione el archivo que desea cargar:" << endl;
        cout << "  1. log607-1.txt" << endl;
        cout << "  2. log607-2.txt" << endl;
        cout << "  3. Ingresar el nombre del archivo manualmente" << endl;
        cout << "Opcion: ";

        string opcionCarga;
        getline(cin, opcionCarga);

        if (opcionCarga == "1") {
            if (!abrirArchivoLog("log607-1.txt", archivoEntrada, rutaReal)) {
                abrirArchivoLog("log607-1.txt", archivoEntrada, rutaReal);
                nombreArchivo = "log607-1.txt";
            } else {
                nombreArchivo = "log607-1.txt";
            }
        } else if (opcionCarga == "2") {
            if (!abrirArchivoLog("log607-2.txt", archivoEntrada, rutaReal)) {
                abrirArchivoLog("log607-2.txt", archivoEntrada, rutaReal);
                nombreArchivo = "log607-2.txt";
            } else {
                nombreArchivo = "log607-2.txt";
            }
        } else if (opcionCarga == "3") {
            cout << "Ingrese el nombre o ruta del archivo (ej. log607-1.txt): ";
            getline(cin, nombreArchivo);
            if (nombreArchivo.empty()) {
                cout << "[Aviso] El nombre del archivo no puede estar vacio." << endl;
                continue;
            }
            abrirArchivoLog(nombreArchivo, archivoEntrada, rutaReal);
        } else {
            cout << "[Error] Opcion invalida. Por favor ingrese 1, 2 o 3." << endl;
            continue;
        }

        if (archivoEntrada.is_open()) {
            break;
        } else {
            cout << "[Error] No se pudo abrir el archivo '" << nombreArchivo
                 << "'. Verifique que exista en la carpeta actual o en /data." << endl;
        }
    }

    // FASE 1: Lectura del archivo hacia una Fila (Buffer FIFO)
    Queue<string> bufferLectura;
    string linea;
    while (getline(archivoEntrada, linea)) {
        // Limpiar posible salto de carro de Windows (\r)
        if (!linea.empty() && linea.back() == '\r') {
            linea.pop_back();
        }
        bufferLectura.enqueue(linea);
    }
    archivoEntrada.close();

    // FASE 2: Procesador desencola, valida e inserta en Lista Doble
    DoublyLinkedList<Log> listaLogs;
    int numeroLinea = 0;
    int registrosCargados = 0;
    int lineasOmitidas = 0;

    cout << "\nProcesando buffer de lectura (Fila FIFO)..." << endl;
    while (!bufferLectura.isEmpty()) {
        numeroLinea++;
        string lineaActual = bufferLectura.dequeue();
        try {
            Log nuevoRegistro = Log::parseLine(lineaActual);
            listaLogs.addLast(nuevoRegistro);
            registrosCargados++;
        } catch (const exception& e) {
            lineasOmitidas++;
            cout << "  [Formato invalido - Linea " << numeroLinea << " omitida]: " << e.what() << endl;
        }
    }

    cout << "Resumen de carga del archivo '" << nombreArchivo << "':" << endl;
    cout << "  - Registros cargados exitosamente: " << registrosCargados << endl;
    cout << "  - Lineas con formato invalido omitidas: " << lineasOmitidas << endl;

    if (registrosCargados == 0) {
        cout << "No hay registros validos para procesar. Saliendo del programa." << endl;
        return 0;
    }

    // Variables de control del menú
    bool listaOrdenada = false;
    bool busquedaRealizada = false;
    string ultimoDiaBuscado = "";
    Stack<Log> pilaUltimaBusqueda;

    // MENÚ PRINCIPAL
    while (true) {
        cout << "\n MENU PRINCIPAL " << endl;
        cout << "1. Ordenar por fecha y hora" << endl;
        cout << "2. Buscar logs por dia" << endl;
        cout << "3. Mostrar logs por dia en orden descendente" << endl;
        cout << "4. Estadisticas del archivo" << endl;
        cout << "5. Salir" << endl;
        cout << "Seleccione una opcion: ";

        string entradaMenu;
        if (!getline(cin, entradaMenu)) break;

        if (entradaMenu.empty()) {
            cout << "[Aviso] Entrada vacia. Por favor ingrese un número del 1 al 5." << endl;
            continue;
        }

        // OPCIÓN 1: Ordenar por fecha y hora
        if (entradaMenu == "1") {
            if (listaOrdenada || listaLogs.isSorted()) {
                listaOrdenada = true;
                cout << "\n[Aviso] La lista doblemente ligada ya esta ordenada. No es necesario ordenar de nuevo." << endl;
                guardarArchivoSalida(listaLogs, "output608.out");
                cout << "Archivo 'output608.out' verificado/actualizado correctamente." << endl;
                continue;
            }

            cout << "\nAntes de ordenar, ¿que crecimiento esperas en el numero de comparaciones?" << endl;
            cout << "  1. Aproximadamente n log n" << endl;
            cout << "  2. Aproximadamente n^2" << endl;
            string predOpcion = "";
            while (predOpcion != "1" && predOpcion != "2") {
                cout << "Ingresa tu prediccion (1 o 2): ";
                getline(cin, predOpcion);
            }
            string textoPrediccion = (predOpcion == "1") ? "n log n" : "n^2";

            long long comparaciones = 0;
            int profundidadMax = 0;
            int n = listaLogs.getSize();

            auto inicio = chrono::high_resolution_clock::now();
            listaLogs.mergeSort(comparaciones, profundidadMax);
            auto fin = chrono::high_resolution_clock::now();

            double tiempoMs = chrono::duration<double, milli>(fin - inicio).count();
            listaOrdenada = true;

            // Guardar archivo de salida
            guardarArchivoSalida(listaLogs, "output608.out");

            // Evaluar predicción teórica
            double esperadoNLogN = (n > 1) ? (n * log2(n)) : 1.0;
            bool coincide = (predOpcion == "1"); // Merge Sort siempre crece en O(n log n)

            cout << "\n RESULTADOS DEL ORDENAMIENTO " << endl;
            cout << "  - Algoritmo usado:                    Merge Sort (in-place sobre lista doble)" << endl;
            cout << "  - Archivo procesado:                  " << nombreArchivo << endl;
            cout << "  - Tamaño de los datos (n):            " << n << " registros" << endl;
            cout << fixed << setprecision(4);
            cout << "  - Tiempo de ejecucion:                " << tiempoMs << " ms" << endl;
            cout << "  - Numero de comparaciones realizadas: " << comparaciones
                 << " (referencia n*log2(n) = " << (long long)esperadoNLogN << ")" << endl;
            cout << "  - Profundidad maxima de recursion:    " << profundidadMax << " niveles" << endl;
            cout << "  - Prediccion ingresada:               " << textoPrediccion << endl;
            cout << "  - ¿Coincidio con tu prediccion?:      "
                 << (coincide ? "Si, el crecimiento observado es O(n log n)."
                              : "No, como se uso Merge Sort el crecimiento real fue O(n log n), no n^2.") << endl;
            cout << "  - Archivo de salida generado:         output608.out" << endl;
        }

        // OPCIÓN 2: Buscar logs por día
        else if (entradaMenu == "2") {
            if (!listaOrdenada && !listaLogs.isSorted()) {
                cout << "\n[Aviso] La lista aun no está ordenada. Primero debe ordenarse usando la Opcion 1." << endl;
                continue;
            }
            listaOrdenada = true;

            cout << "\nIngrese el dia a buscar en formato 'Mmm DD AAAA' (ejemplo: Sep 14 2024): ";
            string diaInput;
            getline(cin, diaInput);

            int targetDayKey = 0;
            string fechaNormalizada = "";
            if (!Log::parseDayQuery(diaInput, targetDayKey, fechaNormalizada)) {
                cout << "[Error] Formato de día invalido. Asegurese de usar un mes valido en ingles (ej. Sep), "
                     << "dia valido y año de 4 digitos (ej. Sep 14 2024)." << endl;
                continue;
            }

            cout << "\n Registros encontrados para " << fechaNormalizada << " (orden ascendente) ---" << endl;
            int totalEncontrados = buscarPorDia(listaLogs, targetDayKey, pilaUltimaBusqueda, true);
            ultimoDiaBuscado = fechaNormalizada;
            busquedaRealizada = true;

            if (totalEncontrados == 0) {
                cout << "  No se encontraron registros para el dia " << fechaNormalizada << "." << endl;
            } else {
                cout << "Total de registros encontrados en " << fechaNormalizada << ": " << totalEncontrados << endl;
            }
        }

        // OPCIÓN 3: Mostrar logs por día en orden descendente (Pila)
        else if (entradaMenu == "3") {
            if (!listaOrdenada && !listaLogs.isSorted()) {
                cout << "\n[Aviso] La lista aun no esta ordenada. Primero debe ordenarse usando la Opcion 1." << endl;
                continue;
            }
            listaOrdenada = true;

            // Si aún no se ha hecho una búsqueda en la opción 2, pedimos el día
            if (!busquedaRealizada) {
                cout << "\nNo se ha realizado una busqueda previa. Ingrese el dia en formato 'Mmm DD AAAA' (ej. Sep 14 2024): ";
                string diaInput;
                getline(cin, diaInput);

                int targetDayKey = 0;
                string fechaNormalizada = "";
                if (!Log::parseDayQuery(diaInput, targetDayKey, fechaNormalizada)) {
                    cout << "[Error] Formato de día invalido. Ejemplo valido: Sep 14 2024." << endl;
                    continue;
                }
                buscarPorDia(listaLogs, targetDayKey, pilaUltimaBusqueda, false);
                ultimoDiaBuscado = fechaNormalizada;
                busquedaRealizada = true;
            } else {
                // Si la pila ya fue vaciada en una ejecución previa de la opción 3, la recargamos
                if (pilaUltimaBusqueda.isEmpty()) {
                    int targetDayKey = 0;
                    string fechaNorm = "";
                    if (Log::parseDayQuery(ultimoDiaBuscado, targetDayKey, fechaNorm)) {
                        buscarPorDia(listaLogs, targetDayKey, pilaUltimaBusqueda, false);
                    }
                }
            }

            if (pilaUltimaBusqueda.isEmpty()) {
                cout << "\nNo hay registros para el dia " << ultimoDiaBuscado << " para mostrar en orden descendente." << endl;
            } else {
                cout << "\n Registros del dia " << ultimoDiaBuscado << " en orden DESCENDENTE (usando Pila LIFO) ---" << endl;
                int totalMostrados = 0;
                while (!pilaUltimaBusqueda.isEmpty()) {
                    cout << "  " << pilaUltimaBusqueda.pop() << endl;
                    totalMostrados++;
                }
                cout << "Total mostrados (mas reciente a mas antiguo): " << totalMostrados << endl;
            }
        }

        // OPCIÓN 4: Estadísticas del archivo
        else if (entradaMenu == "4") {
            map<string, int> conteoDias;
            map<string, int> conteoEventos;
            map<string, int> conteoIPs;

            NodeD<Log>* aux = listaLogs.getHead();
            while (aux != nullptr) {
                conteoDias[aux->data.getDateString()]++;
                conteoEventos[aux->data.event]++;
                conteoIPs[aux->data.ip]++;
                aux = aux->next;
            }

            int maxDia = 0, maxEvento = 0, maxIP = 0;
            for (auto const& par : conteoDias) {
                if (par.second > maxDia) maxDia = par.second;
            }
            for (auto const& par : conteoEventos) {
                if (par.second > maxEvento) maxEvento = par.second;
            }
            for (auto const& par : conteoIPs) {
                if (par.second > maxIP) maxIP = par.second;
            }

            cout << "\n ESTADISTICAS DEL ARCHIVO " << endl;
            cout << "1. Total de registros validos: " << listaLogs.getSize() << endl;

            cout << "\n2. Dia(s) con mas incidentes (" << maxDia << " apariciones):" << endl;
            for (auto const& par : conteoDias) {
                if (par.second == maxDia) {
                    cout << "   - " << par.first << " (" << par.second << " incidentes)" << endl;
                }
            }

            cout << "\n3. Tipo(s) de evento mas frecuente(s) (" << maxEvento << " apariciones):" << endl;
            for (auto const& par : conteoEventos) {
                if (par.second == maxEvento) {
                    cout << "   - " << par.first << " (" << par.second << " apariciones)" << endl;
                }
            }

            cout << "\n4. Direccion(es) IP que aparece(n) mas veces (" << maxIP << " apariciones):" << endl;
            for (auto const& par : conteoIPs) {
                if (par.second == maxIP) {
                    cout << "   - " << par.first << " (" << par.second << " apariciones)" << endl;
                }
            }
        }

        // OPCIÓN 5: Salir
        else if (entradaMenu == "5") {
            cout << "\nSaliendo de la aplicacion. ¡Hasta luego!" << endl;
            break;
        }

        else {
            cout << "[Error] Opcion inexistente. Por favor elija una opción entre 1 y 5." << endl;
        }
    }

    return 0;
}