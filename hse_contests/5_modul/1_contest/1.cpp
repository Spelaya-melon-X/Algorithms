// найти максимальное паросочтание в двудольном графе, то есть паросочетание с максимально возможным числом ребер
// |A| = n , |B| = m  

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include "../optimization.h"
#include <chrono>
using namespace std;
vector<int > used; 
vector<int > pa;  // pa - пара у вершинки ( тк ор граф)
vector<vector<int> > graph ; 

// [[1 : [2 3]], 
// [2 : [ 1]], 
// [3 : [2 ,3 ]] ]
// 

bool dfs(int v ) {
    used[v] = 1; 
    for (auto x : graph[v]) {
        if ((pa[x] ==-1 )  || (!used[pa[x]]  && dfs(pa[x]))) {
            pa[x] = v ; 
            return true ; 
        }
    }
    return false;
}



int main() {
    auto start = chrono::high_resolution_clock::now();
    int n , m; cin>> n >> m ;  
    graph.resize(n+1 ) ; 
    pa.assign(m+1 , -1);
    used.assign(n + 1, 0);
    for (int i = 1 ; i <= n ;i++) {
        int el ; 
        while(cin>> el and el != 0 ) {
            graph[i].push_back(el) ; 
        }
    }

    int matching = 0 ; 
    for (int v = 1; v <= n ; v++) { 
        fill(used.begin(), used.end(), 0);
        if (dfs(v))  matching++; 
    }
    
    // print_graph() ; 

    cout << matching << endl;
    for (int j = 1; j <= m; j++) {          
        if (pa[j] != -1) {                  
            cout << pa[j] << " " << j << "\n";  
        }
    }
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();


    cout << "Execution time: " << (float)duration/1000 << " microseconds" << endl;





    return 0;
}