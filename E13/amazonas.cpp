#include <iostream>
using namespace std;


void aventurilla(vector<vector<int>> &rutaOptima, int poblados){


    for(int k = 1; k < poblados - 1; ++k){ // empezamos desde k = 1 ya que sabemos que desde el poblado 1 no podemos volver al poblado 0, porque es rio abajo por eso empezamos en 1 y no en 0.
        //k < poblados - 1 porque 0 <= i < k < j <= poblados-1. Ademas, nunca tendremos el ultimo poblado como poblado intermedio
        /* Mejor dicho: 
        
            // k es intermedio: necesita i < k < j, con i >= 0 y j <= poblados-1.
            // Por eso k >= 1 (no hay origen antes del 0) y k <= poblados-2 (no hay destino después del último).
        
        */
        for(int i = 0; i < k; ++i){
            for(int j = k + 1; j < poblados; ++j){
                int temp = rutaOptima[i][k] + rutaOptima[k][j];

                if(rutaOptima[i][j] > temp) rutaOptima[i][j] = temp;
            }
        }
    }
}


bool resuelveCaso(){
    int poblados; cin >> poblados;
    if(!cin) return false;

    vector<vector<int>> coste(poblados - 1, vector<int>(poblados, 0));

    for(int i = 0; i < poblados; i++){
        for(int j = i + 1; j < poblados; ++j){
            cin >> coste[i][j];
        }
    }
    
    vector<vector<int>> rutaOptima = coste; // K = 0 (Caso base.)


    aventurilla(rutaOptima, poblados);

    // imprimimos la matriz: 
    
    for(int i = 0; i < poblados - 1; i++){
        for(int j = i + 1; j < poblados; ++j){
            cout << rutaOptima[i][j] << " ";
        }
        cout << endl;
    }



    return true;
}

int main() {

    while(resuelveCaso());

    return 0;
}