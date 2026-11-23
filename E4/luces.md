# Problema 4: Luces para una fiesta
___

Descripción del problema: 
- bombillas ilimitadas a bajo coste (pero de potencias determinadas)
- Cada organizador indicara la potencia minima para la sala.
Objetivo: Calcular la potencia que debe instalar cadad sala. sabiendo la potencia maxima y la minima de cada sala.

1. Definicion de la funcion: 

- bombillas(i, j) = coste mínimo para suplir una potencia máxima j con las potencias de las bombillas del 1 al i

2. Definicion recursiva: 

- Caso base: 
    bombillas(i, 0) = 0
    bomnillas(0, j) = INF

- Caso Recursivo: 
    bombillas(i, j) = min(bombillas(i - 1, j), bombillas(i, j - v[i].potencia) + v[i].coste);


3. Llamada inicial: bombillas(n, P)

4. Estilo de la solucion: La solucion se dará mediante programacion dinamica ascendente donde, por ultimo recorreremos el intervalo para saber el coste mínimo de entre las potencias minima y maxima contratada.

 