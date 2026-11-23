# Problema 7:  Subsecuencia común mas larga
___

Objetivo: Nos dan dos cadenas y queremos hallar la subsecuencia(difiere de una subcadena porque no requiere tener letras contiguas) mas larga comun entre las dos. Ojo, la subsecuencia debe estar en orden.

Idea: Cuando ambas letras coinciden avanzamos ambos indices en ambas palabras. En caso de no coincidir, buscamos el maximo de avanzar con un indice o avanzar con el otro. Veamos en el punto 2 como traducirlo a código.

1. Defincion de la función

> subsec(i, j) = longitud de la subsecuencia mas larga de X[1..i] y Y[1..j]  para 0 <= i <= n y para 0 <= j <= m.

2. Definion recursiva: 

   Caso base: 

   ​	subsec(i, 0) = 0				0<= i <= n

   ​	subsec(0, j) = 0				0 <= j <= m

   Caso recursivo: 

   ​	subsec(i, j) = 	subsec(i - 1, j - 1) + 1 				si x[i] == y[j]

   ​					max(subsec(i - 1, j), subsec(i, j - 1))        si  x[i] != y[j]

3. El rellenado de la tabla se hará de izquierda a derecha, fila a fila (i de 1 a n) y dentro de cada fila de columna en columna (j de 1 a m). Así cuando queramos rellenar subsec(i, j) seguiremos el paso 1.2

4. El coste en espacio y tiempo es de O(N*M) ya que habrá (n+1)(m+1) celdas y cada una se calcula en tiempo constante. Siendo N la longitud de la palabra X y M el cardinal de la palabra Y. 

> Ojo: El + 1 es para que la matriz contenga la cadena vacia de base
