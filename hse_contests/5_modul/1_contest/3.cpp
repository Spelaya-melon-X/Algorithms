#include <iostream>
#include <vector>
#include <string>
#include <set>
using namespace std;

int N, M, A, B;
set<pair<int,int> > bad; 
vector<vector<int> > graph;
vector<bool> used;
vector<int> pa;


bool cell(int i, int j) {
    return (0 <= i && i < N && 0 <= j && j < M && bad.count({i, j}));
}


bool dfs(int v) {
    if (used[v]) return false;
    used[v] = true;
    for (auto u : graph[v]) {
        if (pa[u] == -1 || dfs(pa[u])) {
            pa[u] = v;
            return true;
        }
    }
    return false;
}


int id(int i, int j) { 
    return i * M + j; 
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M >> A >> B;
    graph.resize(N * M);
    pa.assign(N * M, -1);
    used.assign(N * M, false);

    for (int i = 0; i < N; i++) {
        string row;
        cin >> row;
        for (int j = 0; j < M; j++) {
            if (row[j] == '*')
                bad.insert({i, j});
        }
    }

    if (B >= 2 * A) {
        cout << 1LL * A * bad.size() << "\n";
        return 0;
    }


    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    for (auto [i, j] : bad) {
        if ((i + j) % 2 == 0) { 
            for (int k = 0; k < 4; k++) {
                int ni = i + dx[k], nj = j + dy[k];
                if (cell(ni, nj))
                    graph[id(i, j)].push_back(id(ni, nj));
            }
        }
    }

    int matching = 0;
    for (auto [i, j] : bad) {
        if ((i + j) % 2 == 0) {
            fill(used.begin(), used.end(), false);
            if (dfs(id(i, j)))
                matching++;
        }
    }
    long long ans = 1LL * matching * B + 1LL * (bad.size() - 2 * matching) * A;
    cout << ans << "\n";
    return 0;
}


