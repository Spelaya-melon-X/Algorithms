#include "optimization.h"
#include <vector>
#include <map>
#include <algorithm>
using namespace std;


void upd_tout_tin_tour(int v, int root , vector<vector<int> > &g,  vector<int> &tour, vector<int> &tin, vector<int> &tout) {
    int T = 0;
    vector<pair<int, int> > stk;
    stk.emplace_back(root, 0);
    while (!stk.empty()) {
        auto &[v, ci] = stk.back();
        if (ci == 0) {
            tin[v] = ++T;
            tour[T] = v;
        }
        if (ci < (int)g[v].size()) {
            stk.emplace_back(g[v][ci++], 0);
        } else {
            tout[v] = T;
            stk.pop_back();
        }
    }
}

void upd_border(int v, int Q, map<int, vector<pair<int, int> > > &borders) {
    vector<pair<int, int> > ranges(Q);
    for (int i = 0; i < Q; ++i) {
        int l = readInt(), r = readInt();
        ranges[i] = {l, r};
        borders[r].emplace_back(i, +1);

        if (l > 1) {
            borders[l - 1].emplace_back(i, -1);
        }
    }
}

void upd_answer( int N , vector<int> &tourColor, vector<vector<int> > &answer, map<int, vector<pair<int, int> > > &borders , vector<int> &tin, vector<int> &tout) {
    vector<int> thresholds; 
    for (auto &[x, _] : borders)
        thresholds.push_back(x);
    sort(thresholds.begin(), thresholds.end());

    vector<int> B(N+1), P(N+1);
    for (int X : thresholds) {
        for (int i = 1; i <= N; ++i)
            B[i] = (tourColor[i] <= X);
        for (int i = 1; i <= N; ++i)
            P[i] = P[i-1] + B[i];

        for (int v = 1; v <= N; ++v) {
            int cnt = P[tout[v]] - P[tin[v] - 1];
            for (auto &[qi, sign] : borders[X])
                answer[v][qi] += sign * cnt;
        }
    }
}

int main() {
    int N = readInt() , Q = readInt();

    vector<int> par(N+1), col(N+1), isRoot(N+1, 1);
    vector<vector<int> > g(N+1);
    for (int i = 1; i <= N; ++i) {
        par[i] = readInt() , col[i] = readInt();
        if (par[i]) {
            g[par[i]].push_back(i);

            isRoot[i] = 0;
        }
    }

    int root = 1;
    while (!isRoot[root]) { ++root;}

    vector<int> tin(N+1), tout(N+1), tour(N+1);
    upd_tout_tin_tour(root, root, g, tour, tin, tout);

    
    map<int, vector<pair<int, int> > > borders;
    upd_border(root, Q,  borders);


    vector<int> tourColor(N+1);
    for (int i = 1; i <= N; ++i)
        tourColor[i] = col[tour[i]];

    vector<vector<int> > answer(N+1, vector<int>(Q, 0));
    upd_answer(N, tourColor, answer, borders, tin, tout);

    for (int v = 1; v <= N; ++v)
        for (int i = 0; i < Q; ++i)
            writeInt(answer[v][i], i + 1 < Q ? ' ' : '\n');

    return 0;
}
