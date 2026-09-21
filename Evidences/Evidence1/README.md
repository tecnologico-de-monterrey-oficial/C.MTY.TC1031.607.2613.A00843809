# Evidencia 1 - Procesamiento, Ordenamiento y Búsqueda de Logs

## Datos del estudiante
* **Nombre:** Juan Ángel Narváez Torres
* **Matricula:** A00843809
* **Materia:** Programación de Estructuras de Datos y Algoritmos Fundamentales

## Instrucciones de Compilación y Ejecución
Para probar este programa, sigue estos pasos:

1. Abre una terminal y asegúrate de estar ubicado dentro de la carpeta `src` del proyecto.
2. Compila el código fuente usando `g++` con el siguiente comando (es importante usar el estándar C++11):
   `g++ -std=c++11 main.cpp -o app`
3. Ejecuta el programa que se acaba de crear:
   * En Mac: `./app`
4. El programa abrirá un menú interactivo en la consola. Sigue las instrucciones para elegir el archivo de log y el algoritmo de ordenamiento.

## Formato de fechas para la búsqueda por rango
Al momento de realizar la búsqueda binaria, el sistema pedirá ingresar una fecha de inicio y una fecha de fin. Es necesario respetar la estructura, los espacios y las mayúsculas del archivo de texto original:
`Mes Dia Anio Hora:Minuto:Segundo`
Utilicé `Anio` para que no hubiera algún conflicto con la letra ñ en el codigo y siguiera siendo entendible.

**Ejemplo de entrada válida:** `Sep 08 2024 04:37:37`

## Política de Uso de Inteligencia Artificial (IA)
En el desarrollo de esta evidencia, me apegué a los lineamientos de la materia sobre el uso de herramientas de IA:

* **Uso permitido aplicado:** Utilicé Gemini como apoyo para repasar conceptos teóricos de complejidad algorítmica (O(n log n) vs O(n^2)) y para consultar cómo convertir los datos de fecha de tipo `string` a numéricos usando `<sstream>`.
* **Trabajo manual y corrección de errores:** No usé la IA para generar la solución de punta a punta. Durante el desarrollo de la búsqueda binaria, la IA sugirió un algoritmo que fallaba con los timestamps duplicados (un caso de prueba estipulado en la actividad). Detecté este error, descarté la sugerencia y programé manualmente las funciones de límite inferior y superior para manejar las colisiones correctamente.

## Enlace al Video Explicativo
https://youtu.be/6gfkAglb9X0