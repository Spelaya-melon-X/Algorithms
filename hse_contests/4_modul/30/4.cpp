// пожалуйста реши , я уже задолбался эти запросы ***** писать... воообще полное **** этот промп гпт контес 

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


static const int MAXN = 100000;
int n, q;

// Список смежности: (to, weight)
vector<pair<int,int>> adj[MAXN+1];

// Для подъёма по дереву (LCA-двойное)
int parentUp[MAXN+1][18];
int depthArr[MAXN+1];

// Вес ребра до родителя
int w_to_par[MAXN+1];

// Для HLD
int sz[MAXN+1], heavy[MAXN+1];
int head[MAXN+1], pos[MAXN+1];
int curPos;

// Fenwick (1..n)
struct Fenw {
    int n;
    vector<int> fenw;
    Fenw(int _n=0) { init(_n); }
    void init(int _n) {
        n = _n;
        fenw.assign(n+1, 0);
    }
    // увеличить на delta в точке i
    void update(int i, int delta) {
        for (; i <= n; i += i & -i) {
            fenw[i] += delta;
        }
    }
    // префиксная сумма [1..i]
    int sum(int i) const {
        int s = 0;
        for (; i > 0; i -= i & -i) {
            s += fenw[i];
        }
        return s;
    }
};

// LCA: поднять v на dist уровней
int lift(int v, int dist) {
    for(int i = 0; i < 18; i++) {
        if (dist & (1<<i)) {
            v = parentUp[v][i];
            if (v == 0) break;
        }
    }
    return v;
}

// LCA на основе двойного подъёма
int LCA(int a, int b) {
    if (depthArr[a] < depthArr[b]) 
        swap(a,b);
    // поднимем a, чтобы depth[a] == depth[b]
    a = lift(a, depthArr[a] - depthArr[b]);
    if (a == b) return a;
    for(int i = 17; i >= 0; i--) {
        if (parentUp[a][i] != parentUp[b][i]) {
            a = parentUp[a][i];
            b = parentUp[b][i];
        }
    }
    return parentUp[a][0];
}

// Первый DFS: вычисляем parentUp[v][0], depthArr[v], sz[v], heavy[v], w_to_par[v]
void dfs1(int v, int p) {
    parentUp[v][0] = p;
    sz[v] = 1;
    heavy[v] = 0;
    for (auto &edge : adj[v]) {
        int to = edge.first;
        int w  = edge.second;
        if (to == p) continue;
        depthArr[to] = depthArr[v] + 1;
        w_to_par[to] = w;
        dfs1(to, v);
        if (sz[to] > sz[ heavy[v] ]) {
            heavy[v] = to;
        }
        sz[v] += sz[to];
    }
}

// Вторая стадия HLD: выставляем head[] и pos[]
void decompose(int v, int h) {
    head[v] = h;
    pos[v] = ++curPos;
    if (heavy[v] != 0) {
        // «протягиваем» тяжёлое ребро дальше в ту же цепочку
        decompose(heavy[v], h);
    }
    for (auto &edge : adj[v]) {
        int to = edge.first;
        if (to == parentUp[v][0] || to == heavy[v]) continue;
        // новая цепочка с головой = себя
        decompose(to, to);
    }
}

// Fenwick-дерево по позициям HLD
Fenw fenw;

// Сумма «помеченных» рёбер (ребро привязано к child) на пути x -> ancestor (не включая ancestor)
int query_up(int x, int anc) {
    int res = 0;
    while (head[x] != head[anc]) {
        // в Fenwick всё «ребро» child→parent отмечено именно в pos[child].
        // берем всё от головы chain до x
        int h = head[x];
        res += fenw.sum(pos[x]) - fenw.sum(pos[h] - 1);
        x = parentUp[h][0];
    }
    // теперь x и anc в одной цепочке; надо взять вершины от anc+1 до x (не включая anc)
    if (x != anc) {
        res += fenw.sum(pos[x]) - fenw.sum(pos[anc]);
    }
    return res;
}

struct EdgeNode {
    int w, v;
    bool operator< (EdgeNode const& o) const {
        return w < o.w;
    }
};

struct Query {
    int k, v, u, id;
    bool operator< (Query const& o) const {
        return k < o.k;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    // читаем n-1 рёбер
    for (int i = 1; i <= n; i++) {
        adj[i].clear();
    }
    for (int i = 0; i < n-1; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        adj[a].push_back({b,w});
        adj[b].push_back({a,w});
    }

    // 1) Первый DFS от корня=1
    depthArr[1] = 0;
    w_to_par[1] = 0;    // у корня «ребра до родителя» нет
    dfs1(1, 0);

    // 2) Заполним таблицу parentUp для LCA за O(n log n)
    for(int j = 1; j < 18; j++){
        for(int v = 1; v <= n; v++){
            int mid = parentUp[v][j-1];
            parentUp[v][j] = mid ? parentUp[mid][j-1] : 0;
        }
    }

    // 3) HLD – вторая стадия
    curPos = 0;
    decompose(1, 1);

    // 4) Собираем вершины (всех, кроме 1) с весом ребра до parent-а
    vector<EdgeNode> vec_nodes;
    vec_nodes.reserve(n);
    for (int v = 2; v <= n; v++) {
        vec_nodes.push_back({ w_to_par[v], v });
    }
    sort(vec_nodes.begin(), vec_nodes.end());

    // 5) Fenwick по n позициям
    fenw.init(n);

    // 6) Читаем запросы
    cin >> q;
    vector<Query> qs(q);
    for(int i = 0; i < q; i++){
        int v,u,k;
        cin >> v >> u >> k;
        qs[i] = {k, v, u, i};
    }
    sort(qs.begin(), qs.end());

    vector<int> ans(q, 0);
    int ptr = 0;  
    // ptr пробегает по vec_nodes, добавляя «разрешённые» (<= current k)

    for (auto &Q : qs) {
        int K = Q.k;
        // пока есть вершины с w_to_par <= K, помечаем их в Fenwick
        while (ptr < (int)vec_nodes.size() && vec_nodes[ptr].w <= K) {
            int node = vec_nodes[ptr].v;
            fenw.update(pos[node], 1);
            ptr++;
        }
        int v = Q.v, u = Q.u;
        int w = LCA(v,u);
        int cnt = query_up(v, w) + query_up(u, w);
        ans[Q.id] = cnt;
    }

    // 7) Выводим результаты в исходном порядке
    for (int i = 0; i < q; i++) {
        cout << ans[i] << "\n";
    }
    return 0;
}
