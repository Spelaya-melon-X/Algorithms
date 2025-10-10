

 #include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

const int MaX = 100005 ; 
int s[MaX] ; 
int used[MaX] ; 
vector <vector <int> > gr ; 

// данная функция подсчитывает размеры поддеревьев рекурсивно , при этом заполняя s[v] , то есть расстряние до какой-то вершины 
void sizes(int v , int par ){
    s[v] = 1; 
    for ( auto u : gr[v]){
        if ( u != par and !used[u] ){
            sizes(u , v) ;  // <-- идем в следующие поддерево с соседом 
            s[v] += s[u] ; // <-- добавленям значение в значениях родствеников 
        }
    }
}

// возвращает центройд дерева 
int cenroid(int v , int p , int n ){
    for ( auto u : gr[v]){ // <-- проходим по всем вершинам 
        if ( u != p and !used[u] and s[u] > n  / 2){ // <--- ищем чтобы веришнка не являлась родилеям , не была посещена , а также что размер ее ребернка не превосходит половины 
            return cenroid(u, v,  n ) ; // идем дальше ищем центройды , только уже в меньших поддеревьях 
        }
    }
    return v; 
}

// подсчет расстояний 
void dfs( int v , int p , int dist , vector<int> &t){ // dist = 1-> dist = 2 -> ...
    t.push_back(dist) ; // добавляем вершинку , с расстоянием 
    for (auto u : gr[v]){ // после чего мы перебираем все вершинки из графа
        if ( u != p and !used[u]){ // проверка 
            dfs(u , v , dist+1 , t) ; // рекурсивно вызываем от dist + 1 , так как мы увеличиваем расстояние от корня до других вершин 
        }
    }
}

void  solve(int v , const vector <int> &L , vector<long long > &ans ){
    sizes(v , -1) ; // заполняем s[] 
    int c = cenroid(v , -1 , s[v]) ; // ищем центройд  построенный от вершины v (чтобы понимать какая вершина будет являться началом нашего поддерева )
    used[c] = true; // пометили 

    unordered_map<int, int> d; // мы создали unorded_map , для того , чтобы не несколько раз брать и считать все заново , а для того , чтобы сразу посчитать все кол-ва , и в u_m закинкть их 
    d[0] = 1 ; // пометили 

    for ( auto u : gr[c]){
        if ( !used[u]){
            vector <int> t ; // <- записываем  ввсе глубины деревьев 
            dfs(u , c , 1, t) ;  // запускаем dfs от этих вершин , чтобы подсчитатть все расстояния которые есть в текущий момент 
            for ( auto x : t ){ // <-- идем по массиву , который состоит из размеров подддеревьев ) 
                for( int i = 0 ; i< L.size() ; i++){ // перебираем все вершинки чтобы посчититать 
                    if (L[i] >=x and d.count(L[i] - x)) { // проверка на то , что расстояние приемлимое , а также что оно есть внутри u_m 
                        ans[i]+= d[L[i]-x] ; // тогда прибавляем к ans[i] это расттояние , которое мы посчитали 
                    }
                }


            }
            for ( int x : t){ // тут мы проходим ся по всем расстоняиям 
                d[x]++;  // обновляем что кол-во расстояний увеличилось 
            }
        }
    }

    // вызываемся от всех вершин графа которые не были посещены еще один раз (ркукрсияяя)
    for (int u : gr[c]){ 
        if (!used[u]){
            solve(u ,L , ans ) ; 
        }
    }

}



int main() {
    int n ; cin >> n ; 
    gr.resize(n+1) ; 
    // ! error 
    for ( int i = 1 ; i < n ; i++)    {
        int par ; cin >> par ; 
        gr[par].push_back(i) ; 
        gr[i].push_back(par) ; 
    }

    int k ; cin >> k ;
    vector <int> L(k ) ;
    for ( int i = 0 ; i < k ; i++){
        cin >> L[i] ; 
    }
    // cout << "wow" ; 
    vector <long long > ans(k , 0) ; 
    solve(0,L,ans) ; 

    for (auto x : ans){
        cout << x << " " ; 
    }


    return 0;
}