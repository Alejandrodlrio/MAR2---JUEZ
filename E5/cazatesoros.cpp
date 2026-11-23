#include <iostream>
#include <vector>
#include <fstream>
using namespace std;


struct Tesoro {
    int profundidad;
    int oro;
};


void cazatesoros(vector<vector<int>> & matriz, vector<Tesoro> const& v, int n, int T){
    
    
    // Caso base: matriz inicializada a 0 por tanto m[0][j] = 0 ; m[i][0] = 0
    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= T; ++j){
            if(3*v[i - 1].profundidad > j) matriz[i][j] = matriz[i - 1][j];
            else
                matriz[i][j] = max(matriz[i - 1][j], matriz[i - 1][j - 3*v[i - 1].profundidad] + v[i - 1].oro); // no cogerlo o cogerlo
        }
    }

}

vector<int> reconstruccion(vector<vector<int>> const& matriz, vector<Tesoro> const& v, int n, int T){
    int i = n;
    int j = T;
    vector<int> res;
    
    if(matriz[n][T] != 0){
        while(i > 0 && j > 0){
            if(matriz[i][j] != matriz[i - 1][j]){
                j -= 3*v[i - 1].profundidad;
                res.push_back(i - 1);
            }
            --i;
        }
    }

    return res;
}
bool resuelveCaso(){
    int T, n; cin >> T >> n;

    if(!cin) return false;

    vector<Tesoro> v(n);
    vector<vector<int>> matriz(n + 1, vector<int>(T + 1, 0));
    for(auto &i: v) cin >> i.profundidad >> i.oro;

    cazatesoros(matriz, v, n, T);

    vector<int> z = reconstruccion(matriz, v, n, T);

    cout << matriz[n][T] << '\n'; // oro total obtenido
    cout << z.size() << '\n'; // numero de cofres rescatados a la superficie
    // Caracteristicas de cada cofre en orden inverso (orden en el que se han encontrado los cofres)
    for(int i = z.size() - 1; i >= 0; --i){
        cout << v[z[i]].profundidad << " " << v[z[i]].oro << '\n';
    }
    cout << "---\n";

    return true;
}

int main(){

    while(resuelveCaso());

    return 0;
}