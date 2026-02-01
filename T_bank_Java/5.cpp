#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    unordered_map<int, vector<int>> pos;
    for (int i = 0; i < n; i++) {
        pos[a[i]].push_back(i);
    }

    for (int i = 0; i < n; i++) {
        int X = a[i];
        auto &v = pos[X];

        int k = v.size();
        int max_gap = 0;

        for (int j = 0; j < k; j++) {
            int cur = v[j];
            int nxt = v[(j + 1) % k];
            int gap = (n + nxt - cur - 1) % n;
            max_gap = max(max_gap, gap);
        }

        int ans = (max_gap + 1) / 2;

        bool hasLess = false, hasGreater = false;
        for (int x : a) {
            if (x < X) hasLess = true;
            if (x > X) hasGreater = true;
        }

        if (hasLess && hasGreater) ans++;

        cout << ans << " ";
    }

    cout << "\n";
}
