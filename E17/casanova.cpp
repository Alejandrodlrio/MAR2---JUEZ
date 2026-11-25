#include <iostream>
#include <climits>
#include <vector>
#include <algorithm>
#include <queue>
#include <cmath>
using namespace std;



struct Nodo {
    int k; // nivel: canciones.
    vector<int> cinta; //cinta[i] = #cara, donde i indica la cancion que estamos tratando.
    vector<int> almacenamiento;
    int puntuacion;
    int puntuacion_estimada;
    bool operator<(Nodo const& o) const{
        return o.puntuacion_estimada > puntuacion_estimada;
    }
};
//Arbol ternario: 0 -> metemos en la cara A, 1-> metemos en la cara B, 3 -> no grabamos la cancion. 

struct Cancion {
    int dur;
    int punt;
};
// estimacion optimista y pesimista como la mochila, partimos las canciones sobreestimando el coste en optimista e intentamos meter lo que nos quede en la pesimista respetando las restricciones.
int optimista(vector<Cancion> const& canciones, Nodo const& X){
    int n = canciones.size();
    double opt = X.puntuacion;
    double hueco = X.almacenamiento[1] + X.almacenamiento[0]; // simplificamos el hueco con un hueco comun.
    int i = X.k + 1;
    while(i < n && hueco > 0){
        if(hueco - canciones[i].dur >= 0){
            hueco -= canciones[i].dur;
            opt += canciones[i].punt;
        }
        else{
            opt += hueco * canciones[i].punt / canciones[i].dur;
            hueco = 0;
        }
        ++i;
    }
 

    return (int)floor(opt);
    
} 


int pesimista(vector<Cancion> const& canciones, Nodo const& X){
    int n = canciones.size();
    int pes = X.puntuacion;
    int huecoA = X.almacenamiento[0];
    int huecoB = X.almacenamiento[1];
    int i = X.k + 1;

    while(i < n){
        if(huecoA - canciones[i].dur >= 0){
            pes +=  canciones[i].punt;
            huecoA -= canciones[i].dur;
        }
        else if(huecoB - canciones[i].dur >= 0){
            pes += canciones[i].punt;
            huecoB -= canciones[i].dur;
        }
        // si no cabe descartamos y vamos al siguiente.
        ++i;
    }


    return pes;
    
} 


void cintas(vector<Cancion> const& canciones, int dur, int &punt_mejor){
    int n = canciones.size();
    Nodo Y;
    Y.k = -1;
    Y.puntuacion = 0;
    Y.cinta = vector<int>(n, -1);
    Y.almacenamiento = vector<int>(2, dur);
    Y.puntuacion_estimada = optimista(canciones, Y);
    punt_mejor = pesimista(canciones, Y);

    priority_queue<Nodo> q;
    q.push(Y);

    while(!q.empty() && q.top().puntuacion_estimada >= punt_mejor){
        Y = q.top(); q.pop();
        Nodo X(Y);
        X.k++;
        if(Y.almacenamiento[0] - canciones[X.k].dur >= 0){ // metemos en cara a
            X.almacenamiento[0] -= canciones[X.k].dur; 
            X.puntuacion = Y.puntuacion + canciones[X.k].punt;
            X.cinta[X.k] = 0;
            X.puntuacion_estimada = optimista(canciones, X);
            if(X.puntuacion_estimada >= punt_mejor){
                if(X.k == n - 1){
                    punt_mejor = X.puntuacion;
                    //sol_mejor = X.cinta;
                }
                else{
                    q.push(X);
                    punt_mejor = max(punt_mejor, pesimista(canciones, X));
                }
            }
            X.almacenamiento[0] += canciones[X.k].dur; 

        }
        if(Y.almacenamiento[1] - canciones[X.k].dur >= 0){ // metemos en cara b
            X.puntuacion = Y.puntuacion + canciones[X.k].punt;
            X.almacenamiento[1] -= canciones[X.k].dur; 
            X.cinta[X.k] = 1;
            X.puntuacion_estimada = optimista(canciones, X);
            if(X.puntuacion_estimada >= punt_mejor){
                if(X.k == n - 1){
                    punt_mejor = X.puntuacion;
                    //sol_mejor = X.cinta;
                }
                else{
                    q.push(X);
                    punt_mejor = max(punt_mejor, pesimista(canciones, X));
                }
            }
            X.almacenamiento[1] += canciones[X.k].dur; 
        }
        //No metemos la cancion
        X.almacenamiento = Y.almacenamiento; // no es necesario pero quiero que se vea que se mantiene el almacenamiento porque no guardamos la cancion en ningun lado
        X.puntuacion = Y.puntuacion; // no guardamos la cancion
        X.cinta[X.k] = 3;
        X.puntuacion_estimada = optimista(canciones, X);
        if(X.puntuacion_estimada >= punt_mejor){
            if(X.k == n - 1){
                punt_mejor = X.puntuacion;
                //sol_mejor = X.cinta;
            }
            else{
                q.push(X);
                punt_mejor = max(punt_mejor, pesimista(canciones, X));
            }
        }



    }
}


bool resuelveCaso(){
    int n; cin >> n;
    if(n == 0) return false;

    int dur; cin >> dur;

    vector<Cancion> canciones(n);
    for(auto &i: canciones) cin >> i.dur >> i.punt;
    // ordenamos las canciones por ratio punt/dur tal que consideramos antes las que tengan un mayor punt/dur
    sort(canciones.begin(), canciones.end(), [](Cancion const& a, Cancion const& b){
        return (a.punt*b.dur) > (a.dur*b.punt);
    });
    int punt_mejor;
    cintas(canciones, dur, punt_mejor);

    cout << punt_mejor << endl;

    return true;
}

int main(){
    while(resuelveCaso());
    return 0;
}