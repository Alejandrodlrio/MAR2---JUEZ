# Problema 9: Carpintero Ebanisto
___

Objetivo: Se deben hacer unos cortes y se deben hacer en el orden mas eficiente para minimizar el esfuerzo realizado.

 Ejemplo de matrix chain multiplicatoin![matrix chain multiplication](/Users/alejandro/Documents/MAR2 - LAST DANCE/MAR2 - JUEZ/E9/matrix chain multiplication.jpg)







Este tipo de problemas forma parte del esquema de intervalos (por ejemplo, el Matrix chain multiplication). 

```markdown
Esquema: 

1. Entender que se busca: 
 - Hay que elegir un orden para los cortes. Con 3 cortes hay 3! ordenes posibles. (inviable si no lo solucionamos mediante programacion dinamica)

2. Fijar las posiciones relevantes: 	
	- Añadimos los esstremos del tablon a las marcas. 			
			p0=0;
			pn+1=L; 
3. Definimos la funcion
	E(i, i+1) = si entre dos marcas consecutivas no hay ningun corte, el esfuerzo es minimo = 0.
	
4. Definición recursiva

	Supongamos el ejemplo: 0, 3, 6, 8, 10. 
		Con E(0, 2) tenemos en medio la marca 3. por tanto, la unica opción: E(0,1) + E(1, 2) + 2(6-0) = 0 + 0 + 12 = 12.
```





Para mejorar las dudas consultar cuaderno en goodNotes.



> El problema es parecido al de Matrix chain multiplication

1. Defincion de la función

​	Carpintero(i, j) = esfuerzo minimo que hará el carpintero ebanisto para realizar los cortes entre i y j (donde i < j )sobre el tablon de longitud L[j] - L[i]

2. Defincion recursiva: 

   Caso base: 

   ​	carpintero(i, i + 1) = 0 

   Caso recursivo: 

   ​	E(i, j) = min over i < k < j de [ E(i, k) + E(k, j) + 2(pⱼ − pᵢ) ], para j − i  >= 2,



