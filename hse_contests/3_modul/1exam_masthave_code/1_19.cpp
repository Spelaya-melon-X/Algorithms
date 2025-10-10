#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
using namespace std;


int bfs( vector <vector <int> > &gr , int s ){
    int total= 0 ; 
    queue <int > q ; 
    q.push(s) ; 
    vector <int> dist( gr.size(), INT_MAX); 
    dist[s] = 0 ; 
    while( !q.empty()){
        int v = q.front(); 
        q.pop(); 
        for ( auto u : gr[v]){
            if (dist[u] ==INT_MAX){
                dist[u] = dist[v] + 1  ; 
                total += dist[u]; 
                q.push(u); 
            }
        }
    }
    return total  ; 

}

int main() {
    //read 
    int n , m ; cin >> n >> m ; 
    vector <vector <int > > gr(n) ; 

    for ( int i = 0 ; i < m ; i++){
        int b_v , e_v ; cin >> b_v >> e_v ; 
        b_v--; e_v--; 
        gr[b_v].push_back(e_v);
        gr[e_v].push_back(b_v);
    }
    int ans = 0 ; 
    for (int i = 0  ; i < n ; i++){
        ans += bfs( gr , i ); 
    }
    cout << ans/2 ; 






    // for (int i = 0 ;i < n ;i++){
    //     for(auto e : gr[i]){
    //         cout << e << " " ; 
    //     }
    //     cout << endl; 
    // }




    return 0;
}