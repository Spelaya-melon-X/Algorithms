#include <climits>
#include <iostream> 
#include <unordered_set>
#include <vector> 
#include <string> 
#include <algorithm>

using  namespace std;
struct Node {
    int key   ; 
    int inside_size ; 
    Node *L = nullptr , *R = nullptr , *P = nullptr; 
    Node(int key_ , int inside_size , Node *L_ , Node *R_ , Node* P_) : key(key_) , inside_size(inside_size) , L(L_) , R(R_) , P(P_) {}
}; 

Node* Add(Node *V , int x ){
    if ( !V  ) {
        return new Node(x ,1, nullptr , nullptr , V); 
    }
    if ( x < V->key){
        V->L = Add(V->L, x) ;
        // if (V->L){
        V->inside_size = 1 + (V->R ? V->R->inside_size : 0 ) + (V->L ? V->L->inside_size : 0) ; 
        // }
    }
    else if (x > V->key)  {
        V->R = Add(V->R , x) ; 
        // if (V->R){
        V->inside_size = 1 + (V->R ? V->R->inside_size : 0 ) + (V->L ? V->L->inside_size : 0) ; 
        // }
    }
    return V; 
}


int get_kth(Node *V , int k){
    int left = V->L ? V->L->inside_size : 0 ; 
    if ( left == k ) {
        return V->key ; 
    }
    if (k < left ) {
        return get_kth(V->L,  k) ; 
    }
    return get_kth(V->R, k - left -1) ; 
}




int main(){
    char s ; 

    Node *root = nullptr; 
    unordered_set<int> um; 
    while (cin >> s) {
        if (s == '+') {
            int x ; cin >> x ; 
            if (um.find(x) == um.end() ){
                root = Add(root,  x) ; 
            }
            um.insert(x) ; 
            // cout << root->inside_size << '\n'; 
 
        } 
        if ( s == '?') {
            int x ; cin >> x; x--;
            cout << get_kth(root,  x) << '\n'; 
        }
    }

    return 0 ; 
}