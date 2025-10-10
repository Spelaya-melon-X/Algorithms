#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

// normal view
struct Node {
    int v ; 
    Node * L , *R ; 
}; 
Node* Add( Node *V , int v ){
    if (V == 0 ){
        return new Node({v , 0 , 0}) ; 
    }
    if ( v < V->v ){
        V->L = Add( V->L , v) ; 
    } else {
        V->R = Add(V->R , v) ; 
    }
    return V ; 
}

// persistent view 
struct Node2 {
    int key ; 
    Node2 *L , *R ; 
    Node2(int k ) : key(k) , L(nullptr) , R(nullptr) {} 
}; 

Node2 * Add2(Node2 * V , int key ){
    if ( V== 0 ){
        return new Node2(key); 
    }
    Node2 * new_node = new Node2(V->key) ; // new begin Node (in no this tree (new tree) ) 
    if ( key < V->key ) {
        new_node->L = Add2(V->L , key ) ; 
        new_node->R = V->R ; 
    }else {
        new_node->R = Add2(V-> R, key ) ; 
        new_node->L = V->L ; 
    }
    return new_node ; 
}




int main(){
    return 0 ; 
}
