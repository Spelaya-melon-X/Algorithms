#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <stack> 
#include <algorithm>
#include "optimization.h"
using namespace std;

void dfs(int  v , vector < int> &mark , vector <vector <int>> &gr, stack <int> &st){
    if (mark[v] ) return  ; 
    mark[ v ] = 1; 

    for (int u : gr[v]){
        dfs(u , mark , gr , st); 
    }
    st.push(v);
}

stack <int> topsort(int n , vector < vector < int >> &gr){

    stack <int > st ; 
    vector <int > mark( n, 0); 
    for ( int i  = 0 ;i < n ; ++i){
        if (!mark[i] ){
            dfs(i, mark, gr , st) ; 
        }
    }

    return st; 
}



int ml(int n, stack <int> &st , vector <vector <int>> &gr){
    vector<int> dp(n, 0);  
    stack<int> tmp_st;
    tmp_st = st;


    while (!tmp_st.empty()) {
        int v = tmp_st.top();  tmp_st.pop();

        for (int u : gr[v]) {
            dp[u] = max(dp[u], dp[v] + 1);  
        }
    }

    return *max_element(dp.begin(), dp.end());

}


int main() {
    int n  = readInt(); 
    int m   = readInt(); 

    vector < vector< int > > gr(n); 
    vector <int> mark(n , 0); 
    stack <int> st ; 
    for (int i = 0 ; i< n ;i++){
        int v = readInt(); int u = readInt(); u--; v--; 
        gr[v].push_back(u); 
    }


    st = topsort(n , gr); 

    int ans =  ml(n, st , gr); 
    writeInt(ans); 

    
    
    





    return 0;
}