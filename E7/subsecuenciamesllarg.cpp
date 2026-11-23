#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void subsecuencia(vector<vector<int>> &subsec, string const& X, string const& Y, int n, int m){

    // Todas las celdas son necesarias asi que pasamos por cada uan de las celdas.
    // Caso base: i == 0 || j == 0 -> subsec[i][j] = 0;
    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= m; ++j){
            if(X[i - 1] == Y[j - 1]) subsec[i][j] = subsec[i - 1][j - 1] + 1;
            else subsec[i][j] = max(subsec[i - 1][j], subsec[i][j - 1]);
        }
    }

}

string reconstruccion(vector<vector<int>> const& subsec, string const& X, string const& Y, int n, int m){


    int i = n;
    int j = m;
    string s;
    if(subsec[i][j] != 0){
        while(i > 0 && j > 0){
            if(X[i - 1] == Y[j - 1]){
                s.push_back(X[i - 1]);
                i--; j--;
            }
            else if(subsec[i - 1][j] > subsec[i][j - 1]) --i;
            else --j;
        }
        reverse(s.begin(), s.end()); // coste de O(n + m)
    }
    return s;
}
bool resuelveCaso(){

    string X, Y; cin >> X >> Y;
    if(!cin) return false;

    int n = X.size(), m = Y.size();
    vector<vector<int>> subsec(n + 1, vector<int>(m + 1, 0));
    subsecuencia(subsec, X, Y, n, m);
    cout << subsec[n][m] << endl;
    cout << reconstruccion(subsec, X, Y, n, m) << endl;
    // for(int i = 0; i <= n; ++i){
    //     for(int j = 0; j <= m; ++j){
    //         cout << subsec[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    return true;
}

int main(){
    while(resuelveCaso());
    return 0;
}