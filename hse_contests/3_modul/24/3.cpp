#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

vector<vector<int>> gr;
vector<long long> ans;
vector<bool> used;

int dfs_size(int v, int p) {
    int size = 1;
    for (int u : gr[v])
        if (u != p && !used[u])
            size += dfs_size(u, v);
    return size;
}

int find_centroid(int v, int p, int total_size) {
    for (int u : gr[v])
        if (u != p && !used[u] && dfs_size(u, -1) > total_size/2)
            return find_centroid(u, v, total_size);
    return v;
}

void dfs_dist(int v, int p, int depth, unordered_map<int, int>& dists) {
    dists[depth]++;
    for (int u : gr[v])
        if (u != p && !used[u])
            dfs_dist(u, v, depth + 1, dists);
}

void process_centroid(int v) {
    int total = dfs_size(v, -1);
    int centr = find_centroid(v, -1, total);
    used[centr] = true;

    unordered_map<int, int> global_cnt;
    global_cnt[0] = 1; // Сам центроид

    for (int u : gr[centr]) {
        if (!used[u]) {
            unordered_map<int, int> subtree_cnt;
            dfs_dist(u, centr, 1, subtree_cnt);

            // Учет путей внутри поддерева
            for (auto& [d, cnt] : subtree_cnt)
                if (d < ans.size())
                    ans[d] += cnt;

            // Комбинация с глобальными путями
            for (auto& [d1, cnt1] : subtree_cnt)
                for (auto& [d2, cnt2] : global_cnt)
                    if (d1 + d2 < ans.size())
                        ans[d1 + d2] += cnt1 * cnt2;

            // Добавляем в глобальный счетчик
            for (auto& [d, cnt] : subtree_cnt)
                global_cnt[d] += cnt;
        }
    }

    // Обработка дочерних поддеревьев
    for (int u : gr[centr])
        if (!used[u])
            process_centroid(u);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    gr.resize(n);
    ans.resize(n, 0);
    used.resize(n, false);

    for (int i = 1; i < n; ++i) {
        int p; cin >> p;
        gr[p].push_back(i);
        gr[i].push_back(p);
    }

    process_centroid(0);

    // Корректировка результатов
    for (int k = 1; k < n; ++k)
        cout << ans[k]/2 << " ";

    return 0;
}