#include <iostream>
#include <fstream>
#include <vector>
using namespace std;





// Aproximacion descendente: Recorremos por diagonales.
int aibofobia(vector<vector<int>> & aibo, string const& s, int i, int j){
    if(aibo[i][j] == -1){ // aun no esta calculado adis que seguimos hasta calcular
        if(i > j || i == j) aibo[i][j] = 0;
        else{
            if(s[i] == s[j]) aibo[i][j] = aibofobia(aibo, s, i + 1, j - 1);
            else{
                aibo[i][j] = min(aibofobia(aibo, s, i + 1, j), aibofobia(aibo, s, i , j - 1)) + 1;
            }
        }
    }
    
    return aibo[i][j];
}

string reconstruccion(vector<vector<int>> const& aibo, string const& s, int i, int j){
    if(i > j) return {};
    else if(i == j) return{ s[i] };
    else if(s[i] == s[j]){
        return s[i] + reconstruccion(aibo, s, i + 1, j - 1) + s[j];
    }
    else if(aibo[i][j - 1] <= aibo[i + 1][j]){  // priorizamos las soluciones mas a la izquierda
        return s[j] + reconstruccion(aibo, s, i, j - 1) + s[j];
    }
    else { 
        return s[i] + reconstruccion(aibo, s, i + 1, j) + s[i];
    }

}

bool resuelveCaso(){
    string s; cin >> s;
    if(!cin) return false;

    int n = s.size();
    vector<vector<int>> aibo(n, vector<int>(n, -1));
    cout << aibofobia(aibo, s, 0, n - 1) << endl;
    cout << reconstruccion(aibo, s, 0, n - 1) << endl;
    

    return true;
}

int main(){
    while(resuelveCaso());
    return 0;
}