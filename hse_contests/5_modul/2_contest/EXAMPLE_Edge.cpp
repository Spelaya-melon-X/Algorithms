#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

int N , M , C , F ; 

struct Edge {
    int a , b , f ,c ; 
    int next; 
}; 
vector<Edge> edges;
vector<int> head; 



void add(int a, int b, int c) {
    edges.push_back({a, b, 0, c, head[a]});
    head[a] = edges.size() - 1;

    edges.push_back({b, a, 0, 0, head[b]});
    head[b] = edges.size() - 1;
}

void print_graph() {
    for (int v = 0; v < N; v++) {
        cout << v << ": ";
        for (int i = head[v]; i != -1; i = edges[i].next) {
            if (edges[i].c > 0) {
                cout << "-> " << edges[i].b << " (cap=" << edges[i].c << ") ";
            }
        }
        cout << "\n";
    }
}


int main() {
    std::cin>> N >> M >> C >> F; C--, F--; 
    head.resize(N, -1) ; 
    for (int i = 0 ; i < M ; i++) {
        int a , b ; cin >> a >> b ;  a-- ; b-- ; 
        add(a ,b ,1) ;
    }

    print_graph()  ; 

    return 0;
}