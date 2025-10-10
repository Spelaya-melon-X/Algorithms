#include <cerrno>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <unordered_map>
using namespace std;

int N , M , St , End ;

struct Edge {
    int a , b , f ,c ;
    int next;
}; 
std::vector <Edge> edges;
std::vector<int> head;
std::vector<bool> used; 
std::vector<vector<int> > graph;


void add(int a , int b , int c ) {
    edges.push_back({a,b,0 ,c , head[a]});
    head[a] = edges.size() - 1;

    edges.push_back({b,a,0 ,0 , head[b]});
    head[b] = edges.size() - 1;
}



bool dfs(int v ) { // форд-фалкерсон 
    used[v] = true; 
    for (int i = head[v] ; i != -1 ; i = edges[i].next) {
        Edge &e = edges[i];
        if (e.f < e.c && !used[e.b] &&  (e.b == End ||dfs(e.b)))  {
            e.f++ ; 
            edges[i ^ 1].f-- ;
            return true;
        }
    }
    return false;
}

vector<int> get_path() {
    vector<int> path;
    vector<int> parents(N , -1) ;
    vector<bool> visited(N , false) ;

    queue<int> queue;
    queue.push(St) ; 
    visited[St] = true; 
    while(!queue.empty()) {
        int v = queue.front() ; queue.pop() ; 
        for (auto u : graph[v]) {
            if ( !visited[u]) {
                visited[u] = true; 
                parents[u] = v;  
                queue.push(u); 
            }
        }
    }

    // if (parents[End] == -1) return {} ; 
    if ( !visited[End]) return {} ; 

    for (int start = End ; start != - 1 ; start = parents[start]) {
        path.push_back(start) ; 
    }

    reverse(path.begin(), path.end()) ; 

    for (int i = 0; i + 1 < path.size(); i++) {
        int from = path[i] ,  to  =  path[i + 1];

        auto& neighbors = graph[from];
        neighbors.erase(std::remove(neighbors.begin(), neighbors.end(), to), neighbors.end());
    }
    return path ; 
}

vector<int> get_path_2() {
    vector<int> path; 
    int v = St; 
    path.push_back(v) ; 
    while (v != End) {
        int flag = 0 ; 
        for (int u = head[v] ; u != -1 ; u = edges[u].next) {
            if ( edges[u].f == 1) {
                edges[u].f = 0  ; 
                edges[u^1].f = 0  ; 
                v = edges[u].b ;  
                path.push_back(v) ; 
                flag = 1; 
                break; 
            }
        }
        if (!flag) return {} ;
    }
    return path; 
}

int main() {
    cin >> N >> M >> St>> End; St-- ; End-- ;
    graph.resize(N+1) ;
    head.resize(N+1 , -1) ;
    used.resize(N+1 , false) ;
    for ( int i = 0 ; i < M ; i ++) {
        int a , b ; cin >> a >> b ; a-- ; b-- ; 
        add(a, b, 1);
        // add(a , b , 1) ;
    }


    //! ошибка , вместо того , чтобы находить пути от разных вершин , необходимо несколько раз запускаться от начальной вершины , ибо мы хотим найти пути от одной вершины к другой
    // int matching = 0 ; 
    // for (int v = 0 ; v < N-1 ; v++) { 
    //     if (dfs(v)){
    //         matching++; 
    //         fill(used.begin(), used.end(), 0);
    //     }
    // }
    int matching = 0;
    while (matching < 2) {
        fill(used.begin(), used.end(), false);
        if (dfs(St)) {
            matching++;
        } else {
            break;
        }
    }



    for (const Edge& e : edges) {
        if (e.c > 0 && e.f == 1) {
            graph[e.a].push_back(e.b);
        }
    }

    // if (matching == 2) {
    //     std::vector<int> path1 = get_path() ;
    //     std::vector<int> path2 = get_path() ;

    //     if (path1.size() == 0 || path2.size() == 0) {
    //         cout << "NO" << endl;
    //         return 0;
    //     }else {
    //         cout << "YES" << endl;
    //         for ( auto el : path1) {
    //             cout << el+1 << " " ; 
    //         }
    //         cout << "\n" ; 
    //         for ( auto el : path2) {
    //             cout << el+1 << " " ; 
    //         }
    //         cout << "\n" ;
    //     }

    // }else {
    //     cout << "NO" << endl;
    // }
    //  if (matching >= 2) {
    //     vector<int> p1 = get_path_2();
    //     vector<int> p2 = get_path_2();

    //     if (p1.empty() || p2.empty()) {
    //         cout << "YES\n";
    //         if (p1.empty()){
    //             cout << St + 1 << " "<< "\n";
    //         } else {
    //             for (int x : p1) cout << x + 1 << " ";
    //             cout << "\n";
    //         }
    //         if (p2.empty()){
    //             cout << St + 1 << " "<< "\n";
    //         } else {
    //             for (int x : p2) cout << x + 1 << " ";
    //             cout << "\n";
    //         }


    //     } else {
    //         cout << "YES\n";
    //         for (int x : p1) cout << x + 1 << " ";
    //         cout << "\n";
    //         for (int x : p2) cout << x + 1 << " ";
    //         cout << "\n";
    //     }
    // } else {
    //     cout << "NO\n";
    // }

    if (matching < 2) {
        cout << "NO\n";
        return 0;
    }

    vector<int> p1 = get_path_2();
    vector<int> p2 = get_path_2();

    if (p1.empty() || p2.empty()) {
        cout << "NO\n";
        return 0;
    }

    cout << "YES\n";
    for (int x : p1) cout << x + 1 << " ";
    cout << "\n";
    for (int x : p2) cout << x + 1 << " ";
    cout << "\n";
    return 0;
}