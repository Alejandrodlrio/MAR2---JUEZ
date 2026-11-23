#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

int carpintero(vector<vector<int>> & E, vector<int> const& cortes){

    int n = cortes.size(); // #cortes + 2. Ese 2 es para meter el 0 y la longitud maxima del tablon como cortes del intervalo.

    for (int i = 0; i + 1 < n; ++i)
        E[i][i + 1] = 0;                       // caso base

    for(int len = 2; len < n; ++len){ // longitud que hay entre los indices, con len = 2 nos aseguramos que haya minimo un corte dentro del intervalo
        for(int i = 0; i + len < n; ++i){ // La recurrencia solo aplica cuando hay marcas intermedias., por eso i, i+1 es caso base, i, i + 2 ya aplica recurrencia.
            // hacemos que i + len sea j de tal forma nunca lleguemos a j pues (i < j)
            int j = i + len;
            int mejor = 9999;
            for(int k = i + 1; k < j; ++k) {
                mejor = min(mejor, E[i][k] + E[k][j] + 2 * (cortes[j] - cortes[i]));
            }
            E[i][j] = mejor;
            
        }

        // recorremos la matriz por diagonales.
    }
    return E[0][n - 1];
}
bool resuelveCaso(){
    int L, c; cin >> L >> c;
    if(L == 0 && c == 0) return false;

    vector<int> cortes(c + 2);
    cortes[0] = 0;
    for(int i = 1; i <= c; ++i) cin >> cortes[i];
    cortes[c + 1] = L;

    vector<vector<int>> E(c + 2, vector<int>(c + 2, 0));
    
    carpintero(E, cortes);


    return true;
}

int main(){
    while(resuelveCaso());
    return 0;
}