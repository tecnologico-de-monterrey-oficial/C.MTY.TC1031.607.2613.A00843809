#Actividad 1. Templates - Reflexion

*1. ¿Qué ventaja concreta notaste al usar templates en tu clase 'Lista', comparado con haberla hecho solo para un tipo de dato (por ejemplo, solo enteros)? Da un ejemplo de tu propio código.*

La mayor ventaja es que te ahorra estar copiando y pegando el codigo. En vez de programar toda una clase desde cero para 'ListInt' y hacer exactamente lo mismo para 'ListString', el template deja que la misma clase funcione para lo que vayas a necesitar. En mi archivo del main 'act1.1-Templates.cpp' pude usar 'List<int> numeros;' y también 'List<string> cosas;' reciclando exactamente la misma lógica de los métodos sin tener que hacer dos clases diferentes.

*2. ¿Qué parte de la actividad ya sea el uso de templates o el reto de 'insertAt' / 'removeAt' te costó más trabajo entender o depurar? ¿Qué hiciste para resolverlo?*

Honestamente lo que más me hizo pensar fue cómo armar el 'insertAt' y el 'removeAt'. Recorrer todos los elementos a la derecha o a la izquierda sin salirte de los límites del arreglo estaba medio enredado y me daban error. Para no complicarme la vida con ciclos 'for' a mano, me metí a investigar rápido cómo funcionaban las listas dinámicas en C++ y vi que la librería de '<vector>' ya trae métodos como '.insert()' y '.erase()' que usan iteradores ('data.begin() + pos'). Con eso el código quedó súper corto y fácil de leer.

*3. Si tuvieras que explicarle a un compañero qué es un template en C++ usando tus propias palabras, sin tecnicismos, ¿qué le dirías?*

Le diría que es literal como un molde o una plantilla. Tú solo te encargas de diseñar el cómo quieres que funcione la estructura o el proceso, y luego cuando programes en el 'main' le avisas con qué tipo de dato lo vas a usar, ya sean enteros, texto, decimales.