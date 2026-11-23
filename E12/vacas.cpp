#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

int vacasPensantes(vector<vector<int>> &comida, vector<int> const& v, int n){

    // int N = n - 1;
    // caso base:
    for(int i = 0; i < n; ++i){
        comida[i][i] = v[i];
    }
    // Caso recursivo
    for(int len = 2; len <= n; ++len){
        for(int i = 0; i + len <= n; ++i){
            int j = len + i - 1;
            // No damos nada por sentado, comparamos ambos lados igualmente:
            int ladoIzq = 0;
            int ladoDcho = 0;
            
            // cojo lado v[i]
            if(v[i + 1] > v[j])  ladoIzq = v[i] + (i + 2 > j ? 0 : comida[i + 2][j]); // devoradora se come v[i + 1]
            else ladoIzq = v[i] + (i + 1 > j - 1 ? 0 : comida[i + 1][j - 1]); // devoradora se come v[j].
            
            // cojo lado v[j]
            if(v[i] > v[j - 1]) ladoDcho = v[j] + (j - 1 < i + 1 ? 0 :  comida[i + 1][j - 1]); // Devoradora se come v[i];
            else ladoDcho = v[j] + (i > j - 2 ? 0 : comida[i][j - 2]); // devoradora se come v[j - 1]


            comida[i][j] = max(ladoIzq, ladoDcho);
        }
    }


    return comida[0][n - 1];
}

bool resuelveCaso(){
    int n; cin >> n;
    if(n == 0) return false;


    vector<int> cubos(n);
    for(auto &i: cubos) cin >> i;

    vector<vector<int>> comida(n, vector<int>(n, 0));

    int res = vacasPensantes(comida, cubos, n);
    cout << res << endl;

    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            cout << comida[i][j] << " ";
        }
        cout << endl;
    }


    return true;
}

int main(){
    while(resuelveCaso());
    return 0;
}