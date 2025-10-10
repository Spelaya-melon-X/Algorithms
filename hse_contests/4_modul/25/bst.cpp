
struct Node{
    int x , size  ; 
    Node *L , *R
}; 

Node* Add(Node * v , int ind , int x)  {
    if !v --> new node 

    int left_size = (v.l) ? v.l.size : 0 ; 

    if ( ind<= left_size ) {
        v.l = add(v.l , ind , x); 
    }else {
        v.r =add (v .r ,ind - left_size - 1 , x) 
    }
    v->size = upd ; 
    retur v; 
}


int get(node *v , int ind) {
    int left_size ; 

    if ( left_size == iunbd) {
        return v.x ; 
    }else if ( ind < left) {
        return get(v.l , ind)
    }else if (retur get(v.r , ind - l_s -1)) {
    
    }
}