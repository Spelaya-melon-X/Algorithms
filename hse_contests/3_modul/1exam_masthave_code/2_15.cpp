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