// OK 
#include <climits>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>

using namespace std;
const int INF = INT_MAX; 


int bfs_cyrcle(int st, const vector<vector<int> >& graph) {
    int n = graph.size() - 1;
    vector<int> dist(n + 1, -1), parent(n + 1, -1);
    int shorti = INF;
    
    queue<int> q;
    dist[st] = 0;
    q.push(st);
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        for (int v : graph[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                parent[v] = u;
                q.push(v);
            } else if (parent[u] != v) {
                shorti = min(shorti, dist[u] + dist[v] + 1);
            }
        }
    }
    
    return shorti;
}

int coutAnwer(int n , const vector<vector<int> >& graph) {
    int ans = INF;
    
    for (int i = 1; i <= n; ++i) {
        ans = min(ans, bfs_cyrcle(i, graph));
    }

    if (ans == INF) {
        return -1;
    } 
    return ans;

}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n, m;  cin >> n >> m;
    
    vector< vector< int > > graph(n + 1);
    for (int i = 0; i < m; ++i) {
        int a, b;  cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    std::cout << coutAnwer(n, graph) << std::endl;
    


    return 0;
}


// // OK 
// #include <iostream>
// #include <vector>
// #include <queue>
// #include <algorithm>
// #include <limits>

// using namespace std;
// const int INF = numeric_limits<int>::max();

// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);

//     int n, m; cin >> n >> m;

//     vector<vector<int> > graph(n + 1);
//     for (int i = 0; i < m; ++i) {
//         int a, b; cin >> a >> b;
//         graph[a].push_back(b);
//         graph[b].push_back(a);
//     }

//     int ans = INF;

    
//     for (int st = 1; st <= n; ++st) {
//         vector<int> dist(n + 1, -1) ,  parent(n + 1, -1);

//         queue<int> q;
//         dist[st] = 0;
//         q.push(st);

//         while (!q.empty()) {
//             int u = q.front();
//             q.pop();

//             for (int v : graph[u]) {
//                 if (dist[v] == -1) {
                    
//                     dist[v] = dist[u] + 1;
//                     parent[v] = u;
//                     q.push(v);
//                 } else if (parent[u] != v) {
//                     ans = min(ans, dist[u] + dist[v] + 1);
//                 }
//             }
//         }
//     }

//     if (ans == INF) {
//         cout << -1 << '\n';
//     } else {
//         cout << ans << '\n';
//     }

//     return 0;
// }
