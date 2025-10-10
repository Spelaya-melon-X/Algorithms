
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
    cin >> N  ; 


    vector<int> count_win(N) ; 
    vector<int> count_games(N); 
    vector<vector<int> > turnir(N, vector<int>(N)) ;

    for (int i = 0; i < N; i++) {
        cin >> count_win[i]; 
    }

    for (int i = 0 ; i < N ; i++) {
        cin >> count_games[i];
    }
    for (int i = 0 ; i < N ; i++) {
        for (int j = 0 ; j < N; j++) {
            int x ; cin>> x;
            turnir[i][j] = x; 
        }
    }

    int max_wins1 = count_win[0] + count_games[0];

    for (int i = 1 ;i < N ;i++) {
        if (count_win[i] > max_wins1) {
            std::cout << "NO" << '\n';
            return 0 ; 
        }
    }

    int count_turnirs_with_command = 0 ; 
    for (int i = 1 ; i < N; i++) {
        for (int j = i + 1 ; j < N ; j++) {
            count_turnirs_with_command += turnir[i][j] ;
        }
    }

    // int games_count = (N-1) * ((N-2)/2) ; 
    int games_count = (N-1) * (N-2) / 2;
    int total_ver = 1 + games_count + (N-1) +1; 

    
    head.resize(total_ver,-1); 
    level.resize(total_ver, -1) ;
    ptr.resize(total_ver , 0) ; 
    vector<int> edge_id ;

    
    int vertex_counter = 1; 

    
    vector<vector<int> > game_vertex(N, vector<int>(N, -1));
    for (int i = 1; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            game_vertex[i][j] = vertex_counter++;
        }
    }

    
    int team_start = games_count + 1;
    vector<int> team_vertex(N, -1);
    for (int i = 1; i < N; i++) {
        team_vertex[i] = team_start + (i - 1);
    }

    int sink = games_count + N; 

    

    
    for (int i = 1; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            int game_v = game_vertex[i][j];
            add(0, game_v, turnir[i][j]); 
        }
    }

    
    for (int i = 1; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            int game_v = game_vertex[i][j];
            add(game_v, team_vertex[i], INF); 
            add(game_v, team_vertex[j], INF); 
        }
    }

    
    for (int i = 1; i < N; i++) {
        int capacity = max_wins1 - count_win[i];
        if (capacity < 0) capacity = 0; 
        add(team_vertex[i], sink, capacity);
    }

    
    int old_N = N;
    N = sink + 1; 

    
    head.resize(N, -1);
    level.resize(N, -1);
    ptr.resize(N, 0);

    long long max_flow = dinic();
    if (max_flow == count_turnirs_with_command) 
        cout << "YES" << endl;
    else 
        cout << "NO" << endl;
        
    return 0;
}