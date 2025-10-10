
#include <iostream> 
#include <vector> 
#include <stack>
#include <algorithm>
using namespace std;


void dfs(int v , vector <int> &mark , vector <vector <int>> &edges , stack <int> &sorted_edge){
    if (mark[v] ) return  ; 
    mark[v] = 1; 
    for (int u : edges[v]){
        dfs(u , mark , edges , sorted_edge); 
    }
    sorted_edge.push(v);
}


    stack <int> topsort(int n , vector < vector < int >> &edges){
        vector <int > visit(n, 0); 
        stack <int> st; 
        for ( int i = 0 ;i < n ; i++){
            if (!visit[i]){
                dfs(i, visit, edges , st) ; 
            }
        }
        return st; 
    }

int max_lenght(int n, stack <int> &st , vector <vector <int>> &edges){
    vector<int> dp(n, 0);  
    stack<int> tmpStack;
    tmpStack = st;


    while (!tmpStack.empty()) {
        int v = tmpStack.top(); 
        tmpStack.pop();

        for (int u : edges[v]) {
            dp[u] = max(dp[u], dp[v] + 1);  
        }
    }

    return *max_element(dp.begin(), dp.end());

}

int main(){
    int n , m ; cin >> n  >> m ; 
    stack<int> st ;

    vector <int> mark(n, 0) ; 
    vector <vector <int> > edges(n) ; 

    for ( int i = 0;i < m ;i++){
        int f , t ; cin >> f >> t ; 
        f--; t--; 
        edges[f].push_back(t) ; 
    }
    st = topsort(n , edges); 

    cout << max_lenght(n, st , edges); 
    
    
    


    return 0 ; 
}