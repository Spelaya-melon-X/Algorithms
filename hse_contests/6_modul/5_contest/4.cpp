#include <iostream> 
#include <vector> 
#include <unordered_map>
#include <cmath>

using namespace std;


static long long powww(long long a, long long e, long long mod) {
    long long r = 1;

    while ( e) {
        if (e & 1) r  = (__int128)r * a % mod;
        a =  (__int128)a * a % mod;
        e >>=  1;
    }

    return r; }


long long BDSM(long long B, long long N, long long P) {
    B %= P;  N %= P;
    if (N == 1) {
        return 0;  
    }

    long long m = (long long)sqrt(P) + 1;

    
    unordered_map<long long , long long> table; table.reserve(m * 1.3); table.max_load_factor(0.7);

    long long e = 1;
    for (long long j = 0; j < m; j++) {
        if (!table.count(e)) table[e] = j;
        e = (__int128)e * B % P;
    }

    
    long long factor = powww(B, P - 1 - m, P) , cur = N;

    for (long long i = 0; i <= m; i++) {
        if (table.count(cur)) {
            long long ans = i * m + table[cur];
            return ans;
        }
        cur = (__int128)cur * factor % P;
    }

    return -1;  
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long P, B, N;
    while (cin >> P >> B >> N) {
        long long ans = BDSM(B, N, P);
        if (ans == -1) cout << "no solution\n";
        else cout << ans << "\n";
    }
    return 0;
}
