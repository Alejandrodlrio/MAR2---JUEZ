#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

// Diferentes cordeles de longitudes y costes. 
// Matematico: ¿De cuantas formas diferentes podriamos formar la cuerda de un tamaño L?
// Ingeniero: Buscar el numero minimo numero de cordeles para acabar de unirlos lo antes posible
// EconomistA: Lo importante es que la cometa salga lo mas barata posible. (minimizar el coste)

struct cordel {
    int coste;
    int tam;
};

void calculo_cordeles(vector<vector<int>> & mat, vector<vector<int>> & ing, vector<vector<int>> & eco, vector<cordel> const& cordeles, int n, int L){

    // Caso base 1
    mat[0][0] = 1;
    ing[0][0] = 0;
    eco[0][0] = 0;
    for(int i = 1; i <= n; ++i){
        mat[i][0] = 1; // caso base 2
        ing[i][0] = 0; 
        eco[i][0] = 0;
        for(int j = 1; j <= L; ++j){
            if(cordeles[i - 1].tam > j) {
                mat[i][j] = mat[i - 1][j];
                ing[i][j] = ing[i - 1][j];
                eco[i][j] = eco[i - 1][j];
            }
            else {
                mat[i][j] = mat[i - 1][j] + mat[i - 1][j - cordeles[i - 1].tam];
                ing[i][j] = min(ing[i - 1][j], ing[i - 1][j - cordeles[i - 1].tam] + 1);
                eco[i][j] = min(eco[i - 1][j], eco[i - 1][j - cordeles[i - 1].tam] + cordeles[i - 1].coste);
            }
        }
    }
}



bool resuelveCaso(){
    int n, L; cin >> n >> L;
    if(!cin) return false;
    vector<cordel> cordeles(n);
    for(auto &i: cordeles) cin >> i.tam >> i.coste;
 
    vector<vector<int>> mat(n + 1, vector<int>(L + 1, 0));
    vector<vector<int>> ing(n + 1, vector<int>(L + 1, 999));
    vector<vector<int>> eco(n + 1, vector<int>(L + 1, 999));
    calculo_cordeles(mat, ing, eco, cordeles, n, L);
    int res = mat[n][L];
    if(res != 0) {
        cout << "SI " << res << " " << ing[n][L] << " " << eco[n][L];
    }
    else cout << "NO";

    cout << '\n';

    return true;
}

int main()
{
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
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
