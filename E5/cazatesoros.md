# Problema 5: Cazatesoros
___

Por el GPS conocemos:  <u>Sonar</u>, <u>Profundidad</u>, <u>Cantidad de oro</u>. Marcos dispone de una botella de aire de capacidad T segundos. En cada inmersión solamente podrá subir uno de los cofres. El tiempo de descenso a una profundidad p es de p segundos mientras que el tiempo de ascenso es de 2p segundos.



1. Defincion de la función: 

   Cazatesoros(i, j) = Cantidad maxima de oro que podemos obtener  usando los cofres del 1 al i, con una botella de aire que permite una inmersión de j segundos donde cada cofre k requiere un coste de 3pk segundos.

Defincion recursiva: 

​	cazatesoros(i, 0) = 0

​	cazatezoros(0, j) =  0

​	

​	Cazatesoros(i, j) = 	cazatesoros(i - 1, j)			si 3*v[i].p > j  

​							max(cazatesoros(i - 1, j),

​								 cazatesoros(i - 1, j - 3*v[i].p) + v[i].oro)    si 3*v[i].p <= j  





Coste en tiempo y espacio: O(N*T) pseudopolinomial. 

