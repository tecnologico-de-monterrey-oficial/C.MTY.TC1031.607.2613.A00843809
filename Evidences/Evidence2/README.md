# Evidencia 2 - Juan Ángel Narváez Torres - A00843809

## Descripción
Aplicación en C++ que procesa archivos logs de seguridad de red implementando estructuras de datos lineales propias desde cero

- **Lista ligada simple (`LinkedList`)**: Con punteros `head` y `tail` para inserciones y eliminaciones en los extremos en O(1).
- **Fila (`Queue`)**: Construida sobre `LinkedList`. Funciona como buffer de lectura FIFO para encolar cada línea cruda del archivo antes de validarla.
- **Lista doblemente ligada (`DoublyLinkedList`)**: Almacén principal de los objetos `Log`. Se ordena directamente sobre sus nodos mediante **Merge Sort** (O(n log n)) re-enlazando punteros `next` y `prev`.
- **Pila (`Stack`)**: Construida sobre `LinkedList`. Invierte el orden de los registros encontrados en un día para desplegarlos en orden cronológico descendente (LIFO).

---

## Instrucciones para compilar y ejecutar

### 0. Ubicarse en la carpeta raíz del proyecto
Para que las rutas relativas de los archivos (como la carpeta `data/` o `out/`) funcionen correctamente en cualquier computadora, es **indispensable** ejecutar los comandos desde la carpeta raíz del proyecto (`Evidence2`). 

Abre tu terminal y navega hasta la carpeta usando el comando `cd` con la ruta de tu máquina:
```bash
cd "/ruta/hacia/tu/carpeta/Evidence2"
```
* En Visual Studio Code haz clic derecho sobre la carpeta `Evidence2` en el explorador de archivos lateral y selecciona **"Open in Integrated Terminal"** / **"Abrir en la terminal integrada"** para posicionarte automáticamente en la ruta correcta.*

### 1. Compilar y ejecutar el Programa de Pruebas (Parte A)
Una vez posicionado en la raíz del proyecto, ejecuta:

```bash
g++ -std=c++17 src/main_pruebas.cpp -o pruebas_parteA
./pruebas_parteA
```

### 2. Compilar y ejecutar la Aplicación Principal de Logs (Parte B)
Nuevamente desde la raíz del proyecto, ejecuta:

```bash
g++ -std=c++17 src/main.cpp -o app_logs
./app_logs
```

---

## Formato de fechas esperado
- **Formato de cada línea en el archivo de entrada**:
  `Mmm DD AAAA HH:MM:SS <IP> <tipo de evento>`
  Ejemplo: `Sep 29 2024 14:37:38 10.14.19.188 Unauthorized Access Attempts`
- **Formato para búsqueda por día (Opciones 2 y 3)**:
  `Mmm DD AAAA` (mes en inglés con tres letras e inicial mayúscula, día y año de 4 dígitos).
  Ejemplo: `Sep 14 2024`

---

## Video explicativo
- **Enlace al video**: https://youtu.be/uQLkfU7871E

---

## Política de uso de Inteligencia Artificial aplicada
- **Parte A (Estructuras base)**: Desarrollada al 100% sin asistentes de IA, partiendo de las implementaciones trabajadas en clase de `Node`, `NodeD`, `LinkedList` y `DoublyLinkedList`, adaptando el puntero `tail` en la lista simple para garantizar O(1) en extremos.
- **Parte B (Aplicación de logs)**:
  - **Permitido y aplicado**: Consulta puntual de sintaxis de `<chrono>` para medir tiempos en milisegundos, validación de formato con `std::stringstream` y revisión de casos extremos en el re-enlace de punteros `prev` durante la fusión (`mergeLists`) de la lista doblemente ligada.
  - **No permitido**: Generación automática de la aplicación de punta a punta o uso de agentes autónomos. Todo el código sugerido o revisado fue validado, corregido manualmente y probado contra los archivos de prueba.