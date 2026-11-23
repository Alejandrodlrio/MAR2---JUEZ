#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct Moneda {
    int cantidad;
    int valor;
};
struct Paquete {
    int peso; // peso total, pack*valor
    int pack; // Representacion binaria
};


int monedasBinarias(vector<vector<int>> &matriz, vector<Paquete> const& paquetes, int n, int C){

    //Caso base: i,0 -> 0; 0, j = INF 1 <= j < C
    matriz[0][0] = 0;
    for(int i = 1 ; i <= n; ++i){
        matriz[i][0] = 0;
        for(int j = 1; j <= C; ++j){
            if(paquetes[i - 1].peso > j) matriz[i][j] = matriz[i - 1][j];
            else{
                matriz[i][j] = min(matriz[i - 1][j], matriz[i - 1][j - paquetes[i - 1].peso] + paquetes[i - 1].pack);
            }
        }
    }

    return matriz[n][C];

}


bool resuelveCaso(){
    int n; cin >> n;
    if(!cin) return false;

    vector<Moneda> monedas(n);
    for(int i = 0; i < 2; ++i){
        for(int j = 0; j < n; ++j){
            if(i == 0) cin >> monedas[j].valor;
            else if(i == 1) cin >> monedas[j].cantidad;
        }
    }
    int C; cin >> C; // Cantidad a pagar.

    //Montamos paquetes multiplos de 2 de cada moneda
    vector<Paquete> paquetes;

    for(int i = 0; i < n; ++i){
        int cantidad = monedas[i].cantidad;
        int pack = 1;
        
        while(pack <= cantidad){

            cantidad -= pack; 
            paquetes.push_back({monedas[i].valor*pack, pack});
            pack *= 2;
        }
        if(cantidad > 0) paquetes.push_back({cantidad*monedas[i].valor, cantidad}); // creamos un paquete que simboliza el residuo, es decir, tenemos potencias de 2 + residuo
    }


    // nueva matriz con filas nuevas organizadas por paquetes.
    vector<vector<int>> matriz(paquetes.size() + 1, vector<int>(C + 1, 99999));
   
    int res = monedasBinarias(matriz, paquetes, paquetes.size(), C);
    
    if(res != 99999) cout << "SI " << res;
    else cout << "NO";
    cout << "\n";

    return true;
}

int main(){
    while(resuelveCaso());
    return 0;
}