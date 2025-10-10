#include <iostream>
#include <vector>
#include <queue>
#include <string> 
#include <algorithm>
#include "../optimization.h"

using namespace std;

void print(std::vector<int> &dp , int n ) {
    for (int i  = 0; i < n; i++) {
        if (dp[i] == 1) {
            writeWord("FIRST\n");
            // cout << "FIRST\n";
        } else if  (dp[i] == 0) {
            writeWord("SECOND\n");
            // cout << "SECOND\n";
        } else {
            writeWord("DRAW\n");
            // cout  << "DRAW\n";
        }
    }
}

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(0);

    int n, m;
    while (/*cin >> n  >> m*/ n = readInt() , m = readInt() ) {
        vector<vector< int> > frd(n) , bcd(n);
        vector<int> deg(n,  0);

        for (int i = 0; i < m ;  i++) {
            // int a, b; cin >>  a >> b; a--; b--;
            int a = readInt() - 1 , b = readInt() - 1;
            frd[a].push_back(b);// туда 
            bcd[b].push_back(a);// обратно 
            deg[a]++; // увеличиваем степени вершины 
        } 

        vector<int> temp_deg =  deg;
        vector<int> dp(n, 2 ); //  2 - DRAW, 0 - SECOND, 1 - FIRST

        queue<int> q; // и очередь

        for (int i = 0;  i < n;  i++) { // добавляем все вершины , которые являются листьями
            if (deg[i]  == 0) {
                dp[i] = 0;
                q.push(i);
            }
        }

        while ( !q.empty() ) { // пока у нас очередь не пуста 
            int u = q.front(); q.pop(); // берем элемент из очереди 


            for (int v : bcd[ u]) { // пробегаемся по обратным ребрам u 
                if (dp[v] != 2 ) continue; // если мы уже посетили вершину , то пропускаем
                if (dp[u ] == 0) {
                    dp[v] =  1;
                    q.push( v);
                } else if ( dp[u] == 1) {
                    temp_deg[v]--; 
                    if (temp_deg[v] == 0) {
                        dp[v] = 0;
                        q.push(v);
                    }
                }
            }
        }
        print(dp, n);
    }

    return 0;
}