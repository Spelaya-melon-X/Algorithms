#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <stack> 
#include "optimization.h"
#include <set> 

using namespace std;

void dfs ( int v , vector <vector <int> > &gr , vector <int> &mark , stack <int> &ed ){
    if (mark[v]) return ; 
    mark[v] = 1; 
    for ( auto u : gr[v]){
        dfs(u , gr , mark , ed ); 
    }
    ed.push(v); 
}


stack<int> topsort (int n , vector <vector <int>> &gr){
    vector <int> visit(n , 0); 
    stack <int> st; 
    for ( int i = 0 ;i < n ;i++){
        dfs( i , gr   , visit , st); 
    }
    return st; 
}
void printStack(stack <int> &st){
    stack <int> tmpStack ; 
    tmpStack = st; 
    while (!tmpStack.empty()){
        int temp = tmpStack.top();  
        tmpStack.pop(); 
        cout << temp+1 << " ";  
    }
}

vector <int> replace_in_vector(stack<int> &st){
    vector <int > temp ; 
    while (!st.empty()){
        int t = st.top(); 
        temp.push_back(t); 
        st.pop(); 
    }
    return temp ; 

}

int main() {
    int n = readInt();
    int m  = readInt();
    vector <vector <int > > gr(n); 
    vector <int> mark(n) ; 
    stack <int> ed ; 
    set <pair<int, int> > sv ; 
    for (int i = 0; i < m ; i++){
        int u = readInt();
        int v = readInt();

        u--; v--; 
        sv.emplace(make_pair(u, v )); 
        gr[u].push_back(v); 
    }

    ed = topsort(n , gr) ; 
    // printStack(ed); 
    vector <int> t_gr =  replace_in_vector(ed) ; 

    bool uniq = true; 
    for ( size_t i = 0 ;i < t_gr.size()-1 ;i++){
        int u = t_gr[i]; 
        int v = t_gr[i+1];
        if (sv.find({u , v}) == sv.end()) {
            uniq = false; 
            break; 
        }
    }
    
    if (uniq) {
        cout <<  "YES\n";
        for (int v : t_gr) {
            cout << v + 1 << " "; 
        }
        cout << "\n";
    } else {
        cout << "NO\n";
    }
    

    // for ( int i = 0 ; i < n ;i++){
    //     cout << i+ 1 << " " ; 
    //     for ( auto el : gr[i]){
    //         cout << el+ 1 << " " ; 
    //     }
    //     cout << endl ; 
    // }

    return 0;

}