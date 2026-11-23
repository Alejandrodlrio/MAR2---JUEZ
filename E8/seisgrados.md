# Problema 8: Seis grados de separacion.
___

Objetivo: Queremos averiguar el grado de sepracion de una red de personas. Para dos personas, su grado de separación es el numero minimo de relaciones que hay que travesar para conectarlas. Para una red, el grado de separación es el maximo grado de separación entre dos personas cualesquiera de la red. O sea, el numero minimo de relaciones se refiere al numero de "aristas" que debmos atravesar.







1. Definición de la funcion: 

   Separacion^k(i, j) = numero minimo de relaciones entre las personas i y j pudiendo utilizar como personas intermedias aquellas entre 1 y k. 

2. Defincion recursiva:

   Casos base

   ​	separación^k(i, i) = 0 (idempotencia)

   ​	separación^k(i, j) = 1 si i y j tienen relacion directa 

   ​	separación^k(i, j) = INF si i y j no tienen relacion directa

   Caso recursivo: 

   ​	separación^k(i, j) = min(separación^(k - 1)(i, j), 

   ​								separación^(k - 1)(i, k) + separación^(k-1)(k, j) 

   ​							  )

3. Rellenamos las celdas de la matriz celda a celga segun k.
