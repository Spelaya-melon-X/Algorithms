
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n; string s; cin >> s;

    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i]; p[i]--; 
    }

    vector<int> rank(n);
    for (int i = 0; i < n; i++)
        rank[p[i]] = i;

    vector<int> lcp(n - 1);
    int k = 0;

    for (int i = 0; i < n; i++) {
        if (rank[i] == n - 1) {
            k = 0;
            continue;
        }

        int j = p[rank[i] + 1];
        while (i + k < n && j + k < n && s[i + k] == s[j + k])
            k++;

        lcp[rank[i]] = k;

        if (k > 0) k--;
    }

    for (int i = 0; i < n - 1; i++)
        cout << lcp[i] << (i + 1 == n - 1 ? '\n' : ' ');
}
