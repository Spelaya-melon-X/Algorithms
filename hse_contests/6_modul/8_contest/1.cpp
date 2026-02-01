#include <iostream>
#include <vector>
using namespace std;

int main() {
    
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k; long long m; cin >> n >> k >> m;
    
    vector<long long> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }

    vector<long long> res(n + k, 0);
    
    
    for (int i = k; i < n + k; i++) {
        res[i] = p[i - k];
    }
    
    
    for (int i = 0; i < n; i++) {
        res[i] = (res[i] - p[i] + m) % m;
    }
    
    
    for (int i = 0; i < n + k; i++) {
        cout << res[i] << " ";
    }
    cout << "\n";
    
    return 0;
}