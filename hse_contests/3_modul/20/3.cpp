#include <iostream>
#include <vector>
#include <bitset>

using namespace std;
int main() {
    ios_base::sync_with_stdio(false);cin.tie(nullptr);
    int n; cin >> n;
    vector<bitset<2000>> gr(n);

    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        for (int j = 0; j < n; ++j) {
            gr[i][j] = (s[j] == '1');
        }
    }


    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            if (gr[i][k]) {gr[i] |= gr[k];}
        }
    }


    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {cout << gr[i][j];}
        cout << '\n';
    }
    return 0;
}