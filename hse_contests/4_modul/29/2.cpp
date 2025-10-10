#include <iostream>
#include <vector>
#include <cmath>
using namespace std;



int LOG;

void dfs(int v, int p, const vector<vector<int> >& vec  , vector<vector<int> > &up , vector<int> &depth) {
    up[v][0] = p;
    for (int k = 1; k <= LOG; ++k) {
        up[v][k] = up[up[v][k-1]][k-1];
    }
    for (int u : vec[v]) {
        if (u != p) {
            depth[u] = depth[v] + 1;
            dfs(u, v, vec , up  , depth);
        }
    }
}

int lca(int u, int v , vector<vector<int> > &up  ,vector<int> &depth) {
    if (depth[u] < depth[v]) swap(u, v);

    for (int k = LOG; k >= 0; --k) {
        if (depth[u] - (1 << k) >= depth[v]) {
            u = up[u][k];
        }
    }
    
    if (u == v) return u;
    for (int k = LOG; k >= 0; --k) {
        if (up[u][k] != up[v][k]) {
            u = up[u][k];
            v = up[v][k]; 
        }
    }
    
    return up[u][0];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    LOG = ceil(log2(n));

    vector<vector<int> > up(n+1 , vector<int>(LOG+1));  vector<int> depth(n+1); 
    
    
    vector<vector<int> > vec(n + 1);
    for (int i = 2; i <= n; ++i) {
        int x; cin >> x;
        vec[x].push_back(i); vec[i].push_back(x);
    }
    
    
    dfs(1, 1, vec , up , depth);  
    
    int m; cin >> m;
    while (m--) {
        int x, y; cin >> x >> y;
        cout << lca(x, y , up ,depth) << '\n';
    }
    
    return 0;
}