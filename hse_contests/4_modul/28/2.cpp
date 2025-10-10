
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

using ll = long long;
const int MAXN = 1'000'00;

std::vector <ll > tree ;

void build(int v , int tl , int tr){
    if (tl == tr) {
        tree[v] = 0 ;
    }else {

        int tm = (tr + tl )/2 ; 
        build(2* v , tl , tm ) ; 
        build(2* v + 1 , tm+1 , tr ); 
        tree[v] = tree[2 * v] + tree[2 * v + 1] ;
    }
}

ll get_sum( int v , int tl , int tr , int l , int r ){

    if (tr < l || r < tl) { return 0; }

    if (l <= tl && tr <= r) {
        return tree[v];
    }

    int tm = (tr + tl )/2 ; 
    return get_sum(2 * v , tl , tm , l , r ) + get_sum(2 * v + 1 , tm + 1 , tr , l , r ) ;
}
void update(int idx, int tl, int tr, int v) {
    if (tl == tr) {  
        tree[v]++;
        return;
    }
    int tm = (tl + tr) / 2;
    if (idx <= tm) {
        update(idx, tl, tm, 2 * v);  
    } else {
        update(idx, tm + 1, tr, 2 * v + 1);  
    }
    tree[v] = tree[2 * v] + tree[2 * v + 1];  
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n ; 
 
    while (cin >> n ){
        tree.assign(4 * MAXN, 0); 
        vector<int> levels(n, 0);
        build(1 , 0 , MAXN-1 ) ;
        for ( int i = 1 ; i <= n ; i++){
            
            int x , y ; cin >> x >> y ; 
            levels[get_sum(1 , 0 , MAXN-1 , 0 , x )]++;
            update(x , 0 , MAXN-1 , 1 ) ;
        }
        for (int i = 0 ; i < n ; i++){
            cout << levels[i] << "\n" ;
        }


    }

}