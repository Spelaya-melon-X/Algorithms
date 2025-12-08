#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

const int MAXN = 1000;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n; cin >> n;
    vector<bitset<2*MAXN>> a(n);
    
    
    for (int i = 0; i < n; i++) {
        string row; cin >> row;
        for (int j = 0; j < n; j++) {
            a[i][j] = (row[j] == '1');
        }
        
        a[i][n + i] = 1;
    }
    
    
    for (int i = 0; i < n; i++) {
        
        int pivot = i;
        while (pivot < n && !a[pivot][i]) { pivot++; }
        if (pivot == n) { cout << "NO\n"; return 0; }
        if (pivot != i) {swap(a[i], a[pivot]); }
        
        
        for (int j = 0; j < n; j++) {
            if (j != i && a[j][i]) {
                a[j] ^= a[i];
            }
        }
    }
    
    cout << "YES\n";
    
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << a[i][n + j];
        }
        cout << '\n';
    }
    
    return 0;
}