#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <unordered_map>

using namespace std;
const int n = 4; 

struct edge{
    int to , weight ; 
}
vector <set <int > > g(n)  = {{1 2,4},{ 3 ,4 } ,{1,2}}; 
vector <edge> answer(n); 


void dfs(int v ){
    if(!g[v].empty()){
        int  x = *g[v].begin(); 
        g[v].erase() ,  g[x].erase(); 
        dfs(x); 
        answer.push_back(edge(v , x)); 
    }
}

int main() {
    dfs()
    
    return 0;
}