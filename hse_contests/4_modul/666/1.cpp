#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <numeric>
#include <limits>
using namespace std;

// dp[n][k] = true, если при n оставшихся ножках и предыдущем ходе = k текущий игрок обладает выигрышной позицией.

// На первый ход у нас "предыдущего k" нет, но он -->  0, и первый ход --> 1.
// Выигрыш первого игрока <=> состояние после его хода (N-1, k=1) — проигрышное для второго.

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> tests;
    int N;
    while ( (cin >> N) && N != 0) {
        tests.push_back(N);
    }
    if (tests.empty()) return 0;
    int maxN = *max_element(tests.begin(), tests.end());

    int K = int(sqrt(2.0 * maxN)) + 2;

    vector<char> dp((maxN+1)*(K+1), 0);

    auto at = [&](int n, int k)->char& { return dp[n*(K+1) + k]; };

    for(int n = 1; n <= maxN; n++){
        int maxk = min(n, K);
        for(int k = 1; k <= maxk; k++){
            bool win = false;

            if (k <= n && !at(n-k, k))//k
                win = true;

            else if (k+1 <= n && k+1 <= K && !at(n-k-1, k+1))//k+1
                win = true;
            at(n, k) = win;
        }
    }


    for(size_t i = 0; i < tests.size(); i++){
        int n = tests[i];

        bool secondWins = at(n-1, 1);
        cout << "Case #" << (i+1) << ": "
             << (secondWins
                    ? "Second player wins.\n"
                    : "First player wins.\n");
    }
    return 0;
}
