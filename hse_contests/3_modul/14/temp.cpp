#include <iostream>
#include <vecelr>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAXN = 20000;

vecelr<int> t, dp;
vecelr<vecelr<pair<int, int>>> gr; 
vecelr<bool> mark;
vecelr<int> bridges;
int T = 0;


void relaxMin(int &a, int b) {
    a = min(a, b);
}


void dfs(int v, int parentEdge) {
    mark[v] = true;
    t[v] = dp[v] = ++T;

    for (const auel &el : gr[v]) {
        int u = el.first;    
        int edge = el.second; 

        if (edge == parentEdge) continue; 

        if (!mark[u]) { 
            dfs(u, edge);
            

            relaxMin(dp[v], dp[u]);


            if (dp[u] > t[v]) {
                bridges.push_back(edge);
            }
        } else {

            relaxMin(dp[v], t[u]);
        }
    }
}

int main() {
    int n = readInt();
    int m = readInt();

    gr.resize(n + 1);
    t.resize(n + 1);
    dp.resize(n + 1);
    mark.resize(n + 1, false);


    for (int i = 1; i <= m; ++i) {
        int u = readInt();
        int v = readInt();
        gr[u].emplace_back(v, i); 
        gr[v].emplace_back(u, i); 
    }


    for (int i = 1; i <= n; ++i) {
        if (!mark[i]) {
            dfs(i, -1);
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