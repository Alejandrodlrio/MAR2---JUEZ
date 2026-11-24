#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

/*
    1. Definicion del espacio de soluciones.
        El espacio de soluciones esta formado por el conjunto de tuplas de la forma sol[i] = trabajo, que satisfacen las restricciones explicitas. 
    2. La estructura del arbol: 
       
    El árbol tiene n niveles, uno por funcionario. En el nivel i, cada rama corresponde a un trabajo todavía libre. Las hojas factibles son n!.
    El árbol completo sin podar tendría n^n hojas, pero la restricción de tener trabajos unicos reduce el número de ramas en cada nivel. teniendo en el nivel k, n - k + 1 ramas.



    3. Restricciones: 
        - Explicitas:  cada posicion sol[i] representa el trabajo asignado al funcionario i.
        La asignacion es de tal forma que cada funcionario tiene exactamente un trabajo y cada trabajo lo realiza exactamente un solo funcionario.

        - Implicitas: Una solucion parcial de nivel k solo es viable si su suma acumulada + la cota inferior de los funcionarios restantes es estrictamente menor que el coste de la mejor solucion completa encontrada hasta el momento.
        Los nodos que no cumplan dicha condicion se descartan  
*/


struct Nodo {
    int k;
    vector<int> sol;
    vector<bool> asignados; // condicion implicita
    int suma;
    int suma_estimada;
    bool operator<(Nodo const& o) const {
        return o.suma_estimada < suma_estimada;
    }
};

vector<int> optimo(vector<vector<int>> const& tabla, Nodo const& X){
    int n = tabla.size();
    vector<int> optimo(n + 1);

    for(int i = n - 1; i >= 0; --i){
        int minim = tabla[i][0];
        for(int j = 0; j < n; ++j){
            if(minim > tabla[i][j]) minim = tabla[i][j];
        }
        optimo[i] = optimo[i + 1] + minim; // vector de acumulados
    }

    return optimo;
}

int pesimista(vector<vector<int>> const& tabla, Nodo const& X){
    int n = tabla.size();

    vector<bool> asign = X.asignados; // copiamos los trabajos ya asignados.
    int pes = X.suma;
    for(int i = X.k + 1; i < n; ++i){
        int tElegido = -1;
        for(int j = 0; j < n; ++j){
            if(!asign[j] && (tElegido = -1 || tabla[i][j] < tabla[i][tElegido])){ // mientras el trabajo no se haya asignado nunca y el funcionario actual no tiene trabajo asignado, escogemos el minimo
                tElegido = j;
            }
        }
        pes += tabla[i][tElegido];
        //marcamos para el resto de trabajos
        asign[tElegido] = true;
    }

    return pes;
}


void funcionarios_rp(vector<vector<int>> const& tabla, vector<int> &sol_mejor, int &suma_mejor){

    int n = tabla.size();
    Nodo Y;
    Y.k = -1;
    Y.sol = vector<int>(n, -1);
    Y.asignados = vector<bool>(n, false);
    Y.suma = 0;
    vector<int> opt = optimo(tabla, Y);
    Y.suma_estimada = 0 + opt[Y.k + 1];

    suma_mejor = pesimista(tabla, Y);

    priority_queue<Nodo> q;
    q.push(Y);
    
    while(!q.empty() && q.top().suma_estimada < suma_mejor){

        Y = q.top(); q.pop();
        Nodo X(Y);
        ++X.k;
        for(int t = 0; t < n; ++t){ // recorremos todos los trabajos
            if(!Y.asignados[t]){
                
                X.asignados[t] = true; // marcamos
                X.sol[X.k] = t;
                X.suma = Y.suma + tabla[X.k][t];
                X.suma_estimada = X.suma + opt[X.k + 1];
                if(X.suma_estimada < suma_mejor){
                    if(X.k == n - 1){
                        suma_mejor = X.suma;
                        sol_mejor = X.sol;
                    }
                    else{
                        q.push(X);
                        suma_mejor = min(suma_mejor, pesimista(tabla, X));
                    }
                }


                X.asignados[t] = false;

            }
        }
    }




}

bool resuelveCaso(){
    int n; cin >> n; 
    if(n == 0) return false;

    vector<vector<int>> tabla(n, vector<int>(n, 0)); 

    for(int i = 0; i < n; ++i){ // funcionarios
        for(int j = 0; j < n; ++j){ // trabajos
            cin >> tabla[i][j];
        }
    }

    vector<int> sol_mejor;
    int suma_mejor = -1;
    funcionarios_rp(tabla, sol_mejor, suma_mejor);

    cout << suma_mejor << "\n";

    return true;
}
int main(){
    while(resuelveCaso());
    return 0;
}