
#include <iostream> 



using  namespace std;
struct Node {
    int key   ; 
    int size ; 
    Node *L  , *R  ; 
    Node(int key_ , int size_ , Node *L_ , Node *R_) : key(key_) , size(size_) , L(L_) , R(R_){}
}; 

Node* insert(Node * V , int ind , int elem ){
    if (!V ) return new Node(elem , 1 , nullptr , nullptr) ; 
    
    int left_size = V->L ? V->L->size : 0 ; 

    if (ind <= left_size){
        V->L =  insert(V->L, ind , elem) ; 
    } else {
        V->R = insert(V->R , ind - left_size -1 , elem) ; 
    }
    V->size = 1 + (V->L ? V->L->size :0 ) + (V->R ? V->R->size :0 ) ; 
    return V ; 
}

int get(Node * V , int index ){
    int left_size = V->L ? V->L->size : 0 ; 

    if (index == left_size){
        return V->key ; 
    } else if( index < left_size){
        return get(V -> L , index ); 
    }else {
        return get(V->R , index - left_size - 1) ; 
    }
}


int main(){
    int a , b ; 
    Node *root = nullptr; 
    int ind= 0 ; 
    while (cin >> a >> b ){

        root = insert(root, a, b) ; 
        ind++; 
    }
    for ( int i = 0 ; i < ind; i++){
        cout << get(root , i) << " " ; 
    }

    return 0 ; 
}