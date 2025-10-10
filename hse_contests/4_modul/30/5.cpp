// такс , смотир , можешь ершить данную задачу на С++ используя следующие идеи : испльзовиниеLCA с помощью поднятия по степеням , также Heavy-Light Decomposition для быстрого обновления/запроса на путях также Fenwick

// посмотри на прошлый запрос , найди увязвимсоти и реши их 
#include <iostream> 
#include <vector>
#include <algorithm>
#include <cmath>
#include <random>
#include <functional>
#include <numeric>
#include <cstring>
#include <stack>

using namespace std;

const int MAXN = 100000;
const int LOGN = 17;

int N, Q;
vector<pair<int,int>> adj[MAXN+1];
int parentArr[MAXN+1], depthArr[MAXN+1];
int up[MAXN+1][LOGN+1];
int inTime[MAXN+1], outTime[MAXN+1], timer;

// DFS: заполняем parentArr, depthArr, up[ ][ ], а также inTime и outTime (Эйлерово время)
void dfs(int u, int p) {
    parentArr[u] = p;
    depthArr[u] = (p == 0 ? 0 : depthArr[p] + 1);
    up[u][0] = (p == 0 ? u : p);
    for(int k = 1; k <= LOGN; k++) {
        up[u][k] = up[ up[u][k-1] ][k-1];
    }
    inTime[u] = ++timer;
    for(auto &pr : adj[u]) {
        int v = pr.first;
        if(v == p) continue;
        dfs(v, u);
    }
    outTime[u] = timer;
}

// Быстрая LCA на основе табличного подъёма
int lca(int u, int v) {
    if(depthArr[u] < depthArr[v]) swap(u, v);
    int diff = depthArr[u] - depthArr[v];
    for(int k = LOGN; k >= 0; k--) {
        if(diff & (1 << k)) {
            u = up[u][k];
        }
    }
    if(u == v) return u;
    for(int k = LOGN; k >= 0; k--) {
        if(up[u][k] != up[v][k]) {
            u = up[u][k];
            v = up[v][k];
        }
    }
    return parentArr[u];
}

// Fenwick-дерево для точечных обновлений и префиксных (а значит, и диапазонных) сумм
struct BIT {
    int n;
    vector<int> bit;
    BIT(int _n): n(_n), bit(n+1, 0) {}
    // добавить v в точку idx
    void update(int idx, int v) {
        for(int i = idx; i <= n; i += i & -i)
            bit[i] += v;
    }
    // префиксная сумма [1..idx]
    int query(int idx) {
        int res = 0;
        for(int i = idx; i > 0; i -= i & -i)
            res += bit[i];
        return res;
    }
    // сумма по диапазону [l..r]
    int rangeQuery(int l, int r) {
        if(l > r) return 0;
        return query(r) - query(l-1);
    }
};

struct Event {
    int w;
    int u, v;
    int delta;
    bool operator<(const Event &o) const {
        return w < o.w;
    }
};

struct EdgeInfo {
    int w;
    int child;
    bool operator<(const EdgeInfo &o) const {
        return w < o.w;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    vector<tuple<int,int,int>> edgesInput(N-1);
    for(int i = 0; i < N-1; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        edgesInput[i] = make_tuple(a, b, w);
        adj[a].push_back({b, w});
        adj[b].push_back({a, w});
    }

    // Делаем DFS от корня 1, чтобы получить parentArr, depthArr, up[ ][ ], inTime / outTime
    timer = 0;
    dfs(1, 0);

    // Собираем информацию об рёбрах: для каждого ребра определяем, какой узел — «child»
    vector<EdgeInfo> edges;
    edges.reserve(N-1);
    for(auto &e : edgesInput) {
        int u, v, w;
        tie(u, v, w) = e;
        // если parentArr[u] == v, значит ребро (v→u), child = u, иначе child = v.
        int child = (parentArr[u] == v ? u : v);
        edges.push_back({w, child});
    }
    sort(edges.begin(), edges.end());

    cin >> Q;
    vector<Event> events;
    events.reserve(2*Q);
    // Для каждого запроса (u, v, Wmin, Wmax) мы заведём два события:
    //  1) при w = Wmin: добавляем +1 к «разности» по дереву на пути u–v
    //  2) при w = Wmax+1: добавляем −1 к той же разности (чтобы на [Wmin..Wmax] счётчик был активен)
    for(int i = 0; i < Q; i++) {
        int u, v, wmin, wmax;
        cin >> u >> v >> wmin >> wmax;
        events.push_back({wmin, u, v, +1});
        events.push_back({wmax + 1, u, v, -1});
    }
    sort(events.begin(), events.end());

    BIT bit(N);
    long long answer = 0;
    int ev = 0, totalEvents = (int)events.size();
    int ei = 0, totalEdges = (int)edges.size();

    // Sweep: проходим по всем разным весам rёбер в порядке возрастания
    // и одновременно «активируем»/«деактивируем» запросы по их событиям.
    while(ei < totalEdges) {
        int curW = edges[ei].w;
        // Активируем все события с w <= curW
        while(ev < totalEvents && events[ev].w <= curW) {
            int u = events[ev].u;
            int v = events[ev].v;
            int delta = events[ev].delta;
            int w = lca(u, v);
            // стандартная техника «разности по дереву»:
            //   +delta в inTime[u], +delta в inTime[v], и −2·delta в inTime[LCA].
            bit.update(inTime[u], delta);
            bit.update(inTime[v], delta);
            bit.update(inTime[w], -2 * delta);
            ev++;
        }
        // Теперь все запросы с Wmin ≤ curW ≤ Wmax «активны».
        // Посчитаем, сколько из них проходят через каждое ребро weight = curW.
        // Для ребра, ориентированного от parentArr[c]→c, величина
        //   sumSubtree = bit.rangeQuery(inTime[c], outTime[c])
        // равна числу активных путей, которые «проходят» через это ребро.
        while(ei < totalEdges && edges[ei].w == curW) {
            int c = edges[ei].child;
            int cnt = bit.rangeQuery(inTime[c], outTime[c]);
            if(cnt > 0) answer++;
            ei++;
        }
    }

    cout << answer << "\n";
    return 0;
}
