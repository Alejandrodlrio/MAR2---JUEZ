#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct Pelicula {
    int ini; // hora de inicio
    int final; // hora de finalizacion
    int dur; // duracion
};

int maraton(vector<int> &cine, vector<Pelicula> const& peliculas, int n){
    // Caso base: cine(0) = 0 ; // No hay peliculas
    // Caso recursivo: c[i] = max(c[i - 1], c[k] + peliculas[i - 1].dur) donde k = indica la cantidad de peliculas tal que su horario de fin es superior al horario de inicio de la pelicula actual - 10.
                        // es decir, nos indica la ultima pelicula compatible para poder encadenar visionado de peliculas.
    
    // Se podria hacer sobre el vector peliculas pero resulta mas claro asi aunque un pelin peor en espacio ya que sumamos +O(n):
    vector<int> fins(n);
    for(int i = 0; i < n; ++i) fins[i] = peliculas[i].final; // ya ordenadas por orden de finalizacion

    for(int i = 1; i <= n; ++i){

        int k = upper_bound(fins.begin(), fins.end(), peliculas[i - 1].ini - 10) - fins.begin(); // devuelve la primer pelicula compatible superior en orden de finalizacion a la pelicula actual + el margen. mediante busqueda binaria.
        
        cine[i] = max(cine[i - 1], peliculas[i - 1].dur + cine[k]);
        
    }
    return cine[n];
}


// Coste final: 
/*
O(log n) del uppper bound pero n veces... n * log n
O(n log n) del sort
O(n) + O(n) de los bucles

total = O(2n + 2 * n log n)= O(n log n)
*/
bool resuelveCaso(){
    
    int n; cin >> n;
    if(n == 0) return false;

    vector<int> cine(n + 1);

    vector<Pelicula> peliculas(n);

    for(int i = 0; i < n; ++i){
        int d, h, min, dur;
        char sep; 
        cin >> d >> h >> sep >> min >> dur;
        peliculas[i].ini = d*1440 + h*60 + min;
        peliculas[i].final = peliculas[i].ini + dur;
        peliculas[i].dur = dur;
    }

    sort(peliculas.begin(), peliculas.end(), [](Pelicula const& a, Pelicula const& b){ // ordenamos por duracion final 
       return  a.final < b.final;
    });


    cout << maraton(cine, peliculas, n) << endl;

    return true;
}

int main(){
    while(resuelveCaso());
}