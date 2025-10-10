// такс . смори . вот задача , сможешь ее решить использукя такие идеи как эйлеров обход, чтобы получатьбыстро сумму в поддереве
// такуже фенвика , и дфс для поиска минимума

#include <iostream> 
#include <vector>
#include <algorithm>
#include <cmath>
#include <random>
#include <unordered_map>
#include <functional>
#include <numeric>


using namespace std;

using ll = long long;
const int MAXN = 200005;

int n;
vector<pair<int, int>> tree[MAXN];
int parent[MAXN], depth[MAXN];
ll dist_to_root[MAXN];

void dfs(int v, int p) {
    for (auto [to, w] : tree[v]) {
        if (to == p) continue;
        parent[to] = v;
        depth[to] = depth[v] + 1;
        dist_to_root[to] = dist_to_root[v] + w;
        dfs(to, v);
    }
}

// Binary lifting for LCA
const int LOG = 20;
int up[MAXN][LOG];

void preprocess_lca() {
    for (int v = 1; v <= n; ++v) up[v][0] = parent[v];
    for (int j = 1; j < LOG; ++j)
        for (int v = 1; v <= n; ++v)
            up[v][j] = up[up[v][j - 1]][j - 1];
}

int lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    for (int j = LOG - 1; j >= 0; --j)
        if (depth[u] - (1 << j) >= depth[v])
            u = up[u][j];
    if (u == v) return u;
    for (int j = LOG - 1; j >= 0; --j)
        if (up[u][j] != up[v][j]) {
            u = up[u][j];
            v = up[v][j];
        }
    return parent[u];
}

ll get_dist(int u, int v) {
    int a = lca(u, v);
    return dist_to_root[u] + dist_to_root[v] - 2 * dist_to_root[a];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 2; i <= n; ++i) {
        int p, d;
        cin >> p >> d;
        tree[p].emplace_back(i, d);
        tree[i].emplace_back(p, d);
    }

    parent[1] = 1;
    dfs(1, -1);
    preprocess_lca();

    vector<int> active;
    ll total_sum = 0;

    for (int k = 1; k <= n; ++k) {
        active.push_back(k);

        // Binary search to find best center (brute force, but fast enough)
        ll best_sum = LLONG_MAX;
        for (int v : active) {
            ll sum = 0;
            for (int u : active)
                sum += get_dist(u, v);
            best_sum = min(best_sum, sum);
        }
        cout << best_sum << '\n';
    }
    return 0;
}
