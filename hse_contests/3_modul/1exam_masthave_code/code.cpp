// 1_14 - длинейший путь : 

#include <iostream> 
#include <vector> 
#include <stack>
#include <algorithm>
using namespace std;
/**
 * алгоритм : топсорт 
 * 
 */

void dfs(int v , vector <int> &mark , vector <vector <int>> &edges , stack <int> &sorted_edge){
    if (mark[v] ) return  ; 
    mark[v] = 1; 
    for (int u : edges[v]){
        dfs(u , mark , edges , sorted_edge); 
    }
    sorted_edge.push(v);
}


stack <int> topsort(int n , vector < vector < int >> &edges){
    vector <int > visit(n, 0); 
    stack <int> st; 
    for ( int i = 0 ;i < n ; i++){
        if (!visit[i]){
            dfs(i, visit, edges , st) ; 
        }
    }
    return st; 
}

int max_lenght(int n, stack <int> &st , vector <vector <int>> &edges){
    vector<int> dp(n, 0);  // Массив для хранения максимальных длин путей
    stack<int> tmpStack;
    tmpStack = st;

    // Проходим по вершинам в топологическом порядке
    while (!tmpStack.empty()) {
        int v = tmpStack.top(); 
        tmpStack.pop();

        for (int u : edges[v]) {
            dp[u] = max(dp[u], dp[v] + 1);  // Обновляем максимальную длину пути для соседа
        }
    }

    // Находим максимальную длину пути среди всех вершин
    return *max_element(dp.begin(), dp.end());

}

int main(){
    int n , m ; cin >> n  >> m ; // n - количесвтво вершин m - количество ребер 
    stack<int> st ;

    vector <int> mark(n, 0) ; 
    vector <vector <int> > edges(n) ; 

    for ( int i = 0;i < m ;i++){
        int f , t ; cin >> f >> t ; 
        f--; t--; 
        edges[f].push_back(t) ; 
    }
    st = topsort(n , edges); 

    cout << max_lenght(n, st , edges); 

    // for ( int i = 0 ;i < n ;i++){
    //     for ( auto el : edges[i]){
    //         cout << i << " " << el << endl; 
    //     }
    // }

    return 0 ; 
}

// 2_14 - цикл
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std; 

bool dfs( int v , vector <vector < int> > &edges , int &cycle_begin , int &cycle_end, vector <int> &parents, vector <int> &color){
        color[v] = 1; 
        for (auto u : edges[v]){
            if ( color[u] == 0 ){
                parents[u] = v; 
                if (dfs( u , edges, cycle_begin , cycle_end , parents , color)){
                    return true; 
                }

            } else if (color[u] == 1 ) {
                cycle_begin = u ; 
                cycle_end = v; 
                return true; 

            }
        }
        color[v] = 2 ; 
        return false; 


}

void find_cycle( int  n , vector < vector <int> > &edges){
    vector <int> parents(n , -1) ;
    vector <int> color(n , 0); 
    int cycle_begin = -1 , cycle_end = -1; 

    for (int i = 0 ; i < n; i++) {
        if (color[i] == 0) {
            if (dfs( i , edges , cycle_begin , cycle_end , parents , color)) {
                break;
            }
        }
    }

    if (cycle_begin == -1) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
        vector<int> cycle;

        for (int v = cycle_end; v != cycle_begin; v = parents[v]) {
            cycle.push_back(v);
        }
        cycle.push_back(cycle_begin); 
        reverse(cycle.begin(), cycle.end()); 
        for (int v : cycle) {
            cout << v + 1 << " "; 
        }
        cout << endl; 
    }

}


int main() {
    int n , m ; cin >> n >> m ; 

    vector <vector < int > > edges(n) ; 

    for ( int i = 0;i < m ;i++){
        int f , t ; cin >> f >> t ; 
        f--; t--; 
        edges[f].push_back(t) ; 
    }
    find_cycle(n , edges); 



    // for ( int i = 0 ;i < n ;i++){
    //     for ( auto el : edges[i]){
    //         cout << i << " " << el << endl; 
    //     }
    // }
    return 0;
}

//1_15 - кошки 
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <set>
#include <bitset>
using namespace std;
/*
1 vector bool !

*/
static int count_trigl = 0 ; 

int main() {  
    int v , e ; cin >> v >> e ; 
    vector<vector<bool>> gr(v, vector<bool>(v, false));
    set<std::pair<int,int> > us;  
    for ( int i = 0 ; i < e ; ++i){
        int a , b ;cin >> a >> b ; 
        a--;  b--; 

        gr[a][b] =1 ; 
        gr[b][a] =1 ; 

        us.insert(std::make_pair(min(a,b), max(a,b))); 

    }
    for (auto &[a,b] : us){
        int count = 0 ; 
        for (int i = 0 ;i < v ; ++i){
            if (gr[a][i] && gr[b][i]){
                count++ ; 
            }
        }

        // int count = ob.count();
        count_trigl += count  ;

    }
    std ::cout << count_trigl/3 ;


    // for ( int i = 0 ; i < e ; i++){
    //     cout << i << ":" << endl; 
    //     for (auto el : gr[i]){
    //         cout << el << " " ; 1
    //     }
    //     cout << endl; 
    // }
    return 0;
}

//2-15
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <set>
#include <stack>
#include "optimization.h"
using namespace std;

vector <int> mark ; 
stack <int> st ; 
vector <vector <int > > gr; 
vector <vector <int > > obr_gr; 
vector <int > comp ;

// дфс для того , чтобы заполнить стэк значениями - просто получается топсорт мы сделалми 
void dfs(int v , vector <vector <int> >&gr ){
    if ( mark[v]) return ; 
    mark[v] = 1; 
    for ( auto u : gr[v]){
        dfs(u , gr);
    }
    st.push(v); 
}
// этот дфс он проходит по обратным ребрам , для того , чтобы красить граф в определнные компоненты 
void dfs2(int v , vector<vector <int> >&obr_gr , int cc , vector<int> &comp){
    comp[v] = cc ; 
    for (auto u : obr_gr[v]){
        if (comp[u] == 0)
            dfs2(u , obr_gr , cc , comp ); 
    }

}

int main() {
while (!isEof()){
    int n = readInt(); 
    int m = readInt();
    if (n == 1 and m == 0 ){
        writeInt(1,'\n'); 
        continue;
    }
    gr.resize(2*n);  
    obr_gr.resize(2*n);  
    mark.assign(2 * n, 0);
    comp.assign(2 * n, 0);

    for (int i = 0; i < m  ; i++){ 
        int i_1  = readInt(); int e_1  = readInt(); int  i_2 = readInt();  int e_2 = readInt();


        int u_in = 2* i_1 + (1- e_1) ; 
        int v_in = 2 * i_2 + (1 - e_2);    
        int u_out = 2 * i_2 + e_2   ; 
        int v_out = 2* i_1 + e_1 ; 

        gr[v_in].push_back(v_out);
        obr_gr[v_out].push_back(v_in);

        gr[u_in].push_back(u_out);
        obr_gr[u_out].push_back(u_in);
    }
    // вызываемся от каждой вершины 
    for (int i = 0 ; i < 2*n ; i++){
        dfs(i, gr); 
    }
    // подсчитываем комопненты связанности 
    int cc = 0 ;
    while ( !st.empty()){
        int v = st.top(); 
        st.pop(); 
        if (comp[v] == 0) { // только в том случае , когда у нас не покрашена компонента - вызываем дфс от нее 
            dfs2(v ,obr_gr , ++cc , comp); 
        }
    }


    int ans[n]; 
    for ( int v= 0 ; v < n  ;v++){
        if (comp[2*v] >  comp[2*v+1]){  
            ans[v] = 0 ; 
        }else {
            ans[v] = 1; 
        }
    }

    for ( int i = 0 ; i < n ; i++){
        writeInt(ans[i]); 
    }
    writeChar('\n'); 


    gr.clear();
    obr_gr.clear();
    comp.clear();
    mark.clear();

}    
return 0;
}

// 1_16 - поллард 
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>qx
#include <numeric>
#include "optimization.h"
using namespace std;

__int128_t f(__int128_t x , __int128_t n  ){
    return (x  + 1)* (x + 1)% n;
}

__int128_t finder(__int128_t n , __int128_t seed = 2 ){
    __int128_t x = seed ; 
    __int128_t y = seed; 
    __int128_t divisor = 1; 
    for (__int128_t i = 0 ;i < 1000000 && divisor == 1 ; i++){
        x = f(x,n ) ; 
        y = f ( f ( y , n )  , n);  
        divisor = std::gcd((x - y) , n ) ;  

        if ( divisor > 1 and divisor < n ) return divisor ; 
    }
    return -1 ; 
}

int  main() {

    while( !isEof() ){
        __int128_t n = readInt(); 
        __int128_t s = finder( n , 2
        ); 
        if ( n == 2){
            writeWord("IMPOSSIBLE") ;continue;; 
        }
        if(n % 2 == 0) {
            writeInt(2, ' ') ; writeInt(n / 2 , '\n' ); continue;; 
        }
        if ( s == - 1 or s == n ){
            writeWord("IMPOSSIBLE\n"); continue;
        } else if (s < 2 ){
            writeWord("IMPOSSIBLE\n"); continue;; 
        } else {
            writeInt(s, ' ') ; writeInt(n / s , '\n'); continue;; 
        }
    }
    return 0; 
}


// 1_17 - 3-sat 




#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <cstdlib>
#include "optimization.h"
using namespace std;

static int bad_x_index; 
struct Point{
    int x_ind; 
    bool wh  ; 
};

struct Line{
    std::vector <Point> vec; 
}; 

int psevdoRandom(){
    return std::rand() % 2 ; 
}

void fillingRandomXPermutation(std::vector <int> &x_perm   ){
    for ( int i = 0 ;i < x_perm.size() ;i++){
        x_perm[i] = psevdoRandom(); 
    }


}

void changeX_Perm(std::vector <int> &x_perm){
    x_perm[bad_x_index] = 1 - x_perm[bad_x_index]; 
 
}

bool isNormalPerm(const vector<Line>& form, const vector<int>& x_perm) {
    int m = form.size();
    for (int i = 0; i < m; i++) {
        if ( x_perm[ form[i].vec[0].x_ind ] == form[i].vec[0].wh || x_perm[ form[i].vec[1].x_ind ] == form[i].vec[1].wh || x_perm[ form[i].vec[2].x_ind ] == form[i].vec[2].wh ) {
        } else {
            int random_var = std::rand() % 3;
            bad_x_index = form[i].vec[random_var].x_ind;
            return false;
        }
    }
    return true;
}



int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    

    mt19937 gen(static_cast<unsigned>(time(nullptr)));
    int n = readInt(); 
    int m = readInt(); 

    std::vector<Line> form(m) ; 
    std::vector <int> x_perm(n); 

    for (int i = 0 ; i < m ; i++){
        Line stroka ; 
        for (int j = 0 ; j < 3 ; j++){
            int x = readInt();
            bool wh = readInt();
            stroka.vec.push_back({x-1, wh }); 
        }
        form[i] = stroka; 
    }

    const int MAX_TRIES = 1000000;   
    const int MAX_FLIPS = 3 * n;     
    

    for (int tries = 0; tries < MAX_TRIES; tries++) {

        fillingRandomXPermutation(x_perm);
        

        for (int flips = 0; flips < MAX_FLIPS; flips++) {
            if (isNormalPerm(form, x_perm)) {
                string ans;
                ans.reserve(n);
                for (int i = 0; i < n; i++) {
                    ans.push_back(x_perm[i] ? '1' : '0');
                }
                writeWord(ans.c_str());
                return 0;
            } else {
                changeX_Perm(x_perm);
            }
        }
    }



    return 0;
}

//1 _18 друзья 

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <random>
#include <limits>
#include <numbers>
#include <iomanip>
using namespace std;

bool norm(double coor_x, double coor_y, double r, double vec_x, double vec_y) {
    return (double)(vec_x - coor_x) * (vec_x - coor_x) + (double)(vec_y - coor_y) *(vec_y - coor_y) <= r * r;
}


int main() {
    const int SIZE = 10000000; 

    double coor_x1 , coor_y1 , r_1 ; std::cin >> coor_x1  >> coor_y1>> r_1 ; 
    double coor_x2 ,coor_y2,  r_2 ; std::cin >> coor_x2 >> coor_y2 >> r_2 ; 
    double coor_x3 ,coor_y3 , r_3 ; std::cin >> coor_x3 >> coor_y3 >> r_3; 

    int count = 0 ; 

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(-3.0, 3.0); 



    for ( int i = 0 ;i < SIZE; i++){
        double vec_x = dis(gen); 
        double vec_y = dis(gen); 
        // cout << vec_x << " " << vec_y << endl; 



        if (norm(coor_x1 , coor_y1 , r_1 , vec_x , vec_y ) && 
            norm (coor_x2 , coor_y2 , r_2 , vec_x , vec_y) && 
            norm (coor_x3 , coor_y3 , r_3, vec_x , vec_y )){
                count++; 
            }


    }

    double  area = 1.0 * count / SIZE *36.0; 
    std::cout << std::fixed << std::showpoint;
    std::cout << std::setprecision(6);
    std::cout << area << std::endl;
    

    // for ( auto el : vec){
    //     cout << el << std::endl; 
    // }
    return 0;
} 

// сумма расстояний 
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <random>
#include <limits>
#include <numbers>
#include <iomanip>
using namespace std;

bool norm(double coor_x, double coor_y, double r, double vec_x, double vec_y) {
    return (double)(vec_x - coor_x) * (vec_x - coor_x) + (double)(vec_y - coor_y) *(vec_y - coor_y) <= r * r;
}


int main() {
    const int SIZE = 10000000; 

    double coor_x1 , coor_y1 , r_1 ; std::cin >> coor_x1  >> coor_y1>> r_1 ; 
    double coor_x2 ,coor_y2,  r_2 ; std::cin >> coor_x2 >> coor_y2 >> r_2 ; 
    double coor_x3 ,coor_y3 , r_3 ; std::cin >> coor_x3 >> coor_y3 >> r_3; 

    int count = 0 ; 

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(-3.0, 3.0); 



    for ( int i = 0 ;i < SIZE; i++){
        double vec_x = dis(gen); 
        double vec_y = dis(gen); 
        // cout << vec_x << " " << vec_y << endl; 



        if (norm(coor_x1 , coor_y1 , r_1 , vec_x , vec_y ) && 
            norm (coor_x2 , coor_y2 , r_2 , vec_x , vec_y) && 
            norm (coor_x3 , coor_y3 , r_3, vec_x , vec_y )){
                count++; 
            }


    }

    double  area = 1.0 * count / SIZE *36.0; 
    std::cout << std::fixed << std::showpoint;
    std::cout << std::setprecision(6);
    std::cout << area << std::endl;
    

    // for ( auto el : vec){
    //     cout << el << std::endl; 
    // }
    return 0;
} 

// путь в случайном графе 
#include <iostream>
#include <vector>
#include <tuple>
#include "optimization.h"

using namespace std;
const long long INF = 1000000000000000000LL; 

int main() {

    int n = readInt(); 
    int m = readInt(); 
    int s = readInt(); 
    int t = readInt(); 
    vector<tuple<int,int,long long>> gr(m); 

    for(int i = 0; i < m; i++) {
        int u = readInt(); 
        int v = readInt(); 
        long long  w = readInt(); 
        gr.emplace_back(u, v, w);
    }

    vector<long long> dist(n + 1, INF);
    dist[s] = 0;


    for(int i = 0; i < n - 1; i++) {
        bool us = false;
        for(const auto &e: gr) {
            int u , v ; long long w ; 
            tie(u ,v , w) = e ; 

            if(dist[u] < INF ){
                if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                us = true;
                }
            }
        }
        if(!us) {
            break;
        }
    }

    if(dist[t] == INF) {
        writeInt(INF,'\n');
    } else {
        writeInt(dist[t],'\n');
    }

    return 0;
}


// оставное дерево 
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include "optimization.h"
using namespace std;

struct edge {
    int u , v , w ; 
    bool operator < (const edge &other) const {
        return w < other.w;
    }
}; 

struct DSU {
    vector <int> parent;    
    DSU(int n) : parent(n) {
        for(int i = 0; i < n; ++i)
            parent[i] = i;
    } 
    void make_set(int v) {
        parent[v] = v;
    }

    int find_set(int v) {
        if (v == parent[v])
            return v;
        return parent[v] = find_set(parent[v]);
    }

    void union_sets(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if (a != b)
            parent[b] = a;
    }
}; 

int main() {
    int n = readInt() , m = readInt();
    vector < edge > gr(n);
    for ( int i = 0 ; i< m ; i ++){
        int b = readInt() , e = readInt() , w = readInt();
        b--; e--; 
        gr.push_back({b , e , w});
    }
    int cost = 0 ; 
    sort(gr.begin() , gr.end());
    DSU dsu(n); 
    int edc = 0 ; 
    for ( const auto &x : gr){
        if (dsu.find_set(x.u) != dsu.find_set(x.v)){
            dsu.union_sets(x.u , x.v);
            if (x.w > 0){
                cost += x.w;
                if (++edc == n - 1)
                    break ; 
            }
        }
    }
    writeInt(cost);



    return 0;
}

// поиск цикла 
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std; 

bool dfs( int v , vector <vector < int> > &edges , int &cycle_begin , int &cycle_end, vector <int> &parents, vector <int> &color){
        color[v] = 1; 
        for (auto u : edges[v]){
            if ( color[u] == 0 ){
                parents[u] = v; 
                if (dfs( u , edges, cycle_begin , cycle_end , parents , color)){
                    return true; 
                }

            } else if (color[u] == 1 ) {
                cycle_begin = u ; 
                cycle_end = v; 
                return true; 

            }
        }
        color[v] = 2 ; 
        return false; 


}

void find_cycle( int  n , vector < vector <int> > &edges){
    vector <int> parents(n , -1) ;
    vector <int> color(n , 0); 
    int cycle_begin = -1 , cycle_end = -1; 

    for (int i = 0 ; i < n; i++) {
        if (color[i] == 0) {
            if (dfs( i , edges , cycle_begin , cycle_end , parents , color)) {
                break;
            }
        }
    }

    if (cycle_begin == -1) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
        vector<int> cycle;

        for (int v = cycle_end; v != cycle_begin; v = parents[v]) {
            cycle.push_back(v);
        }
        cycle.push_back(cycle_begin); 
        reverse(cycle.begin(), cycle.end()); 
        for (int v : cycle) {
            cout << v + 1 << " "; 
        }
        cout << endl; 
    }

}


int main() {
    int n , m ; cin >> n >> m ; 

    vector <vector < int > > edges(n) ; 

    for ( int i = 0;i < m ;i++){
        int f , t ; cin >> f >> t ; 
        f--; t--; 
        edges[f].push_back(t) ; 
    }
    find_cycle(n , edges); 



    // for ( int i = 0 ;i < n ;i++){
    //     for ( auto el : edges[i]){
    //         cout << i << " " << el << endl; 
    //     }
    // }
    return 0;
}

//2 -sat 
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <set>
#include <stack>
#include "optimization.h"
using namespace std;

vector <int> mark ; 
stack <int> st ; 
vector <vector <int > > gr; 
vector <vector <int > > obr_gr; 
vector <int > comp ;

// дфс для того , чтобы заполнить стэк значениями - просто получается топсорт мы сделалми 
void dfs(int v , vector <vector <int> >&gr ){
    if ( mark[v]) return ; 
    mark[v] = 1; 
    for ( auto u : gr[v]){
        dfs(u , gr);
    }
    st.push(v); 
}
// этот дфс он проходит по обратным ребрам , для того , чтобы красить граф в определнные компоненты 
void dfs2(int v , vector<vector <int> >&obr_gr , int cc , vector<int> &comp){
    comp[v] = cc ; 
    for (auto u : obr_gr[v]){
        if (comp[u] == 0)
            dfs2(u , obr_gr , cc , comp ); 
    }

}

int main() {
while (!isEof()){
    int n = readInt(); 
    int m = readInt();
    if (n == 1 and m == 0 ){
        writeInt(1,'\n'); 
        continue;
    }
    gr.resize(2*n);  
    obr_gr.resize(2*n);  
    mark.assign(2 * n, 0);
    comp.assign(2 * n, 0);

    for (int i = 0; i < m  ; i++){ 
        int i_1  = readInt(); int e_1  = readInt(); int  i_2 = readInt();  int e_2 = readInt();


        int u_in = 2* i_1 + (1- e_1) ; 
        int v_in = 2 * i_2 + (1 - e_2);    
        int u_out = 2 * i_2 + e_2   ; 
        int v_out = 2* i_1 + e_1 ; 

        gr[v_in].push_back(v_out);
        obr_gr[v_out].push_back(v_in);

        gr[u_in].push_back(u_out);
        obr_gr[u_out].push_back(u_in);
    }
    // вызываемся от каждой вершины 
    for (int i = 0 ; i < 2*n ; i++){
        dfs(i, gr); 
    }
    // подсчитываем комопненты связанности 
    int cc = 0 ;
    while ( !st.empty()){
        int v = st.top(); 
        st.pop(); 
        if (comp[v] == 0) { // только в том случае , когда у нас не покрашена компонента - вызываем дфс от нее 
            dfs2(v ,obr_gr , ++cc , comp); 
        }
    }


    int ans[n]; 
    for ( int v= 0 ; v < n  ;v++){
        if (comp[2*v] >  comp[2*v+1]){  
            ans[v] = 0 ; 
        }else {
            ans[v] = 1; 
        }
    }

    for ( int i = 0 ; i < n ; i++){
        writeInt(ans[i]); 
    }
    writeChar('\n'); 


    gr.clear();
    obr_gr.clear();
    comp.clear();
    mark.clear();

}    
return 0;
}

// расстояние между вершинами 



#include <iostream>
#include <vector>
#include <set>
#include <climits> 
#include "optimization.h"
using namespace std;

int djestra(int s , int t , vector <vector <pair<int , int> > > &gr){
    vector <int> dist(gr.size() ,INT_MAX); 
    set< pair<int, int> > se ; 
    se.insert(make_pair(0 , s)); 
    dist[s] = 0 ;

    while (!se.empty()){
        int u = se.begin() -> second ; 
        se.erase(se.begin()); 

        for ( const auto &x : gr[u] ){
            int v = x.first ; 
            int we = x.second ; 
            if (dist[v] > dist[u] + we   ) {
                se.erase(make_pair(dist[u], u)); 
                dist[v] = dist[u] + we ;
                se.insert(make_pair(dist[v] , v)); 
            }
        }
    }
    if (dist[t] == INT_MAX){
        return -1; 
    } else {
        return dist[t]; 
    }
}

int main() {
    int n = readInt(); 
    int m = readInt(); 
    int s = readInt(); s--; 
    int t = readInt(); t--; 
    vector <vector <pair <int , int > > > gr(n) ;


    for (int i = 0 ; i < m ; i++ ){
        int b = readInt() ; b--; 
        int e = readInt() ; e--; 
        int w = readInt() ; 
        gr[b].emplace_back(make_pair (e,w )); 
        gr[e].emplace_back(make_pair(b , w)); 
    }
    int ans = djestra(s , t , gr); 
    writeInt(ans); 



    return 0;
}

// диметр графа 
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;
void relax(int &a  , int b ) {a = min(a , b); }

int main() {
    //read 
    int n  ; cin >> n ; 
    vector <vector <int > > gr(n , vector <int> (n , 0)); 
    for (int i = 0 ; i < n ;i++){
        for ( int j = 0 ; j < n ;j++){
            int temp ; cin >> temp ; 
            if (temp == -1) {
                gr[i][j] = 10000; 
            }else {
                gr[i][j] = temp;        
            }
        }
    }
    for (int k = 0 ; k < n ;k++){
        for ( int i = 0 ; i < n ;i++){
            for ( int j = 0 ;j  < n ;j++){
                relax(gr[i][j] , gr[k][j] + gr[i][k]); 
            }
        }
    }
    int dd = 0 ; 
    int mm = 10000 ; 
    for ( int i = 0 ; i < n ;i++){
        int e = 0 ; 
        for ( int j = 0 ; j < n ;j++){
            if ( i != j && gr[i][j] < 10000){
                e = max(e , gr[i][j]); 
            }
        }
        mm =min( mm , e); 
        dd = max(dd , e);
    }
    cout << dd << "\n";
    cout << mm << "\n";
    return 0;
}

// ближе к предкам 
#include <iostream>
#include <vector>
#include <string>
#include "optimization.h"
#include <unordered_map>
using namespace std;
struct DSU {
    vector<int> p;
    vector<int> sz;
    int m ; 
    DSU(int n) : p(n), sz(n,1 ) , m(1) {

        for (int i = 0; i < n; i++) {
            p[i] = i;
        }
    }

    int find(int v) { return p[v] == v ? v : p[v] = find(p[v]); }
    // int find(int v) {
    //     if (p[v] == v) return v;
    //     return p[v] = find(p[v]);
    // }
    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return;
        if (sz[a] < sz[b]) swap(a, b);
        p[b] = a;
        sz[a] += sz[b];
        m = max(m , sz[a]);
    }  
};

int main() {

    int t  = readInt() ; 
    while (t --){
        int n = readInt() ;
        vector <int> p(n-1)  , q(n-1) ,res; 
        for (int i = 0 ; i < n-1 ; i++){
            p[i] = readInt()  ; 
        }
        DSU dsu(n) ; 
        for (int i = 0 ; i < n-1 ; i++){
            q[i] = readInt()  ; 
        }
        for (auto x: q){
            dsu.unite(x, p[x-1]) ;
            res.push_back(dsu.m) ;
        }
        for (auto x: res){
            writeInt(x) ;
            writeChar(' ') ;
        }
        writeChar('\n') ;
    }

    return 0;
} 

//кодирование 

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <string>

using namespace std;
int main() {
    int n ,m ; cin >> n >> m ; 
    std::unordered_map< std::string, char> um;
    

    for (int i = 0;  i < n ; ++i) {
        char l; cin >>    l;
        cin.ignore( 2); 
        string cc;cin >> cc;
        um[cc]= l;
    }
    string obr; cin >> obr;

    string br, temp;
    for (char c : obr) {
        temp += c;
        if (um.count(temp)) {
            br += um[temp];
            temp.clear();
        }
    }
    cout << br ; 

    return 0;
}
// декодировние - хафман 

#include <vector>
#include <iostream>
#include <queue> 
#include <string> 
#include <unordered_map>
using namespace std; 


struct MinHeapNode { 
	char data; 
	int countt; 

	MinHeapNode *left, *right; 

	MinHeapNode(char data_, int freq_): left(NULL) , right(NULL) , data(data_) , countt(freq_) {} 
}; 


struct comparator { 
	bool operator()(MinHeapNode* l, MinHeapNode* r) {  return (l->countt > r->countt); } 
}; 


void recCode(struct MinHeapNode* root, string str , unordered_map < char, string > &um )  { 
	if (!root)  return; 

	if (root->data != '\0') 
        um[root->data] = str; 


	recCode(root->left, str + "0" , um ); 
	recCode(root->right, str + "1" , um ); 
} 


unordered_map <char , string  >  HuffmanCodes(vector <char> data, vector <int> &countt) { 
	struct MinHeapNode *left, *right, *top; 

	priority_queue<MinHeapNode*, vector<MinHeapNode*>, comparator>  minHeap; 

	for (int i = 0; i < data.size(); ++i) {
		minHeap.push(new MinHeapNode(data[i], countt[i])); 
    }

	while (minHeap.size() > 1) {  
		auto left = minHeap.top();  minHeap.pop(); 

		auto right = minHeap.top(); minHeap.pop(); 

		auto  top = new MinHeapNode('\0', left->countt + right->countt); 
		top->left = left;  top->right = right; 
		minHeap.push(top); 
	} 
    unordered_map <char ,string  > um ;  
	recCode(minHeap.top(), "" , um ); 
    return um ; 
} 

int main() { 
    string s ; cin >> s; 

    unordered_map<char , int> um_ ; 
    for ( auto c : s){
        um_[c]++;
    }

    vector <char> arr ; 
    vector <int> countt ; 
    for ( auto [f,e] : um_){
        arr.push_back(f); 
        countt.push_back(e); 
    }


    
	unordered_map<char , string > um = HuffmanCodes(arr, countt); 
    string a = ""; 
    for (auto el : s){
        a += um[el] ; 
    }


    if (um_.size() == 1) {
        char c2 = arr[0];
        string s2(s.size(), '0');  
        cout << 1 << " " << s2.size() << '\n';
        cout << c2 << ": " << 0 << '\n';
        cout << s2 << '\n';
        return 0;
    }



    cout << um_.size() << " " << a.size() << "\n"; 
    for (auto [cc , ss] : um){
        cout << cc << ": " << ss << '\n'; 
    }
    cout << a << '\n'; 


	return 0; 
} 



// золотой песок 

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <random>
#include <limits>
#include <numbers>
#include <iomanip>
#include <algorithm>
using namespace std;



int main() {
    int n , m ; cin >> n >> m ; 
    vector <pair<float , float > > vp ; 
    for (int i = 0 ; i < n ;i++){
        float v , w ; cin>> v >> w ; 
        vp.emplace_back(std::make_pair(v , w)) ; 
    }
    sort(vp.begin() , vp.end() , [](pair <float , float> a , pair <float, float >  b) {return (a.first / a.second  > b.first / b.second) ; } ) ; 

    float total = 0.0 ; 
    for ( int i = 0 ; i< n ; i++){
        if (m >= vp[i].second) {
            total += (float)vp[i].first ; 
            m-= vp[i].second; 
        }else {
            float dr = m / vp[i].second ; 
            total += (float)vp[i].first * dr ; 
            break ;
        }
    }

    std::cout << std::fixed << std::showpoint;
    std::cout << std::setprecision(3);
    std::cout << total << std::endl;
    




    return 0;
}