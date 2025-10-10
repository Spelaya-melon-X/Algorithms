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