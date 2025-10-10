#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <set>
#include <unordered_map>
#include "../optimization.h"
using namespace std;

vector<bool> used ; 


void dfs(int v, vector<vector<int> >& ost_graph) {
    if (used[v]) return;
    used[v] = true;
    for (int u : ost_graph[v]) {
        dfs(u, ost_graph );
    }
}

int main() {
    // int m , n ; cin >> m >> n ; 
    int m = readInt();
    int n = readInt();
    vector<vector<int> > graph(m+1) ;
    used.resize( m + n +1 ,0)  ; 
    for ( int i = 1 ; i <= m ;i++) {
        // int c ; cin>> c ; 
        int c   = readInt();
        for (int j = 0 ; j < c ; j++) {
            // int k ; cin >> k ; 
            int k = readInt();
            graph[i].push_back(k + m ) ;  // sdvg

        }
    }
    // cout << 1 << "\n"; 
    vector<int> pA(m + 1, 0) ; 
    vector<int> pB(n + 1, 0) ; 

    for (int i = 1 ; i <= m ; i++ ) {
        // int p ; cin>> p ; 
        int p = readInt();  
        pA[i] = ( p== 0 ? 0 : p + m ) ; 
        pB[p] = i ; 
    }
    // cout << 2 << "\n"; 

    vector<vector<int> > ost_graph(m + n+1) ; 

    // A->B
    for (int i = 1 ; i <= m ; i++) {
        for (auto j : graph[i]) {
            auto p = std::make_pair(i, j) ; 
            if (pA[i] != j)  {
                ost_graph[i].push_back(j) ; 
            }
        }
    }
    // cout << 3 << "\n"; 
    //B->A
    for ( int i = 1 ; i <= m ; i++) {
        if (pA[i] != 0 ) {
            ost_graph[pA[i]].push_back(i) ; 
        }
    }
    // cout << 4 << "\n"; 

    for (int i =1 ; i <= m ; i++) {
        if (pA[i] ==0 ) {
            dfs(i , ost_graph) ; 
        }
    }
    // cout << 5 << "\n"; 

    vector<int> A ; 
    vector<int> B ; 

    for (int a = 1; a <= m; a++) {
        if (!used[a]) {
            A.push_back(a);
        }
    }
    // cout << 6 << "\n"; 

    for (int b = 1 + m; b <= n+m ; b++) {
        if (used[b]) {
            B.push_back(b-m);
        }
    }
    
    // cout << A.size() + B.size() << "\n"; 
    writeInt(A.size() + B.size() , '\n'); ;

    // cout << A.size() << " " ; 
    writeInt(A.size() , ' ');

    for ( auto el : A) {
        // cout  << el << " " ; 
        writeInt(el , ' ');
    }
    // cout << "\n" << B.size() << " " ; 
    writeChar('\n');
    writeInt(B.size() , ' ');
    for (auto el : B) {
        // cout << el << " "; 
        writeInt(el , ' ');
    }
    return 0;
}










