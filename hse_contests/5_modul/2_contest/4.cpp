
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
    long long  c ; 
    int next; 
}; 
vector<Edge> edges  ;
vector<int> head ; 
vector<int> ptr ;
vector<int> ost_head;
vector<Edge> ost_edges ;
vector<int> edge_id ; // чтобы хранить индексы начальных ребер 


void add(int a , int b , int c ) {
    edges.push_back({a,b,0,c , head[a]}) ; 
    head[a] = edges.size() - 1; 
    edges.push_back({b,a , 0 , c , head[b]}) ; 
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

long long get_cut_capacity(vector<int>& cut_edges) {
    long long sum = 0;
    for (int edge_num : cut_edges) {
        int idx = edge_id[edge_num - 1]; // переходим к индексу в edges
        sum += edges[idx].c; // исходная пропускная способность
    }
    return sum;
}

vector<bool>used ; 
void dfs2(int v ){
    if (used[v]) return ; 
    used[v] = true; 
    for (int u = ost_head[v] ; u != -1 ; u = ost_edges[u].next) {
        if (ost_edges[u].c > 0) 
            dfs2(ost_edges[u].b) ; 
    }
}

int main() {
    cin >> N >> M ; 
    head.resize(N,-1); 
    level.resize(N, -1) ;
    ptr.resize(N) ;
    used.resize(N) ;
    ost_head.resize(N , -1) ;
    
    

    for (int i =0 ; i < M; i++) {
        int a ,b ,c ; cin >> a >> b >> c ; a--; b-- ; 
        edge_id.push_back(edges.size()) ;
        add(a,b,c) ; 
    }
    dinic();

    // остальные сеть 
    for (auto el : edges) {
        if (el.c - el.f > 0 ) {
            ost_edges.push_back({el.a , el.b , 0 , el.c - el.f , ost_head[el.a]}) ;
            ost_head[el.a] = ost_edges.size() - 1;
        }
        if (el.f > 0 ) {
            ost_edges.push_back({el.b , el.a , 0 , el.f  , ost_head[el.b]}) ;
            ost_head[el.b] = ost_edges.size() - 1;

        }
    }

    dfs2(0) ; 


    vector<int> result ; // по идее - хотел , чтобы он находил ребра разреза 


    for (int i = 0 ; i < M ; i++) {
        int edge_idx = edge_id[i] ;
        Edge &e = edges[edge_idx] ; 
        if ((used[e.a] && !used[e.b]) || (!used[e.a] && used[e.b])) {
            result.push_back(i+1) ;
        }
    }

    std::cout << result.size() << " ";
    std::cout << get_cut_capacity(result) << "\n";
    for (auto el : result) {
        std::cout << el  << " ";
    }
    return 0;
}
