#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;ll m;cin >> n >> k >> m ; 
    vector<ll> p(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i]; p[i] %= m;
        if (p[i] < 0) p[i] += m;
    }

    int t = max(n - k, 1);
    vector<ll> a(max(0, n - k));

    
    for (int i = n - 1; i >= k; --i) {
        int idx = i - k;
        a[idx] = p[i] % m;
        p[idx] = (p[idx] + a[idx]) % m;
    }

    
    if ((int)a.size() == 0) {
        cout << 0 << '\n';
    } else {
        for (size_t i = 0; i < a.size(); ++i) {
            if (i) cout << ' ';
            cout << (a[i] % m + m) % m;
        }
        cout << '\n';
    }

    
    for (int i = 0; i < k; ++i) {
        if (i) cout << ' ';
        ll val = 0;
        if (i < n) val = p[i] % m;
        val = (val + m) % m;
        cout << val;
    }
    cout << '\n';
    return 0;
}
