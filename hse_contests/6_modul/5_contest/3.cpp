#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> primes;
    const int LIM = 50000; 
    vector<bool> sieve(LIM + 1, true);
    sieve[0] = sieve[1] = false;

    
    for (int i = 2; i * i <= LIM; i++) {
        if (sieve[i]) {
            for (long long j = 1LL * i * i; j <= LIM; j += i)
                sieve[j] = false;
        }
    }
    for (int i = 2; i <= LIM; i++)
        if (sieve[i]) primes.push_back(i);

    long long n;
    while (cin >> n) {
        if (n == 1) {
            cout << 1 << "\n";
            continue;
        }

        long long phi = n;
        long long m = n;

        for (int p : primes) {
            if (1LL * p * p > m) break;
            if (m % p == 0) {
                phi -= phi / p;
                while (m % p == 0) m /= p;
            }
        }

        if (m > 1) {        
            phi -= phi / m;
        }

        cout << phi << "\n";
    }

    return 0;
}
