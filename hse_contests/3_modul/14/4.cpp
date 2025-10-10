
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <stack> 
#include "optimization.h"
#include <set> 
#include <unordered_set> 
/**
 * алгоритм : 
 * 1. реализация дфс для топсорта со стэком yes 
 * 2. реализация дфс по обр , проходя только там где комп = 0 , где комп - вектор yes 
 * 
 * 3. с помщоью топсорта находим порядок обхода yes 
 * 4. обход по обр ребрам  - счечик комп + обход где комп = 0 дфс2 вызываем yes
 * 
 */

using namespace std;

void dfs ( int v , vector <vector <int> > &gr , vector <int> &mark , stack <int> &ed ){
    if (mark[v]) return ; 
    mark[v] = 1; 
    for ( auto u : gr[v]){
        dfs(u , gr , mark , ed ); 
    }
    ed.push(v); 
}

void dfs2 (int v , int cc , vector <vector <int>> &obr_gr , vector <int> &comp ){
    
    comp[v] = cc ; 
    for ( auto u : obr_gr[v]){
        if ( comp[u] == 0 ){

            dfs2(u , cc , obr_gr , comp); 
        }
    }

}



int main() {
    int n = readInt();
    int m  = readInt();
    vector <vector <int > > gr(n); 
    vector <vector <int > > obr_gr(n); 
    vector <int> mark(n); 
    stack <int> ed ; 

    for (int i = 0; i < m ; i++){
        int u = readInt();
        int v = readInt();

        u--; v--; 
        gr[u].push_back(v); 
        obr_gr[v].push_back(u); 
    }
    for ( int i = 0 ;i < n ;i++){
        dfs( i, gr , mark , ed); 
    }


    int cc = 0 ; 
    vector <int> comp(n, 0); 
    while (!ed.empty()){
        int v = ed.top(); 
        ed.pop(); 
        if(comp[v] == 0 ){
            dfs2(v , ++cc , obr_gr , comp); 
        }
    }

    set<pair<int, int>> edge_set; // Множество уникальных рёбер между компонентами
    for (int u = 0; u < n; u++) {
        for (int v : gr[u]) {
            if (comp[u] != comp[v]) { // Если компоненты разные
                edge_set.insert({comp[u], comp[v]});
            }
        }
    }



    cout << edge_set.size() << endl;



    

    // for ( int i = 0 ; i < n ;i++){
    //     cout << i+ 1 << " " ; 
    //     for ( auto el : gr[i]){
    //         cout << el+ 1 << " " ; 
    //     }
    //     cout << endl ; 
    // }

    return 0;

}