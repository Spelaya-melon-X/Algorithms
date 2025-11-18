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

    // доли макс паросочетнаия читаем
    vector<int> pA(m + 1, 0) ; 
    vector<int> pB(n + 1, 0) ; 

    for (int i = 1 ; i <= m ; i++ ) {
        int p = readInt();  
        pA[i] = ( p== 0 ? 0 : p + m ) ; 
        pB[p] = i ; 
    }

    vector<vector<int> > ost_graph(m + n+1) ; 

    // A->B (те добалвяем только те ребра , которые которые есть в исходном графе )
    for (int i = 1 ; i <= m ; i++) {
        for (auto j : graph[i]) {
            if (pA[i] != j)  { 
                ost_graph[i].push_back(j) ; 
            }
        }
    }

    //B->A (только ребра из паросочетания )
    for ( int i = 1 ; i <= m ; i++) {
        if (pA[i] != 0 ) {
            ost_graph[pA[i]].push_back(i) ; 
        }
    }

    for (int i =1 ; i <= m ; i++) {
        if (pA[i] ==0 ) {
            dfs(i , ost_graph) ; 
        }
    }


    vector<int> A ; 
    vector<int> B ; 

    for (int a = 1; a <= m; a++) {
        if (!used[a]) {
            A.push_back(a);
        }
    }

    for (int b = 1 + m; b <= n+m ; b++) {
        if (used[b]) {
            B.push_back(b-m);
        }
    }
    

    writeInt(A.size() + B.size() , '\n'); ;
    writeInt(A.size() , ' ');

    for ( auto el : A) {
        writeInt(el , ' ');
    }

    writeChar('\n');
    writeInt(B.size() , ' ');
    for (auto el : B) {
        writeInt(el , ' ');
    }
    return 0;
}










