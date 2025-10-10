#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

using ll = long long;

std::vector <ll> a ; 
std::vector <ll > tree ;

void build(int v , int tl , int tr){
    if (tl == tr) {
        tree[v] = a[tl] ;
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
void update(int idx, int tl, int tr, ll val, int v) {
    if (tl == tr) {  
        a[idx] = val;
        tree[v] = val;
        return;
    }
    int tm = (tl + tr) / 2;
    if (idx <= tm) {
        update(idx, tl, tm, val, 2 * v);  
    } else {
        update(idx, tm + 1, tr, val, 2 * v + 1);  
    }
    tree[v] = tree[2 * v] + tree[2 * v + 1];  
}



int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n , k ;  cin >> n >> k ; 
    a.resize(n+ 1 , 0) ;
    tree.resize(4 * n ) ;
    build(1 , 1 , n ) ;
        for (int i = 0; i < k; i++) {
        char c;
        cin >> c;
        if (c == 'A') {  
            int idx ; ll val;
            cin >> idx >> val;
            update(idx, 1, n, val, 1);
        } if (c == 'Q') {
            int l, r;
            cin >> l >> r;
            cout << get_sum(1, 1, n, l, r) << "\n";
        }
    }

    return 0;
}