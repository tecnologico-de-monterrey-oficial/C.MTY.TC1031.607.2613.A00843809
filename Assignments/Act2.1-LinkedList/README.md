# Actividad: Implementación de un ADT (Linked List)

## Prompts utilizados

1. "¿Por qué me sale 'Segmentation fault' en C++ cuando trato de borrar el último nodo de mi lista enlazada?"

2. "¿Cuál es la diferencia entre regresar un valor normal o regresar por referencia (T&) al sobrecargar el operador []?"

3. "¿Cómo funciona exactamente la sintaxis para lanzar un error de tipo out_of_range en C++?"

4. "Me sale este error en la terminal: Program 'LinkedList.exe' failed to run: The specified executable is not a valid application. ¿A qué se debe?"

## Reflexión

* **¿Qué parte del código te propuso la IA que aceptaste tal cual y por qué era correcta?**
  Acepté la sintaxis y la explicación teórica para sobrecargar el operador [] devolviendo una referencia (T&). Yo ya tenía la lógica para recorrer la lista hasta el índice buscado, pero la IA me explicó correctamente que devolver la referencia era estrictamente necesario para que el programa principal pudiera tanto leer como sobrescribir el dato en esa posición de memoria directamente.

* **¿Qué parte modificaste y cómo verificaste que tu cambio era mejor?**
  Cuando pregunté sobre los errores de rango, la IA me propuso implementar bloques try-catch y lanzar excepciones con throw std::out_of_range. Modifiqué esa propuesta por completo para mantener el código alineado a lo que he aprendido en el curso. En su lugar, utilicé validaciones simples con if, imprimiendo el error en consola con cout y regresando un valor por defecto. Verifiqué que mi cambio era mejor porque el programa sigue siendo seguro ante índices inválidos, pero utiliza una sintaxis que domino y entiendo al 100.

* **¿Dónde se equivocó la IA (si ocurrió) y cómo lo detectaste?**
  Al preguntarle por el error de 'Segmentation fault' al borrar nodos, la IA me sugirió un bloque de código que utilizaba iteradores y herramientas de la librería estándar <list> de C++, ignorando por completo que yo estaba construyendo la estructura desde cero con mis propios apuntadores Node<T>*. Lo detecté inmediatamente al leer el código porque incluía palabras clave y métodos que no correspondían a mi archivo .h original, así que ignoré su código y solo tomé su explicación lógica para corregir mi ciclo while.

* **¿Qué harías diferente si no tuvieras Copilot/ChatGPT?**
  Habría perdido mucho tiempo intentando descifrar por qué la terminal me bloqueaba el archivo con el error de ejecutable inválido (LinkedList.exe failed to run), sin saber que simplemente debía borrar el archivo corrupto y recompilar. Además, habría tardado más tiempo depurando en papel o con impresiones en consola los casos borde de los apuntadores, como cuando se intenta borrar un elemento en una lista que ya está vacía.