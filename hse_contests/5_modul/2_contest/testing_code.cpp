#include <climits>
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue> 
#include <set> 
using namespace std;


int N =100000; 
vector<bool> used(N) ;
vector<vector<int> > graph(N) ; 

bool dfs (int v , int u) {
    if (v == u) return true;
    if (used[v]) return false ; 
    used[v] = true; 
    for (auto v_1 : graph[v]) {
        if (dfs(v_1 , u)) {
            return true; 
        }
    }
    return false; 
}



bool bfs( int st , int end) {
    std::queue<int> queue ; 
    if ( st == end ) return true;
    if (used[st]) return false; 
    used[st] = true; 
    queue.push(st) ; 
    while(!queue.empty()) {
        int v = queue.front()  ; queue.pop() ; // ! not queue.back() --> queue.fron()
        for (auto u : graph[v]) {
            //! bfs работает итеративно , ане рекусривно , поэтмоу нужно вызвать bfs , а просто добавлять эти вершины в очередь 
            if ( u == end ) return true; 
            // ! также так как это не рекусривный алгоритм , то мы просто помечаем , какие вершинки , мы посетили ,и записываем в queue для дальнейшего просмотра их внутренностпей 
            if (!used[u]) {
                used[u] = true; 
                queue.push(u) ; 
            }
        }
    }
    return false; 
}


vector<int> dist(N , INT_MAX) ; 
vector < vector < pair<int,int> > > g (N); // for Djistra 


void Djistra(int st ) {
    dist[st] = 0 ;  
    // or priority_queue
    set < pair<int,int> > q ;  // pair(dist[st] , st) - чтобы был sort по dist[st]
    q.insert(make_pair(dist[st] , st)) ;  // ? 
    while (!q.empty()) {
        int v = (q.begin())->second  ; 
        int d = (q.begin())->first; 
        q.erase(q.begin()) ; 

        if (d != dist[v]) continue; // устаревшая версия — пропускаем

        for (auto edge : g[v]) {
            int to = edge.first ; 
            int weight = edge.second ; 
            if (dist[v] + weight < dist[to] ) { //! тут вершина to , а не v!
                dist[to] = dist[v] + weight ; 
                q.insert({dist[to] , to}) ; 
            }

        }
        
    }

}



int main() {
    return 0;
}