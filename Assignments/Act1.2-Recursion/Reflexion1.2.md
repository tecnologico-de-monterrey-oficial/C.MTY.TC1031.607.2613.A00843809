Actividad 1.2 Recursion

*1. ¿En qué casos notaste que la versión recursiva fue más lenta o usó más memoria que la iterativa? ¿A qué se debió?*

Me di cuenta sobre todo en funciones como la de Fibonacci. La versión recursiva se vuelve mucho más lenta y gasta más memoria porque la compu tiene que ir dejando en pausa y guardando en la memoria cada llamada nueva que hace a la función hasta llegar al caso base. Además, en Fibonacci termina calculando los mismos números varias veces. En cambio, la iterativa nada más va actualizando las variables dentro del ciclo y ya, sin gastar memoria de más.

*2. Para la suma 1..n, sumFormula resuelve en un solo paso lo que a sumIterative y sumRecursive les toma n pasos. ¿Qué te dice esto sobre buscar una fórmula antes de escribir código?*

Pues me dice que antes de ponerme a escribir código, siempre se tiene que pensar en si hay alguna fórmula matemática o un atajo. Si usamos una fórmula, nos ahorramos un chorro de tiempo y hacemos que el programa sea súper eficiente, porque en lugar de hacer que la compu dé mil vueltas en un ciclo sumando uno por uno, lo saca de volada con una simple multiplicación y división.

*3. Si bacteriasRecursive tuviera que calcular n = 100,000 días, ¿qué problema esperarías encontrar y cómo lo resolverías?*

Si le pong 100,000 días a la recursiva, lo más seguro es que el programa va a tronar y me va a dar un error de llenado de memoria. Como tendría que abrir 100,000 funciones una dentro de otra sin cerrar ninguna, la memoria no va a aguantar. Para resolverlo, lo más fácil sería usar la versión iterativa con el ciclo for, ya que esa no tiene ese límite de memoria al actualizarse la variable continuamente.   