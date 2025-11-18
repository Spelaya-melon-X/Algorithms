#include <iostream>
#include <vector> 
#include <numeric>
#include <algorithm>

using namespace std;
using ull = unsigned long long;

vector<int> build_sa(const string &s) {
    int n = s.size();
    vector<int> sa(n), rnk(n), tmp(n);
    iota(sa.begin(), sa.end(), 0);
    for (int i = 0; i < n; i++) rnk[i] = s[i];
    for (int k = 1; k < n; k <<= 1) {
        auto cmp = [&](int i, int j) {
            if (rnk[i] != rnk[j]) return rnk[i] < rnk[j];
            int ri = i + k < n ? rnk[i + k] : -1;
            int rj = j + k < n ? rnk[j + k] : -1;
            return ri < rj;
        };
        sort(sa.begin(), sa.end(), cmp);
        tmp[sa[0]] = 0;
        for (int i = 1; i < n; i++)
            tmp[sa[i]] = tmp[sa[i - 1]] + cmp(sa[i - 1], sa[i]);
        rnk.swap(tmp);
        if (rnk[sa.back()] == n - 1) break;
    }
    return sa;
}

struct RH {
    vector<ull> h, p;
    RH(const string &s) {
        int n = s.size();
        h.resize(n + 1, 0);
        p.resize(n + 1, 1);
        const ull B = 1315423911ull;
        for (int i = 0; i < n; i++) {
            h[i + 1] = h[i] * B + (unsigned char)s[i];
            p[i + 1] = p[i] * B;
        }
    }
    ull get(int l, int r) const { // [l, r)
        return h[r] - h[l] * p[r - l];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    int k;
    cin >> s >> k;
    int n = s.size();
    string t = s + s;

    auto sa = build_sa(t);
    RH rh(t);

    ull prev_hash = 0;
    bool has_prev = false;
    int cnt = 0;

    for (int i : sa) {
        if (i >= n) continue;
        ull cur_hash = rh.get(i, i + n);
        if (has_prev && cur_hash == prev_hash) continue;
        prev_hash = cur_hash;
        has_prev = true;
        cnt++;
        if (cnt == k) {
            cout << t.substr(i, n) << '\n';
            return 0;
        }
    }

    cout << "IMPOSSIBLE\n";
}
