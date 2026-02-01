#include <iostream>
#include <vector>
using namespace std;

const int MOD = 1e9 + 7;

vector<int> get_lengths(int n, int parity) {
    // parity = 1 для нечётных индексов (группа A), parity = 0 для чётных (группа B)
    vector<int> lengths;
    for (int idx = 1; idx <= 2*n-1; ++idx) {
        if (idx % 2 == parity) {
            int len;
            if (idx <= n) len = idx;
            else len = 2*n - idx;
            lengths.push_back(len);
        }
    }
    return lengths;
}

vector<vector<int>> dp_ways(const vector<int>& lengths, int max_k) {
    int m = lengths.size();
    vector<vector<int>> dp(m+1, vector<int>(max_k+1, 0));
    dp[0][0] = 1;
    for (int i = 1; i <= m; ++i) {
        int L = lengths[i-1];
        dp[i][0] = 1;
        for (int j = 1; j <= max_k; ++j) {
            dp[i][j] = dp[i-1][j];
            if (j > 0 && L - (j-1) > 0) {
                dp[i][j] = (dp[i][j] + dp[i-1][j-1] * 1LL * (L - (j-1))) % MOD;
            }
        }
    }
    return dp;
}

int main() {
    int n, k;
    cin >> n >> k;
    
    if (k == 0) {
        cout << 1 << endl;
        return 0;
    }
    
    vector<int> lengths_A = get_lengths(n, 1); // нечётные индексы
    vector<int> lengths_B = get_lengths(n, 0); // чётные индексы
    
    int max_k_A = min(k, (int)lengths_A.size());
    int max_k_B = min(k, (int)lengths_B.size());
    
    auto dp_A = dp_ways(lengths_A, max_k_A);
    auto dp_B = dp_ways(lengths_B, max_k_B);
    
    long long ans = 0;
    for (int i = 0; i <= max_k_A; ++i) {
        if (i <= k && k - i <= max_k_B) {
            ans = (ans + dp_A[lengths_A.size()][i] * 1LL * dp_B[lengths_B.size()][k - i]) % MOD;
        }
    }
    
    cout << ans << endl;
    
    return 0;
}