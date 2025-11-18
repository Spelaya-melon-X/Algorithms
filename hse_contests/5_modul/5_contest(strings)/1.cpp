#include <iostream>
#include <string>
#include <set>

using namespace std;

typedef long long ll;

const int MOD1 = 1000000007 ,  MOD2 = 1000000009 , BASE = 131;
set<pair<ll, ll> > hashes;

int main() {
    string s; std::cin >> s;
    int n = s.size();


    for (int i = 0; i < n; ++i) {
        ll hash1 = 0, hash2 = 0;
        for (int j = i; j < n; ++j) {

            hash1 = (hash1 * BASE + s[j]) % MOD1;
            hash2 = (hash2 * BASE + s[j]) % MOD2;
            hashes.insert({hash1, hash2});
        }
    }

    cout << hashes.size() << endl;
    return 0;
}