#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;
int timer = 0 ; 

void dfs(vector <vector <int> > &v , vector <int> &in , vector<int > &out   , int u) {
    in[u] = timer++ ; 
    for (int i : v[u]) {

        dfs(v , in , out , i) ; 
    }
    out[u] = timer++; 
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n ; cin >> n ; 
    vector <vector<int> > v(n+1) ; 
    vector <int> in(n+1) , out(n+1) ;

    int root ; 
    for ( int i = 1 ; i < n+1 ; i++) {
        int p ; cin >> p ; 
        if ( p == 0 ) {
            root = i ; 
        }else {
            v[p].push_back(i);  
        }
    }

    dfs(v , in , out , root) ; 

    int zapr ; cin >> zapr ; 
    while (zapr--) {
        int a , b ; cin >> a >> b; 
        if ( in[a] <= in[b] && out[b] <= out[a]) {
            cout <<  1 << "\n" ; 
        }else {
            cout << 0 << "\n" ; 
        }
    }

    return 0;
}