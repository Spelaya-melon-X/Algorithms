#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include "optimization.h"
using namespace std;

struct Node {
    int key ; 
    int size ; 
    Node *L = nullptr, *R = nullptr; 
    Node(int key) : key(key) , size(1) , L(nullptr) , R(nullptr) {}

}; 

void update_size(Node*V){
    if (V){
        V->size = 1 + (V->L ? V->L->size : 0) + (V->R ? V->R->size : 0) ; 
    }
}

Node *Add(Node *v, int x){
    if (!v) {
        return new Node(x) ; 
    }
    if (x < v->key){
        v->L =  Add(v->L , x) ; 
    }else {
        v->R = Add(v->R , x); 
    }
    update_size(v) ; 
    return v; 
}

void print(Node *V ,int d = 0 ){
    if (!V) return ; 
    print(V->L, d+1) ; 
    for (int i = 0; i < 2 * d; i++) {
        cout << " ";
    }
    cout << "x=" << V->key << " size=" << V->size << "\n";
    print(V->R,d+1) ; 
}

int main() {


    int x;cin >> x; 
    Node root(x); 
    print(&root);
    while (cin >> x) {
        cout << "-\n";  
        Add(&root, x);
        print(&root); 
    }
    
    return 0;
}