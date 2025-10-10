#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

struct Node {
    int key; 
    int size ; 
    Node *L , *R; 
    Node(int k ) : key(k) , L(nullptr) , R(nullptr) , size(1) {}
}; 

int get_size(Node *V ){
    return (V) ? V->size : 0 ; 
}

void update_size(Node *V ){
    if (V){
        V->size =  1 + max(get_size(V->L) , get_size(V->R)) ; 
    }
}
int getBalance(Node *V) { 
    if (!V) return 0; 
    return get_size(V->L) - get_size(V->R); 
} 

    /* 
    до                          
                V   
              /   
             X
              \
               Y
    После 
                X
                  \
                    V
                   /
                 Y

*/
Node* rototaRigth(Node *V){
    Node *X = V->L ; 
    Node *Y = X->R ; 
    
    X->R = V ; 
    V->L = Y ; 
    update_size(V); 
    update_size(X); 

    return X ; 
}



Node *rotateLeft(Node *V){
    Node *X = V->R ; 
    Node *Y = X->L ; 

    X->L = V ; 
    V->R = Y; 

    update_size(V); 
    update_size(X); 
    return X ; 
}


Node *insert(Node *V , int x){
    if (!V) return new Node(x)  ;

    if (x <  V->key){
        return insert(V->L,  x) ; 
    }else if (x > V->key){
        return insert(V->R, x) ; 
    }else {
        return V ; 
    }
    update_size(V); 
    int balance = getBalance(V) ; 
    if (balance > 1 && x < V->L->key) {
        return rototaRigth(V) ; 
    }
    if ( balance < -1 && x > V->R->key) {
        return rotateLeft(V) ; 
    }
    if (balance > 1 && x > V->L->key) {
        V->L = rotateLeft(V->L)  ; 
        return rototaRigth(V) ; 
    }
    if (balance < -1 && x < V->R->key) { 
        V->R = rototaRigth(V->R); 
        return rotateLeft(V); 
    } 

    return V; 
}

Node* Delete() {

}

bool exists(Node* V , int x){

}

int next() {

}

int prev() {

}


int main(){

    return 0 ; 
}