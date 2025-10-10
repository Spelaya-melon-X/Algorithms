#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

struct Edge {
    int from, to, c, co, f;
};
vector<Edge> edges;
vector<vector<int> > graph;


void bellman_ford(int n, vector<long long> &dist, vector<int> &parent, vector<int> &parent_edge) {
    bool updated = true;
    for (int i = 0; i < n && updated; i++) {
        updated = false;
        for (int u = 0; u < n; u++) {
            if (dist[u] == LLONG_MAX) continue;
            for (int idx : graph[u]) {
                Edge& e = edges[idx];
                if (e.c > e.f && dist[e.to] > dist[u] + e.co) {
                    dist[e.to] = dist[u] + e.co;
                    parent[e.to] = u;
                    parent_edge[e.to] = idx;
                    updated = true;
                }
            }
        }
    }
}

void add(int a, int b, int c, int d ) {
    graph[a].push_back(edges.size());
    edges.push_back({a, b, c, d, 0});
    
    graph[b].push_back(edges.size());
    edges.push_back({b, a, 0, -d, 0});
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m; cin >> n >> m;
    graph.resize(n);
    
    
    for (int i = 0; i < m; i++) {
        int u, v, cap, co; cin >> u >> v >> cap >> co; u--; v--;
        add(u, v, cap, co);
        

    }
    
    long long total_co = 0;
    int source = 0, sink = n - 1;
    
    while (true) {
        vector<long long> dist(n, LLONG_MAX);
        vector<int> parent(n, -1);
        vector<int> parent_edge(n, -1);
        
        dist[source] = 0;
        
        bellman_ford(n, dist, parent, parent_edge);
        
        if (dist[sink] == LLONG_MAX) {
            break;
        }
        
        int f = INT_MAX;
        for (int v = sink; v != source; v = parent[v]) {
            int idx = parent_edge[v];
            f = min(f, edges[idx].c - edges[idx].f);
        }
        
        for (int v = sink; v != source; v = parent[v]) {
            int idx = parent_edge[v];
            edges[idx].f += f;
            edges[idx ^ 1].f -= f;
            total_co += (long long)f * edges[idx].co;
        }
    }
    
    cout << total_co << endl;
    
    return 0;
}