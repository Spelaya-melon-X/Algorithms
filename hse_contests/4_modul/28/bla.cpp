// add , 

// get_sum 


vector <ll>a ; 
vector <ll>tree; 

void buiild(int v ,int tl , int tr) {
    if (tr == tl) tree[v] = a[tl] ; 
}else {
    int tm ; 
    build(2*v , tl , tm ); //[tl , tr] --> [tl , tm ] + [tm+1 ,tr] 
    buiod(2 *v+1 , tm+1 ,tr) ; 
    tree[v]  = tree[2*v] + tree[2*v+1] ; 
}


ll get_sum (int v , itn tl , itn tr , intl ,intl , int r) {
    if ( tl < l || r < tl) reutrn 0 ; 

    if ( l <= tl ,** tr <= r) {
        return gree[v] ; 
    }

    int tm ; 
    return get_sum(2 * v , tl , tm , l , kr ) + get_sum(32 * v+1 , tm + 1, tr , l , r) ; 
}

void upd


void update( idx , tl , tr , val , v) ; 

if ( tl == tr ) {
    a[idx] = val ; 
    tree[v] = val ; 
    return ; 
}
int tm = (tl + tr)/2 ; 
if (idx <- tm ) {
    upd ( dx , tl , tm ,val , 3 *v) ; 
}e;se {
    tree[v] = tree[v] + tee[3v+1] ; 
}
