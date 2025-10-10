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

    void dfs(int v , vector <vector <int> >&gr ){
        if ( mark[v]) return ; 
        mark[v] = 1; 
        for ( auto u : gr[v]){
            dfs(u , gr);
        }
        st.push(v); 
    }

    void dfs2(int v , vector<vector <int> >&obr_gr , int cc , vector<int> &comp){
        comp[v] = cc ; 
        for (auto u : obr_gr[v]){
            if (comp[u] == 0)
                dfs2(u , obr_gr , cc , comp ); 
        }

    }

int main() {

    int n = readInt(); 
    int m = readInt();
    char colors[1000]; 
    readWord(colors); 

    gr.resize(2*n);  
    obr_gr.resize(2*n);  
    mark.assign(2 * n, 0);
    comp.assign(2 * n, 0);
    vector<pair<char, char>> allowed(n);

    for (int i = 0; i < n; ++i) {
        if (colors[i] == 'R') allowed[i] = {'G', 'B'};
        else if (colors[i] == 'G') allowed[i] = {'R', 'B'};
        else allowed[i] = {'R', 'G'}; 
    }


    for (int i = 0; i < m  ; i++){ 
        int u  = readInt() - 1; 
        int v  = readInt()-1; 

        char u_color1 = allowed[u].first;
        char u_color2 = allowed[u].second;
        char v_color1 = allowed[v].first;
        char v_color2 = allowed[v].second;

        if (u_color1 == v_color1) {
            gr[2 * u].push_back(2 * v + 1);     
            obr_gr[2 * v + 1].push_back(2 * u);

            gr[2 * v].push_back(2 * u + 1);     
            obr_gr[2 * u + 1].push_back(2 * v);
        }

        if (u_color1 == v_color2) {
            gr[2 * u].push_back(2 * v);         
            obr_gr[2 * v].push_back(2 * u);

            gr[2 * v + 1].push_back(2 * u + 1); 
            obr_gr[2 * u + 1].push_back(2 * v + 1);
        }
        if (u_color2 == v_color1) {
            gr[2 * u + 1].push_back(2 * v + 1); 
            obr_gr[2 * v + 1].push_back(2 * u + 1);
            gr[2 * v].push_back(2 * u);
            obr_gr[2 * u].push_back(2 * v);
        }
        if (u_color2 == v_color2) {
            gr[2 * u + 1].push_back(2 * v);     
            obr_gr[2 * v].push_back(2 * u + 1);

            gr[2 * v + 1].push_back(2 * u);     
            obr_gr[2 * u].push_back(2 * v + 1);
    }




    }
    
    for (int i = 0 ; i < 2*n ; i++){
        if ( !mark[i]){
            dfs(i, gr); 
        }
    }

    int cc = 0 ;
    while ( !st.empty()){
        int v = st.top(); 
        st.pop(); 
        if (comp[v] == 0) {
            dfs2(v ,obr_gr , ++cc , comp); 
        }
    }

    string result(n, ' ');
    bool poss = true;
    for (int i = 0; i < n; ++i) {
        int v_0 = 2 * i;     
        int v_1 = 2 * i + 1; 
        if (comp[v_0] == comp[v_1]) {
            poss = false;
            break;
        }

        result[i] = (comp[v_0] > comp[v_1]) ? allowed[i].first : allowed[i].second;
    }

    if (!poss) {
        writeWord("Impossible\n");
    } else {
        for (char c : result) writeChar(c);
        writeChar('\n');
    }

    
    return 0;
}