#include <iostream>
#include <vector>
#include <algorithm>
#include "optimization.h"

using namespace std;

vector<int> bridges;
int T = 0;

void relaxMin(int &a,int b) { a = min(a, b); }

void dfs(int v, int parentEdge , vector <bool> &mark , vector <int> &t , vector <int> &dp , vector<vector<pair<int, int>>> &gr ) {
    mark[v] =true;
    t[v] = dp[v] =++T;

    for (auto el : gr[v]) {
        int u = el.first , edge = el.second; 
        if (edge == parentEdge) continue; 

        if (!mark[u]) { 
            dfs(u, edge, mark , t  , dp , gr);
            relaxMin(dp[v], dp[u]);
            if (dp[u] >t[v]) {
                bridges.push_back(edge );
            }
        } else{
            relaxMin(dp[v], t[u]);
        }
    }
}

int main() {
    int n = readInt();
    int m = readInt();
    vector<int> t(n+1), dp(n+1);
    vector<vector<pair<int, int>>> gr(n+1); 
    vector<bool> mark(n+1 , false);

    for (int i = 1; i <= m; ++i) {
        int u = readInt();
        int v = readInt();
        gr[u].emplace_back(v, i); 
        gr[v].emplace_back(u, i); 
    }
    for (int i = 1; i <= n; ++i) {
        if (!mark[i]) {
            dfs(i, -1 , mark , t , dp , gr);
        }
    }

    sort(bridges.begin(), bridges.end());   


    cout << bridges.size() << endl;
    for (int bridge : bridges) {
        cout << bridge << " ";
    }
    cout << endl;

    return 0;
}