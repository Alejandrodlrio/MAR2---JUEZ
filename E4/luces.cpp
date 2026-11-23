#include <iostream>
#include <vector>
using namespace std;


struct Led {
    int cost;
    int pot;
};


Led bombillas(vector<vector<int>> & dp, vector<Led> const& leds, int n, int pmin, int pmax){
    dp[0][0] = 0;

    for(int i = 1; i <= n; ++i){
        dp[i][0] = 0;
        for(int j = 1; j <= pmax; ++j){
            if(leds[i - 1].pot > j) dp[i][j] = dp[i - 1][j];
            else 
                dp[i][j] = min(dp[i - 1][j], dp[i][j - leds[i - 1].pot] + leds[i - 1].cost);
        }
    }

    int minCost = dp[n][pmin];
    int pot = pmin;
    for(int j = pmin + 1; j <= pmax; ++j){
        if(dp[n][j] < minCost){
            minCost = dp[n][j];
            pot = j;
        }
    }

    return {minCost, pot};

}



bool resuelveCaso(){
    int n, pmin, pmax; cin >> n >> pmax >> pmin;
    if(!cin) return false;

    vector<Led> leds(n);

    for(auto &i: leds) cin >> i.pot;
    for(auto &i: leds) cin >> i.cost;


    vector<vector<int>> dp(n + 1, vector<int>(pmax + 1, 999)); 

    Led res = bombillas(dp, leds, n, pmin, pmax);
    if(res.cost != 999){ 
        cout << res.cost << " " << res.pot;

    }
    else cout << "IMPOSIBLE" ;
    cout << "\n";

    return true;
}







int main(){
    while(resuelveCaso());
    return 0;
}