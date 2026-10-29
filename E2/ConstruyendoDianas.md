# Problema 2: Construyendo Dianas

___

Objetivo: Sumar un valor V a partir de las puntuaciones obtenidas pero con el menor numero de tiros que sea posible. 

En este caso SI podemos tiros, asi que es como el problema de las monedas donde tenemos "objetos ilimitados" en busca de la minimizacion de los tiros.



1. Definicion de la función: 

   Diana(i, j) = menor numero de tiros posibles para conseguir sumar un valor V utilizando las puntuaciones obtenidas de la 1 a la i.

2. Defincion recursiva: 

   Diana(i, 0) = 0

   Diana(0, j) = INF

​	

​	Diana(i, j) = Diana(i - 1, j) 									     si puntuacion[i] > j

​				min(Diana(i - 1, j), Diana(i, j - puntuacion[i]) + 1)     si puntuacion[i] <= j



3. Idea de recuperar la solución.
   1. Si el resultado anterior era igual al de ahora, el valor actual no es optimo, buscamos en la fila anterior. 
4. Coste de la solución: 
   * Temporal O(n x S) (pseudopolinomial)
   * Espacial O(n x S) (pseudopolinomial)