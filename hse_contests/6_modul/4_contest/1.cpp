/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

#include <cstring>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

struct Ukkonen {
    int N, VN; 
    vector<map<char, int>> t;
    vector<int> l, r, p, suf; 
    int vn;

    Ukkonen(const char *s)
        : N(strlen(s)),
          VN(2 * N + 2),
          t(VN),
          l(VN),
          r(VN),
          p(VN),
          suf(VN),
          vn(2) {

        int v = 1, pos = 0;
        l[1] = -1;
        for (int i = 0; i < 256; i++)
            t[0][i] = 1;

        for (int n = 0; s[n]; n++) {
            char c = s[n];
            auto new_leaf = [&](int v) {
                p[vn] = v, l[vn] = n, r[vn] = N, t[v][c] = vn++;
            };
        go:;
            if (r[v] <= pos) {
                if (!t[v].count(c)) {
                    new_leaf(v), v = suf[v], pos = r[v];
                    goto go;
                }
                v = t[v][c], pos = l[v] + 1;
            } else if (c == s[pos]) {
                pos++;
            } else {
                int x = vn++;
                l[x] = l[v], r[x] = pos, l[v] = pos;
                p[x] = p[v], p[v] = x;
                t[p[x]][s[l[x]]] = x, t[x][s[pos]] = v;
                new_leaf(x);
                v = suf[p[x]], pos = l[x];
                while (pos < r[x]) {
                    v = t[v][s[pos]], pos += r[v] - l[v];
                }
                suf[x] = (pos == r[x] ? v : vn);
                pos = r[v] - (pos - r[x]);
                goto go;
            }
        }
    }


    vector<int> id;                     
    vector<tuple<int,int,int>> edges;   

    void dfs_build(int v) {
        id[v] = edges.size(); 
        edges.emplace_back(-1, -1, -1); 

        for (auto &e : t[v]) {
            int u = e.second;
            if (id[u] == -1) {
                dfs_build(u);
                edges[id[u]] = make_tuple(id[v], l[u], r[u]);
            }
        }
    }

    void print() {
        id.assign(VN, -1);
        edges.clear();

        dfs_build(1); 

        int nodes = edges.size(); 
        cout << nodes << "\n";

        for (int i = 1; i < nodes; i++) {
            auto [par, lf, rf] = edges[i];
            cout << par << " " << lf << " " << rf << "\n";
        }
    }
};


int main() {
    string s;
    cin >> s;
    Ukkonen uk(s.c_str());
    uk.print();
}
