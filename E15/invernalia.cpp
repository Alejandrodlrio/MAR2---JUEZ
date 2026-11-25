#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Anchura {
    int anchura;
};

struct Nodo {
    int k;
    vector<int> sol;
    vector<bool> limpios; // vector de camino "limpios"; limpios[camino] = bool
    int calidad;
    int calidad_estimada;
    bool operator<(Nodo const& o) const {
        return calidad_estimada < o.calidad_estimada; // objetivo: maximizar la calidad de limpieza
    }

};




int pesimista(Nodo const& X, vector<Anchura> const& carros, vector<Anchura> const& caminos, vector<vector<int>> const& calidad){
    
    int n = carros.size();
    int m = caminos.size();
    int pes = X.calidad;

    vector<bool> limpios_parcial = X.limpios;

    for(int i = X.k + 1; i < n; ++i){
        int camElegido = -1;
        for(int j = 0; j < m; ++j){
            if(!limpios_parcial[j] && carros[i].anchura <= caminos[j].anchura && (camElegido == -1 || calidad[i][j] > calidad[i][camElegido])){ // sobreestimamos el coste haciendo que cualquier carro si obtenemos la limpieza maxima pueda limpiar el mismo camino ya "asignado"
                camElegido = j;
            }
        }
        if(camElegido != -1){
            pes += calidad[i][camElegido];
            limpios_parcial[camElegido] = true;
        }
    }

    return pes;
}


int optimista(Nodo const& X, vector<Anchura> const& carros, vector<Anchura> const& caminos, vector<vector<int>> const& calidad){
    int n = carros.size();
    int m = caminos.size();
    int opt = X.calidad;
    for(int i = X.k + 1; i < n; ++i){
        int camElegido = -1;
        for(int j = 0; j < m; ++j){
            if(carros[i].anchura <= caminos[j].anchura && (camElegido == -1 || calidad[i][j] > calidad[i][camElegido])){ // sobreestimamos el coste haciendo que cualquier carro si obtenemos la limpieza maxima pueda limpiar el mismo camino ya "asignado"
                camElegido = j;
            }
        }
        if(camElegido != -1){
            opt += calidad[i][camElegido];
        }

    }


    return opt;
}

void quitanieves_rp(vector<Anchura> const& caminos, vector<Anchura> const& carros, vector<vector<int>> const& calidad, vector<int> &sol_mejor, int &calidad_mejor){

    int n = carros.size();
    int m = caminos.size();

    Nodo Y;
    Y.k = -1;
    Y.limpios = vector<bool>(m, false);
    Y.sol = vector<int>(n, 0);
    Y.calidad = 0;
    Y.calidad_estimada = optimista(Y, carros, caminos, calidad);
    calidad_mejor = pesimista(Y, carros, caminos, calidad);

    priority_queue<Nodo> q;
    q.push(Y);

    while(!q.empty() && q.top().calidad_estimada >= calidad_mejor){

        Y = q.top();
        q.pop();
        Nodo X(Y);
        X.k++;
        for(int i = 0; i < m; ++i){ 
            if(!Y.limpios[i] && carros[X.k].anchura <= caminos[i].anchura){
                X.limpios[i] = true;
                
                X.sol[X.k] = i;
                X.calidad = Y.calidad + calidad[X.k][i];
                X.calidad_estimada = optimista(X, carros, caminos, calidad);
                if(X.calidad_estimada >= calidad_mejor){
                    if(X.k == n - 1){
                        calidad_mejor = X.calidad;
                        sol_mejor = X.sol;
                    }
                    else{
                        q.push(X);
                        calidad_mejor = max(pesimista(X, carros, caminos, calidad), calidad_mejor);
                    }
                }

                X.limpios[i] = false;
            }
        }
        // El carro es demasiado ancho para cualquier camino. Este carro no limpia nada: 
        X.limpios = Y.limpios;
        X.calidad = Y.calidad;
        X.sol[X.k] = -1; // -1 indica que el carro X.k no se ocupa de ningun camino.
        X.calidad_estimada = optimista(X, carros, caminos, calidad);
        if(X.calidad_estimada >= calidad_mejor){
            if(X.k == n - 1){
                calidad_mejor = X.calidad;
                sol_mejor = X.sol;
            }
            else{
                q.push(X);
                // calidad_mejor = max(pesimista(X, carros, caminos, calidad), calidad_mejor);
            }
        }

    }
    
}

void resuelveCaso(){
    
    int n, m; cin >> n >> m;

    
    vector<Anchura> carros(n);
    vector<Anchura> caminos(m);
    for(auto &i: carros) cin >> i.anchura;
    for(auto &i: caminos) cin >> i.anchura;

    vector<vector<int>> calidad(n, vector<int>(m, 0)); // matriz de calidad de limpieza
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            cin >> calidad[i][j];
        }
    }
    if(n == 0){
        cout << n << endl;
    } else{
        vector<int> sol_mejor(n, 0);
        int calidad_mejor = -1;
        
        quitanieves_rp(caminos, carros, calidad, sol_mejor, calidad_mejor);

        cout << calidad_mejor << "\n";
    }
   
    
    
}


int main(){
    int n; cin >> n;
    for(int i = 0; i < n; ++i){
        resuelveCaso();
    }
    return 0;
}