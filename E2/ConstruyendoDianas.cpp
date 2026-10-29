#include <iostream>
#include <vector>
#include <fstream>
using namespace std;



int dianas(vector<vector<int>> &matriz, vector<int> const& v, int n, int S){


    matriz[0][0] = 0;
    for(int i = 1; i <= n; ++i){
        matriz[i][0] = 0;
        for(int j = 1; j <= S; ++j){
            if(v[i - 1] > j) matriz[i][j] = matriz[i - 1][j];
            else
                matriz[i][j] = min(matriz[i - 1][j], matriz[i][j - v[i - 1]] + 1);
        }
    }


    return matriz[n][S];
}

// siempre habrá solucion si llamamos a esta funcion ya que filtramos en main
vector<int> reconstruccion(vector<vector<int>> const&matriz, vector<int> const& v, int n, int S){
    vector<int> z;
    int i = n;
    int j = S;

    while(j > 0){
        if(v[i - 1] <= j && matriz[i][j] != matriz[i - 1][j]){ // escogimos este valor;
            z.push_back(v[i - 1]);
            j -= v[i - 1];
        }
        else --i;
    }
    return z;
}

bool resuelveCaso(){
    int S, n; cin >> S >> n;

    if(!cin) return false;

    vector<int> v(n);
    
    for(auto &i: v) cin >> i;
    
    vector<vector<int>> matriz(n + 1, vector<int>(S + 1, 999));
    int r = dianas(matriz, v, n, S);

    if(r != 999){
        vector<int> z = reconstruccion(matriz, v, n, S);
        cout << r << ": " ;
        for(auto i: z) cout << i << " ";
    }
    else 
        cout << "Imposible";

    cout << "\n";

    return true;

}

int main()
{
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("./samples-02/1.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (
        resuelveCaso())
        ;
    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}