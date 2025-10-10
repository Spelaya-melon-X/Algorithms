


#include <iostream>
#include <vector>
#include <set>
#include <climits> 
#include "optimization.h"
using namespace std;

/* 
1  инверитиурем все ребра 
2 запустим дейкстру 
3 пройдемся по dist и узнаем что не так для каждой вершини 
*/

int main() {
    int n = readInt(); 
    int s = readInt(); s--; 
    int m = readInt(); 
    vector<vector <pair <int , int> > > gr(n); 


    for (int i = 0 ; i < m ; i++ ){
        int b = readInt() ; b--; // where from 
        int e = readInt() ; e--; // where 
        gr[e].emplace_back(make_pair(b ,1)); // inv
    }

    vector <int> dist(n  ,INT_MAX); 
    set< pair<int, int> > se ; 
    se.insert(make_pair(0 , s)); 
    dist[s] = 0 ;

    while (!se.empty()){
        int u = se.begin() -> second ; 
        se.erase(se.begin()); 

        for ( const auto &x : gr[u] ){
            int v = x.first ; 
            int we = 1; 
            if (dist[v] > dist[u] + we   ) {
                se.erase(make_pair(dist[u], u)); 
                dist[v] = dist[u] + we ;
                se.insert(make_pair(dist[v] , v)); 
            }
        }
    }

    vector <int> ans; 
    for (auto el : dist){
        if (el == INT_MAX){
            ans.push_back(-1); 
        }else {
            ans.push_back(el++); 
        }
    }
    for ( auto el : ans){
        cout << el << " " ; 
    }



    return 0;
}