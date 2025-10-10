#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std; 

bool dfs( int v , vector <vector < int> > &edges , int &cycle_begin , int &cycle_end, vector <int> &parents, vector <int> &color){
        color[v] = 1; 
        for (auto u : edges[v]){
            if ( color[u] == 0 ){
                parents[u] = v; 
                if (dfs( u , edges, cycle_begin , cycle_end , parents , color)){
                    return true; 
                }

            } else if (color[u] == 1 ) {
                cycle_begin = u ; 
                cycle_end = v; 
                return true; 

            }
        }
        color[v] = 2 ; 
        return false; 


}

void find_cycle( int  n , vector < vector <int> > &edges){
    vector <int> parents(n , -1) ;
    vector <int> color(n , 0); 
    int cycle_begin = -1 , cycle_end = -1; 

    for (int i = 0 ; i < n; i++) {
        if (color[i] == 0) {
            if (dfs( i , edges , cycle_begin , cycle_end , parents , color)) {
                break;
            }
        }
    }

    if (cycle_begin == -1) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
        vector<int> cycle;

        for (int v = cycle_end; v != cycle_begin; v = parents[v]) {
            cycle.push_back(v);
        }
        cycle.push_back(cycle_begin); 
        reverse(cycle.begin(), cycle.end()); 
        for (int v : cycle) {
            cout << v + 1 << " "; 
        }
        cout << endl; 
    }

}


int main() {
    int n , m ; cin >> n >> m ; 

    vector <vector < int > > edges(n) ; 

    for ( int i = 0;i < m ;i++){
        int f , t ; cin >> f >> t ; 
        f--; t--; 
        edges[f].push_back(t) ; 
    }
    find_cycle(n , edges); 



    // for ( int i = 0 ;i < n ;i++){
    //     for ( auto el : edges[i]){
    //         cout << i << " " << el << endl; 
    //     }
    // }
    return 0;
}