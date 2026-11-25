#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>
using namespace std;

struct Nodo{
    int k ;
    vector<int> sol;
    vector<int> stock;

    int precio;
    int precio_estimado;
    bool operator<(Nodo const& o) const {
        return o.precio_estimado < precio_estimado;
    }
};

vector<int> optimista(vector<vector<int>> const& precios, int m, int p){ //infravaloramos el coste no teniendo en cuenta la restriccion de maximo 3 productos por supermercado
    
    vector<int> opt(p + 1);
    for(int i = p - 1; i >= 0; --i){
        
        int minim = precios[0][i];
        for(int j = 0; j < m; ++j){
            if(minim > precios[j][i]) minim = precios[j][i];
        }
        opt[i] = opt[i + 1] + minim;
    }

    return opt;
}


int pesimista(vector<vector<int>> const& precios, int m, int p, Nodo const& X){
    vector<int> stock = X.stock;
    int pes = X.precio;

    for(int i = X.k + 1; i < p; ++i){
        int minim = -1;
        for(int j = 0; j < m; ++j){
            if(stock[j] > 0 && (minim == -1 || precios[minim][i] > precios[j][i])){
                minim = j;
            }
        }
        if(minim == -1) return INT_MAX;   // no completable desde X
        stock[minim]--;
        pes += precios[minim][i];
    }

    return pes;
}

void supermercado_rp(vector<vector<int>> const& precios, int m, int p, vector<int> & sol_mejor, int& precio_mejor){

    Nodo Y;
    Y.k = -1;
    Y.sol = vector<int>(p, 0); //  sol[i] = j donde cada producto i indica en que supermercado j ha sido comprado.
    Y.stock = vector<int>(m, 3);
    Y.precio = 0;

    vector<int> opt = optimista(precios, m, p);
    Y.precio_estimado = Y.precio + opt[Y.k + 1];

    precio_mejor = pesimista(precios, m, p, Y);


    priority_queue<Nodo> q;
    q.push(Y);

    while(!q.empty() && q.top().precio_estimado <= precio_mejor){
        Y = q.top(); q.pop();
        Nodo X(Y);
        X.k++; // producto
        for(int s = 0; s < m; ++s){ // recorremos todos los supermercados
            if(Y.stock[s] > 0){
                X.stock[s]--;
                
                X.sol[X.k] = s;
                X.precio = Y.precio + precios[s][X.k];
                
                if(X.k == p - 1){
                    if(X.precio < precio_mejor){
                        precio_mejor = X.precio;
                        sol_mejor = X.sol;
                    }
                }
                else {
                    X.precio_estimado = X.precio + opt[X.k + 1];
                    if(X.precio_estimado <= precio_mejor){
                        precio_mejor = min(pesimista(precios, m, p, X), precio_mejor);
                        q.push(X);
                    }
                }
                
                X.stock[s]++;
            }
        }
        // no hay rama de no elegido porque todo producto debe ser comprado.
    }
}

void resuelveCaso()
{
    int m, p; cin >> m >> p;

    vector<vector<int>> precios(m, vector<int>(p, 0));

    // leemos los datos.
    for(int i = 0; i < m; ++i){
        for(int j = 0; j < p; ++j){
            cin >> precios[i][j];
        }
    }

    if(p == 0) {
        cout << p << endl;
    }
    else if(p > 3*m) cout << "Sin solucion factible\n";
    else{
        // llamamos a la funcion: 
        vector<int> sol_mejor(p, -1);
        int precio_mejor = -1;
        
        supermercado_rp(precios, m, p, sol_mejor, precio_mejor);
        for(auto &i: sol_mejor) cout << i << " ";
        cout << endl;
        if(precio_mejor != -1){
            cout << precio_mejor << endl;
        }
        else cout << "Sin solucion factible\n";

    }

}   

int main(){
    int n; cin >> n;
    for(int i = 0; i < n; ++i){
        resuelveCaso();
    }

    return 0;
}