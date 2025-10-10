#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include "optimization.h"
using namespace std;

struct edge {
    int u , v , w ; 
    bool operator < (const edge &other) const {
        return w < other.w;
    }
}; 

struct DSU {
    vector <int> parent;    
    DSU(int n) : parent(n) {
        for(int i = 0; i < n; ++i)
            parent[i] = i;
    } 
    void make_set(int v) {
        parent[v] = v;
    }

    int find_set(int v) {
        if (v == parent[v])
            return v;
        return parent[v] = find_set(parent[v]);
    }

    void union_sets(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if (a != b)
            parent[b] = a;
    }
}; 

int main() {
    int n = readInt() , m = readInt();
    vector < edge > gr(n);
    for ( int i = 0 ; i< m ; i ++){
        int b = readInt() , e = readInt() , w = readInt();
        b--; e--; 
        gr.push_back({b , e , w});
    }
    int cost = 0 ; 
    sort(gr.begin() , gr.end());
    DSU dsu(n); 
    int edc = 0 ; 
    for ( const auto &x : gr){
        if (dsu.find_set(x.u) != dsu.find_set(x.v)){
            dsu.union_sets(x.u , x.v);
            if (x.w > 0){
                cost += x.w;
                if (++edc == n - 1)
                    break ; 
            }
        }
    }
    writeInt(cost);



    return 0;
}