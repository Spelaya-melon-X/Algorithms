


#include <iostream>
#include <vector>
#include <set>
#include <climits> 
#include "optimization.h"
using namespace std;

int djestra(int s , int t , vector <vector <pair<int , int> > > &gr){
    vector <int> dist(gr.size() ,INT_MAX); 
    set< pair<int, int> > se ; 
    se.insert(make_pair(0 , s)); 
    dist[s] = 0 ;

    while (!se.empty()){
        int u = se.begin() -> second ; 
        se.erase(se.begin()); 

        for ( const auto &x : gr[u] ){
            int v = x.first ; 
            int we = x.second ; 
            if (dist[v] > dist[u] + we   ) {
                se.erase(make_pair(dist[u], u)); 
                dist[v] = dist[u] + we ;
                se.insert(make_pair(dist[v] , v)); 
            }
        }
    }
    if (dist[t] == INT_MAX){
        return -1; 
    } else {
        return dist[t]; 
    }
}

int main() {
    int n = readInt(); 
    int m = readInt(); 
    int s = readInt(); s--; 
    int t = readInt(); t--; 
    vector <vector <pair <int , int > > > gr(n) ;


    for (int i = 0 ; i < m ; i++ ){
        int b = readInt() ; b--; 
        int e = readInt() ; e--; 
        int w = readInt() ; 
        gr[b].emplace_back(make_pair (e,w )); 
        gr[e].emplace_back(make_pair(b , w)); 
    }
    int ans = djestra(s , t , gr); 
    writeInt(ans); 



    return 0;
}