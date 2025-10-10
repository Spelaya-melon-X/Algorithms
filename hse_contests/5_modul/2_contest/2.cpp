
#include <ios>
#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include <iomanip>
using namespace std;
int N , M ;
const int INF = 1000000000; 

struct Edge{
    int a , b   ; 
    long long f ; 
    int c ; 
    int next; 
}; 
vector<Edge> edges  ;
vector<int> head ; 
vector<int> ptr ;


void add(int a , int b , int c ) {
    edges.push_back({a,b,0,c , head[a]}) ; 
    head[a] = edges.size() - 1; 
    edges.push_back({b,a , 0 , 0 , head[b]}) ; 
    head[b] = edges.size() - 1; 
}

vector<int> level ; 
bool bfs( ) {
    fill(level.begin(), level.end(), -1);
    level[0] = 0 ; 
    queue<int> queue;
    queue.push(0)  ; 
    while (!queue.empty()) {
        int v = queue.front() ; queue.pop() ; 
        for (int u = head[v] ; u != -1 ; u = edges[u].next) {
            int to = edges[u].b ; 
            if (level[to] == - 1 && edges[u].f < edges[u].c) {
                level[to] = level[v] + 1; 
                queue.push(to) ; 
            }
        }
    }
    return level[N-1] != -1; 
}


long long  dfs(int v , int flow) {
    if (v == N-1) return flow ; 

    long long  total_pushed = 0 ; 
    for (int &u = ptr[v] ; u != -1 ; u = edges[u].next) {
        int to = edges[u].b ; 
        if ((level[to] == level[v] + 1) && edges[u].f < edges[u].c) {
            long long  res = dfs(to ,min (flow - total_pushed ,  (long long) (edges[u].c - edges[u].f))) ; 
            if (res) {
                edges[u].f += res; 
                edges[u^1].f -= res; 
                total_pushed += res; 
                if (total_pushed == flow ) {
                    break; 
                }

            }
        }
    }
    return total_pushed ; 
}


long long dinic() {
    long long  flow = 0 ; 
    while(bfs()) {
        for (int i = 0; i < N; i++) {
            ptr[i] = head[i];
        }

        flow += dfs(0 , INF); 
    }
    return flow; 
}

int main() {
    cin >> N >> M ; 
    head.resize(N,-1); 
    level.resize(N, -1) ;
    ptr.resize(N) ;
    vector<int> edge_id ;
    


    for (int i =0 ; i < M; i++) {
        int a ,b ,c ; cin >> a >> b >> c ; a--; b-- ; 
        edge_id.push_back(edges.size()) ;
        add(a,b,c) ; 
    }

    long long max_flow = dinic();
    cout << fixed << setprecision(1) << (double)max_flow << '\n';
    for (int i = 0; i < M; i++) {
        long long flow_on_edge = edges[edge_id[i]].f;
        cout << fixed << setprecision(1) << (double)flow_on_edge << '\n';
    }
    


    return 0;
}