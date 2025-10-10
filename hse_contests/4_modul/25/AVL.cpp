#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

struct Node {
    int key; 
    Node *L , *R; 
    int height ; 
    Node(int k ) : key(k) , L(nullptr) , R(nullptr) , height(1) {}
}; 

int Height(Node *V){
    if (V == nullptr)    {
        return 0 ; 
    }else {
        return V->height ; 
    }
}

Node * RightRotate(Node *V){
    Node *X = V->L ; 
    Node *Y = X->R ; 

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
    X->R = V ; 
    V->L = Y ; 

    V->height = 1 + max(Height(V->R) , Height(V->L)) ; 
    X->height = 1 +max(Height(X->R) , Height(X->L)) ; 

    return X ; 

}

Node * LeftRotate(Node *V){
    Node *X = V->R ; 
    Node *Y = X->L ; 

    /* 
    до                          
                V   
                 \  
                   X
                  /
                Y
            
    После 
                X
               /
              V
               \
                Y
    */
    X->L = V ; 
    V->R = Y; 

    V->height = max(Height(V->R), Height(V->L)); 
    X->height = max(Height(X->R), Height(X->L)) ; 

    return X ; // return new root 

}

int GetBalance(Node *V){
    if (V == 0){
        return 0 ; 
    }else {
        return Height(V->L) - Height(V->R) ; 
    }
}

int getSize(Node *t) {
    return t ? t->height : 0;
}

void update(Node *t) {
    if (t)
        t->height = 1 + getSize(t->L) + getSize(t->L);
}

void split(Node *t, Node *&l, Node *&r, int k) {
    if (!t)
        l = r = nullptr;
    else if (getSize(t->L) >= k) {
        split(t->L, l, t->L, k);
        r = t;
        update(r);
    } else {
        split(t->L, t->L, r, k - getSize(t->L) - 1);
        l = t;
        update(l);
    }
}

void Cyrcle_shift(Node *V , int l , int r , int d){
    Node *L ,*R , *M; 
    split(V , L , V , l-1) ; // отделяем начало 
    split(M  , M , R , r-l+1) ; // отделяем сегмент [l ,r]

    Node *M1 , *M2 ; 
    split(M , M1 , M2 , d) ; // делим сегмент на две части 
    V = merge(L , merge(M2 , merge(M1 , R))) ; // собираем все со сдвигом 
}



int main() {
    return 0;
}