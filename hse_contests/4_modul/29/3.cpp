#include <iostream>
#include <vector>
#include <cmath>
using namespace std;


int LOG; 

void dfs(int u, int parent, long long d, vector<long long> &dist,  vector<int> &depth, vector<vector<int> >  &up, const vector<vector<pair<int, long long> > > &graph) {
    dist[u] = d;
    depth[u] = (u == parent) ? 0 : depth[parent] + 1;
    up[u][0] =parent;

    for (int i= 1; i <= LOG; ++i) {
        up[u][ i] = up [up[u ][ i-1]][i-1] ;
    }

    for (const auto&  edge : graph[u]) {
        int v = edge.first;
        long long w = edge.second;
        
        if (v != parent) {
            dfs(v, u, d + w, dist, depth, up, graph);
        }

    }

}

int lca(int u, int v, vector<vector<int> > &up , vector<int> &depth) {
    if (depth[u] < depth[v]) swap(u, v);

    for (int k = LOG; k >= 0 ;  --k)  {
        if (depth[u] - (1 <<  k) >= depth[v]) {
            u = up[u][k ];
        }
    }
    
    if (u == v )  return  u;
    for (int k =  LOG; k >= 0; --k) {
        if (up[u][k] != up[v][k]) {
            u = up[u][k];
            v = up[v][k]; 
        }
    }
    
    return up[u][0 ];
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n; cin >> n;
    LOG = ceil(log2(n));
    vector<vector<pair<int, long long> > > graph(n); 
    vector<long long> dist(n); 
    vector<vector<int> > up(n , vector<int>(LOG +1)); 
    vector<int> depth(n); 
    
    
    for (int i = 0; i < n - 1; ++i) {
        int u, v; long long w;cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }
    depth[0] = -1;
    
    dfs(0, 0, 0, dist, depth, up, graph);
    
    int m; cin >> m;
    while (m--) {
        int u, v; cin >> u >> v;
        int a = lca(u, v , up , depth);
        long long distance = dist[u] + dist[v] - 2 * dist[a]; cout << distance << '\n';
    }
    
    return 0;
}