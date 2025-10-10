#include <iostream>
#include <vector>
#include <string>
#include "optimization.h"
#include <unordered_map>
using namespace std;
struct DSU {
    vector<int> p;
    vector<int> sz;
    int m ; 
    DSU(int n) : p(n), sz(n,1 ) , m(1) {

        for (int i = 0; i < n; i++) {
            p[i] = i;
        }
    }

    int find(int v) { return p[v] == v ? v : p[v] = find(p[v]); }
    // int find(int v) {
    //     if (p[v] == v) return v;
    //     return p[v] = find(p[v]);
    // }
    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return;
        if (sz[a] < sz[b]) swap(a, b);
        p[b] = a;
        sz[a] += sz[b];
        m = max(m , sz[a]);
    }  
};

int main() {

    int t  = readInt() ; 
    while (t --){
        int n = readInt() ;
        vector <int> p(n-1)  , q(n-1) ,res; 
        for (int i = 0 ; i < n-1 ; i++){
            p[i] = readInt()  ; 
        }
        DSU dsu(n) ; 
        for (int i = 0 ; i < n-1 ; i++){
            q[i] = readInt()  ; 
        }
        for (auto x: q){
            dsu.unite(x, p[x-1]) ;
            res.push_back(dsu.m) ;
        }
        for (auto x: res){
            writeInt(x) ;
            writeChar(' ') ;
        }
        writeChar('\n') ;
    }

    return 0;
} 