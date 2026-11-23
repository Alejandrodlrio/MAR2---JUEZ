# Problema 6: Aibofobia

____

> Aibofobia: miedo a las palabras que se leen igual de izquierda a derecha que de derecha a izquierda

Objetivo: queremos transformar cualquier palabra en un palindroma a base de añadir las letras que hagan falta en cualquier posición. Queremos hacerlo insertando el menor numero de letras que hacen falta para convertirla en un palindromo.



1. <u>Definición de la función:</u> 

​	aibo(i, j) = minimo numero de letras que debemos añadir a la subcadena [i ..  j] para convertirla en un palindromo.

2. <u>Definición recursiva:</u> 

   Caso base: 

   aibo(i, i) = 0 // diagonal

   aibo(i, j) = 0	si j < i  (subcadena vacia)

   Caso recursivo: 

   aibo(i, j) =     aibo(i + 1, j - 1)			si  s[i] == s[j]

   ​			min(aibo(i + 1, j), aibo(i, j - 1)) + 1 si s[i] != s[j]

   

3. <u>Llamada inicial</u> aibo(0, n - 1);

4. Se resuelve de forma descendente (top-down) con memoización. La tabla se inicializa a -1 para marcar las celdas no calculadas. La llamada inicial `aibo(0, n-1)` calcula recursivamente los subproblemas que necesita: cada celda se calcula una sola vez, y las llamadas posteriores a una celda ya calculada devuelven el valor almacenado. Los casos base son la diagonal (`aibo(i, i) = 0`) y la subcadena vacía (`aibo(i, j) = 0` si `j < i`). La solución es `aibo(0, n-1`
