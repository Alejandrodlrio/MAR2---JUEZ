#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

int camino(vector<vector<int>> &matriz, vector<vector<int>> const& tablero, int n){
    
    matriz = tablero;

    for(int i = n - 1; i > 0 ; --i){
        for(int j = 0; j < n; ++j){
            int actual = matriz[i][j];
            if(matriz[i - 1][j] < actual + tablero[i - 1][j]){
                matriz[i - 1][j] = actual + tablero[i - 1][j];
            }

            if(j < n - 1 && matriz[i - 1][j + 1] < actual + tablero[i - 1][j + 1]){
                matriz[i - 1][j + 1] = actual + tablero[i - 1][j + 1];
            }
            if(j > 0 &&  matriz[i - 1][j - 1] < actual + tablero[i - 1][j - 1]){
                matriz[i - 1][j - 1] = actual + tablero[i - 1][j - 1];
            }
        }
    }

    // Buscamos la posicion de la mejor solucion de la primera fila del tablero (hallamos donde se encuentra el maximo y nos quedamos con su posicion)
    int maxVal = matriz[0][0];
    int indice = 0;
    for(int j = 1; j < n ; ++j){
        if(maxVal < matriz[0][j]) {
            maxVal = matriz[0][j];
            indice = j;
        }
    }

    return indice;
}

int reconstruccion(vector<vector<int>> const& matriz, int n, int indice){
    vector<int> ant(n, -1);
    ant[0] = indice;
    for(int i = 1; i < n; ++i){
        int mejorVal = matriz[i][ant[indice]];
        ant[i] = ant[i - 1];
        if(ant[indice] + 1 < n - 1 && mejorVal < matriz[i][ant[indice] + 1]){
            int mejorVal = matriz[i][ant[indice] + 1];
            ant[i] = ant[i - 1] + 1;
        }
        if(ant[indice] - 1 > 0&& mejorVal < matriz[i][ant[indice] - 1]){
            int mejorVal = matriz[i][ant[indice] - 1];
            ant[i] = ant[i - 1] - 1;
        }
        
    }


    return ant[n - 1] + 1; // para que comience en la pos + 1 (indica que debe ser de la 1 a la n)
    
}
bool resuelveCaso(){

    int n; cin >> n;
    if(!cin) return false;

    vector<vector<int>> tablero(n, vector<int>(n));

    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            cin >> tablero[i][j];
        }
    }

    vector<vector<int>> matriz(n, vector<int>(n, 0)); // matriz de coste
    int indice = camino(matriz, tablero, n);
    int pos = reconstruccion(matriz, n, indice); // matriz de anterior (posiblemente se pueda optimizar a un vector)
    // suma total
    cout << matriz[0][indice] << " " << pos << endl;





    // tablero resultante al aplicar programacion dinamica
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }

    return true;
}

int main(){
    while(resuelveCaso());
    return 0;
}