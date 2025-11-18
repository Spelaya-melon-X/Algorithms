#include <iostream>
#include <vector>
#include <string>
using namespace std;

typedef long long ll;

const ll MOD1 = 1000000007;
const ll MOD2 = 1000000009;
const ll BASE = 131;

vector<ll> pow1, pow2, h1, h2;

void build_hashes(const string& s) {
    int n = s.size();
    
    // Предподсчет степеней BASE
    pow1.resize(n + 1);
    pow2.resize(n + 1);
    pow1[0] = pow2[0] = 1;
    for (int i = 1; i <= n; i++) {
        pow1[i] = (pow1[i-1] * BASE) % MOD1;
        pow2[i] = (pow2[i-1] * BASE) % MOD2;
    }
    
    // Предподсчет префиксных хэшей
    h1.resize(n + 1);
    h2.resize(n + 1);
    h1[0] = h2[0] = 0;
    for (int i = 0; i < n; i++) {
        h1[i+1] = (h1[i] * BASE + s[i]) % MOD1;
        h2[i+1] = (h2[i] * BASE + s[i]) % MOD2;
    }
}

// Получить хэш подстроки [l, r]
pair<ll, ll> get_hash(int l, int r) {
    // h[r+1] - h[l] * BASE^(r-l+1)
    ll hash1 = (h1[r+1] - h1[l] * pow1[r-l+1] % MOD1 + MOD1) % MOD1;
    ll hash2 = (h2[r+1] - h2[l] * pow2[r-l+1] % MOD2 + MOD2) % MOD2;
    return {hash1, hash2};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    int m;
    cin >> m;
    
    build_hashes(s);
    
    while (m--) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        a--; b--; c--; d--;
        
        // Проверяем, что длины совпадают
        if (b - a != d - c) {
            cout << "No\n";
            continue;
        }
        
        if (get_hash(a, b) == get_hash(c, d)) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
    
    return 0;
}