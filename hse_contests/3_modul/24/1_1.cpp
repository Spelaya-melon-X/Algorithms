

void sizes(int v ,  int par) {
    s[v] = 1; 
    for ( auto u : gr[v]) {
        if ( u != par && !used[u]) {
            sizes( u , v) ; 
            s[v] += s[u] ; 
        }
    }
}


void cent( v , int par , n) ; // обходим все места которые мы можем войти , и проверяем , что если у нас размер поддпеерева больче чем n /2 тогда мы вызываемся центройдом от туда 

for (u -> gr[u]) {
    if ( u != p && !used[u] && s[u] > n / 2) {
        retiurn cent(u ,v n , )
    }
}

void dfs(int v , int p , int dist , t){
    t.push_back(dist) ; 
    for * auto u : gr[v] {
        if ( u!= p , !used[u]) {
            dfs(u ,v , dist +1 , t) ; 
        }
    }
}


void solve( int v , vector L , vector Ans) {
    seize(v -1,) ; // заполняем расстояния
    int c = cent( v , -1 , s[v]) ; 
    used[c] = true; 

    u_m<int int> d; 
    d[0] = 1; 

    for ( auto u : gr[c]) {
        if (!used[u]) {
            vector <int> t ; 
            dfs(u ,c , 1 ,t) ; 
        }
    }

}