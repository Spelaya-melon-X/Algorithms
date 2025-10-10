#include <climits>
#include <iostream> 
#include <vector> 
#include <string> 
#include <algorithm>

using  namespace std;
struct Node {
    int key   ; 
    Node *L = nullptr , *R = nullptr ; 
}; 

Node* Add(Node *V , int x ){
    if ( !V  ) {
        return new Node({x , nullptr , nullptr }); 
    }
    if ( x < V->key){
        V->L = Add(V->L, x) ; 
    }
    else  {
        V->R = Add(V->R , x) ; 
    }
    return V; 
}



int Min(Node*V , int x){
    if (!V) return 0 ; 

    if ( x < V->key){
        int n = Min(V->L , x) ; 
        if ( n != 0 ){
            return min(n ,V->key ) ; 
        }else {
            return V->key ; 
        }
    }else {
        return Min(V->R , x) ; 
    }
}


int main(){
    char s ; 

    Node *root = nullptr; 
    bool flag = 0 ; 
    while (cin >> s) {
        if (s == '+') {
            int x ; cin >> x ; 
            root = Add(root,  x) ; 
            // cout << "root-->key: " << root->key << "\n" ; 
        } 
        if ( s == '>') {
            int x ; cin >> x; 
            cout << Min(root , x) << '\n' ; 
        }
    }

    return 0 ; 
}