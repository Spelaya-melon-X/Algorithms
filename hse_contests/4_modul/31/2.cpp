#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

#include "optimization.h"
using namespace std;

void foo(vector<bool> &dp  , vector<int> &v, int max_q) {

    for (int i = 1; i <= max_q; i++) {
        bool norm = false;
        for (int u : v) {
            if (i < u) break; 
            if (!dp[i - u]) {
                norm = true;
                break; 
            }
        }
        dp[i] = norm;
    }

}

void print(vector<bool> &dp , vector<int> &zapr) {
    for (int n : zapr) {
        if (dp[n]) {
            std::cout << "First" << '\n';
        }else {
            std::cout << "Second" << '\n';
        }
    }

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int k; cin >> k;
    // int k = readInt();
    vector<int> v(k);
    for (int i = 0; i < k; i++) {
        int temp ; cin >> temp ; v[i] = temp;
        // v[i] = readInt();
    }


    sort(v.begin(), v.end()  );

    v.erase(unique(v.begin(), v.end()), v.end());
    k = v.size();

    int m; cin >> m;
    vector<int> zapr(m);
    int max_q = 0;
    for (int i = 0; i < m; i++) {
        int temp ; cin >> temp ;  zapr[i] = temp;
        
        if (zapr[i] > max_q) {
            max_q = zapr[i];
        }
    }


    vector<bool> dp(max_q + 1, false);

    foo(dp, v, max_q);
    print(dp, zapr);
    

    return 0;
}