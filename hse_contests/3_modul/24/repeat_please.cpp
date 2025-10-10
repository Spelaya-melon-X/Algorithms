#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

const int Max = 100005 ; 
int s[Max]; 
int used[Max] ; 
vector <vector<int> > gr ; 

void sizes(int v , int p  ) {
    s[v] = 1; 
    for ( auto u : gr[v]){
        if ( u != p and !used[u] ){
            sizes(u , v) ; 
            s[v]+= s[u] ; 
        }
    }
}

int centroid(int v , int p , int n ){
    //? мб чет забыл 
    for ( auto u : gr[v]){
        if ( u != p and !used[u] and s[u] > n /2 ){
            return centroid(u, v,  n) ; 
        }
    }
    return v ; 
}   

void dfs(int v , int p ,  int dist , vector <int> &t ){
    t.push_back(dist) ; 
    for ( auto u : gr[v]){
        if ( !used[u] and p != u  /* something*/){
            dfs(u , v , dist+1 , t) ; 
        }
    }
}

void solve(int v ,  const vector <int>&L , vector <long long > &ans){
    sizes(v, -1) ; 
    int c = centroid(v, -1, s[v]) ; 
    used[c] = 1; 

    unordered_map<int, int> d ; 
    d[0] =1 ; 
    for ( auto u : gr[c]){
        if (!used[u]){
            vector <int> t ; 
            dfs(u , c , 1 , t) ; //! <--  idk error! v -> c 
            for (auto x : t){
                for (int i = 0 ; i < L.size() ; i++){
                    if ( L[i] >= x && d.count(L[i] - x )) {
                        ans[i] += d[L[i] - x] ;
                    }
                }
            }
            for ( int x : t){
                d[x]++; 
            }
        }
    }
    for ( auto u : gr[c]){
        if (!used[u]){
            solve(u , L , ans) ; 
        }
    }
    
}


int main() {
    int n ; cin >> n ;
    gr.resize(n+1) ; 
    for ( int i = 1 ; i < n ; i++){
        int temp; cin >> temp ;
        gr[temp].push_back(i);
        gr[i].push_back(temp);
    }

    int k ; cin >> k ; 
    vector<int> L(k) ; 
    for ( int i = 0 ; i < k ; i++){
        cin >> L[i] ; 
    }

    vector <long long > ans(k , 0); 
    solve(0 , L,  ans); 

    for (auto x : ans){
        cout << x << " " ; 
    }


    return 0;
}