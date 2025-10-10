#include <iostream>
#include <vector>
#include <tuple>
#include "optimization.h"

using namespace std;
const long long INF = 1000000000000000000LL; 

int main() {

    int n = readInt(); 
    int m = readInt(); 
    int s = readInt(); 
    int t = readInt(); 
    vector<tuple<int,int,long long>> gr(m); 

    for(int i = 0; i < m; i++) {
        int u = readInt(); 
        int v = readInt(); 
        long long  w = readInt(); 
        gr.emplace_back(u, v, w);
    }

    vector<long long> dist(n + 1, INF);
    dist[s] = 0;


    for(int i = 0; i < n - 1; i++) {
        bool us = false;
        for(const auto &e: gr) {
            int u , v ; long long w ; 
            tie(u ,v , w) = e ; 

            if(dist[u] < INF ){
                if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                us = true;
                }
            }
        }
        if(!us) {
            break;
        }
    }

    if(dist[t] == INF) {
        writeInt(INF,'\n');
    } else {
        writeInt(dist[t],'\n');
    }

    return 0;
}
