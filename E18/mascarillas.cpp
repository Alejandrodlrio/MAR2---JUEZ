#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <queue>
using namespace std;
//  n >= 1 universidades.
// cada facultad necesita m > 0 mascarillas
// m >= suministradores de mascarillas
// un suministrador puede dar mascarillas a una facultad ; // vector de asign[sumin] = id_universidad
// Una facultad puede recibir mascarillas de mas de un suministrador.
// objetivo: minimizar el coste total de las mascarillas en p.t universidad.
// Cada universidad pagará por las mascarillas que necesite (hasta que se queden a cero)
struct Mascarillas {
    int cantidad;
    int precio;
};
struct Nodo {
    int k ; // nivel = suministradores
    vector<int> sol; // Sol[sumin] = universidad. 
    vector<int> necesidad; // necesidad[universidad]
    vector<Mascarillas> stock; // stock de cada suministrador.
    int coste;
    int coste_estimado;
    bool operator<(Nodo const& o) const {
        return o.coste_estimado < coste_estimado;
    }
};

bool necesidadCubierta(vector<int> const& necesidad){
    int i = 0;
    int n = necesidad.size();
    while(i < n && necesidad[i] == 0) ++i;
    return i == n;
}

// relajamos las restricciones subestimando el cota optimista sabiendo quepodemos volver a utilizar el mismo suministrador siempre y cuando aun haya stock
int cota_optimista(Nodo const& X, vector<int> const& facultad){
    int n = facultad.size();
    int m = X.stock.size();
    int opt = X.coste;
    vector<Mascarillas> stock_parcial = X.stock;
    vector<int> necesidad_parcial = X.necesidad;
    for(int f = 0; f < n; ++f){
        for(int s = X.k + 1; s < m; ++s){
            if(stock_parcial[s].cantidad > 0 && necesidad_parcial[f] > 0){
                int minim = min(necesidad_parcial[f], stock_parcial[s].cantidad);
                necesidad_parcial[f] -= minim;
                stock_parcial[s].cantidad -= minim;

                opt += minim*stock_parcial[s].precio;
            }
        }

    }   

    return opt;
}


//cota pesimista: respetamos las restricciones dando una cota superior al coste real. 
int cota_pesimista(Nodo const& X, vector<int> const& facultad, vector<int> & sol_aux){
    int n = facultad.size();
    int m = X.stock.size();
    int pes = X.coste;
    vector<Mascarillas> stock_parcial = X.stock;
    vector<int> necesidad_parcial = X.necesidad;
    for(int f = 0; f < n; ++f){
        for(int s = X.k + 1; s < m; ++s){
            if(stock_parcial[s].cantidad > 0 && necesidad_parcial[f] > 0){
                int minim = min(necesidad_parcial[f], stock_parcial[s].cantidad);
                necesidad_parcial[f] -= minim;
                stock_parcial[s].cantidad = 0;
                pes += minim*stock_parcial[s].precio;
                sol_aux[s] = f;
            }
        }
    }   

    return necesidadCubierta(necesidad_parcial) ? pes : INT_MAX;
}



void mascarillas_rp(vector<int> const& facultad, vector<Mascarillas> const& suministrador, int &coste_mejor, vector<int> &sol_mejor){
    int n = facultad.size();
    int m = suministrador.size();

    Nodo Y;
    Y.k = -1;
    Y.sol = vector<int>(m, -1); // -1 indica que no ha suministrado a ninguna universidad.

    Y.necesidad = facultad;
    Y.stock = suministrador;

    Y.coste = 0;
    Y.coste_estimado = cota_optimista(Y, facultad);

    vector<int> sol_aux = Y.sol;
    coste_mejor = cota_pesimista(Y, facultad, sol_aux);
    if(coste_mejor != INT_MAX) sol_mejor = sol_aux;

    priority_queue<Nodo> q;
    q.push(Y);

    while(!q.empty() && q.top().coste_estimado < coste_mejor){
        Y = q.top(); q.pop();
        Nodo X(Y);
        ++X.k;
        if(Y.stock[X.k].cantidad > 0){
            for(int i = 0; i < n; ++i){
                if(Y.necesidad[i] > 0){
                    X.sol[X.k] = i;
                    int minim = min(Y.stock[X.k].cantidad, X.necesidad[i]);
                    X.necesidad[i] = Y.necesidad[i] - minim;
                    X.stock[X.k].cantidad = Y.stock[X.k].cantidad - minim;
                    X.coste = Y.coste + minim*X.stock[X.k].precio;
                    X.coste_estimado = cota_optimista(X, facultad);
                    if(X.coste_estimado < coste_mejor){
                        if(X.k == m - 1){
                            if(necesidadCubierta(X.necesidad) && X.coste < coste_mejor){
                                coste_mejor = X.coste;
                                sol_mejor = X.sol;
                            }
                        }
                        else {
                            q.push(X);
                            sol_aux = X.sol;
                            int pes = cota_pesimista(X, facultad, sol_aux);
                            if(pes < coste_mejor) 
                            {
                                coste_mejor = pes; 
                                sol_mejor = sol_aux;
                            } 
                        }
                    } 
                

                    X.necesidad[i] = Y.necesidad[i];
                    X.stock[X.k].cantidad = Y.stock[X.k].cantidad;
                }
            }
        }
        // no coger ninguna mascarilla de este : 
        X.sol[X.k] = -1;
        X.necesidad = Y.necesidad;
        X.stock = Y.stock;
        X.coste = Y.coste;
        X.coste_estimado = cota_optimista(X, facultad);
        if(X.coste_estimado < coste_mejor){
            if(X.k == m - 1){
                if(necesidadCubierta(X.necesidad) && X.coste < coste_mejor){
                    coste_mejor = X.coste;
                    sol_mejor = X.sol;
                }
            }
            else {
                q.push(X);
                sol_aux = X.sol;
                int pes = cota_pesimista(X, facultad, sol_aux);
                if(pes < coste_mejor) 
                {
                    coste_mejor = pes; 
                    sol_mejor = sol_aux;
                } 
            }
        } 


    }
       
}


void resuelveCaso(){
    int u, s; cin >> u >> s;
    
    vector<int> facultad(u);
    vector<Mascarillas> suministrador(s);
    for(auto &i: facultad) cin >> i;
    for(auto &i: suministrador) cin >> i.cantidad;
    for(auto&i: suministrador) cin >> i.precio;
    
    if(u == 0) {
        cout << 0 << endl;

    }else{

        int coste_mejor;
        vector<int> sol_mejor = vector<int>(s, -1);
        mascarillas_rp(facultad, suministrador, coste_mejor, sol_mejor);

        
        if(coste_mejor != INT_MAX){
            cout << coste_mejor << "\n";
            cout << "sol : " ;for(auto &i: sol_mejor) cout << i << " ";
            cout << endl;
        }
        else{
            cout << "NO\n";
        }
    }
    

}

int main(){
    int n; cin >> n;
    for(int i = 0; i < n; i++){
        resuelveCaso();
    }
    return 0;
}