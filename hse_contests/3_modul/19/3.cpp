

// восстановление ответа дейскртры
#include <iostream>
#include <vector>
#include <set>
#include <climits> 
#include "optimization.h"
using namespace std;



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

    vector  <int> dist(n  ,INT_MAX); 
    set< pair<int, int> > se ;
    vector <int> p(n ,-1);  // для восатновления ответа 

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
                p[v] = u ; // берем и запоминаем элементы , которые мы берем 
                se.insert(make_pair(dist[v] , v)); 
            }
        }
    }
    // восстанавливаем путь 
    vector <int > path; 
    for ( int i = t ; i != -1 ; i = p[i]){ // t --> while i != -1 (пока путь продолжается) идем по обратным ссылкам 
        path.push_back(i); 
    }
    reverse(path.begin() , path.end()); // переворачиваем результат 
    

    if (dist[t] == INT_MAX){


        writeInt(-1); 
        return 0 ; 
    }else {
        writeInt(dist[t], '\n'); 
        for ( auto el : path){
            writeInt(el+ 1 , ' ');  
        }
    }


    // writeInt(ans); 



    return 0;
}