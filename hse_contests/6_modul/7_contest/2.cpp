#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;

const long double EPS = 1e-9;

bool isZero(long double x) {
    return fabs(x) < EPS;
}


int gauss(vector<vector<long double>>& a, vector<long double>& ans) {
    int n = a.size() , m = n; 
    
    vector<int> where(m, -1);
    
    for (int col = 0, row = 0; col < m && row < n; ++col) {
        
        int sel = row;
        for (int i = row; i < n; ++i) {
            if (fabs(a[i][col]) > fabs(a[sel][col])) {
                sel = i;
            }
        }
        
        if (isZero(a[sel][col])) {
            continue;
        }
        
        
        for (int j = col; j <= m; ++j) {
            swap(a[sel][j], a[row][j]);
        }
        
        where[col] = row;
        
        
        for (int i = 0; i < n; ++i) {
            if (i != row && !isZero(a[i][col])) {
                long double factor = a[i][col] / a[row][col];
                for (int j = col; j <= m; ++j) {
                    a[i][j] -= a[row][j] * factor;
                }
            }
        }
        
        ++row;
    }
    
    
    ans.assign(m, 0);
    for (int i = 0; i < m; ++i) {
        if (where[i] != -1) {
            ans[i] = a[where[i]][m] / a[where[i]][i];
        }
    }
    
    
    for (int i = 0; i < n; ++i) {
        long double sum = 0;
        for (int j = 0; j < m; ++j) {
            sum += ans[j] * a[i][j];
        }
        if (!isZero(sum - a[i][m])) {
            return 0; 
        }
    }
    
    
    for (int i = 0; i < m; ++i) {
        if (where[i] == -1) {
            return 2; 
        }
    }
    
    return 1; 
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(3);
    
    int n; cin >> n;
    
    vector<vector<long double>> a(n, vector<long double>(n + 1));
    
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n + 1; ++j) {
            cin >> a[i][j];
        }
    }
    
    vector<long double> ans;
    int result = gauss(a, ans);
    
    if (result == 0) {
        cout << "impossible\n";
    } else if (result == 1) {
        cout << "single\n";
        for (int i = 0; i < n; ++i) {
            cout << ans[i] << (i == n - 1 ? "\n" : " ");
        }
    } else {
        cout << "infinity\n";
    }
    
    return 0;
}