#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

int obtenId(string const& nombre, map<string, int> &id){
    auto it = id.find(nombre);
    if(it != id.end()) return it->second;
    int nuevo = id.size();
    id[nombre] = nuevo;

    return nuevo;
}


int gradosSeparacion(vector<vector<int>> &distancia, int P){

    for(int k = 0; k < P; ++k){
        for(int i = 0; i < P; ++i){
            for(int j = 0; j < P; ++j){
                if(distancia[i][k] < 9999 && distancia[k][j] < 9999){ // merece la pena actualizar
                    distancia[i][j] = min(distancia[i][j], distancia[i][k] + distancia[k][j]);
                }
            }
        }
    }
    int sepMax = 0;

    for(int i = 0; i < P; ++i){
        for(int j = 0; j < P; ++j){
            sepMax = max(distancia[i][j], sepMax);
        }
    }

    return sepMax;

}

bool resuelveCaso(){
    int P, R; cin >> P >> R;
    if(!cin) return false;

    map<string, int> id;
    vector<vector<int>> distancia(P, vector<int>(P, 9999));

    // idempotencia
    for(int i = 0; i < P; ++i) distancia[i][i] = 0;

    for(int r = 0 ; r < R; ++r){
        string a, b; cin >> a >> b;
        int u = obtenId(a, id);
        int v = obtenId(b, id);
        if(u != v){
            distancia[u][v] = 1;
            distancia[v][u] = 1;
        }
    }

    int res = gradosSeparacion(distancia, P);
    if(res != 9999) cout << res;
    else cout << "DESCONECTADA";
    cout << '\n';
    return true;
}


int main(){
    while(resuelveCaso());
    return 0;
}