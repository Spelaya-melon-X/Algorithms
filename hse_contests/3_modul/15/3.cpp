#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <set>
#include "optimization.h"
using namespace std;


vector <vector <int> > gr; 
vector <int>up ; 
vector <int>tin ; 
vector <int> mark ; 

static int t = 0 ; 
set <int> ans ; 
void dfs( int v , int parent ){
    up[v] = tin[v] = t++; 
    if ( mark[v]){
        return ; 
    }
    mark[v] =1 ; 
    int count = 0 ; 
    for (auto u : gr[v]){
        if ( u == parent){
            continue;
        }
        if (mark[u]){
            up[v] = min(up[v] , tin[u]); 
        }else {
            dfs(u , v); 
            count++ ; 
            up[v] = min(up[v] , up[u]); 
            if ( parent != -1 && up[u] >= tin[v]){
                ans.insert(v) ; 
            }
        }
    }
    if (parent == -1 && count >= 2 ){
        ans.insert(v); 
    }   
}   

int main() {
    int n = readInt(); 
    int m = readInt(); 
    gr.resize(n); 
    mark.assign(n, 0);  
    up.resize(n); 
    tin.resize(n); 
    for (int i = 0 ;i < m  ;i++){
        int beg = readInt() - 1; 
        int end = readInt() - 1; 

        gr[beg].push_back(end);
        gr[end].push_back(beg);
    }
    for ( int i = 0 ;i < n ;i++){
        if ( !mark[i]){
            dfs(i, -1); 
        }
    }   
    cout << ans.size() << endl ;


    for (const  auto &elm : ans){
        cout << elm +1<<  '\n'; 
    }






    return 0;
}