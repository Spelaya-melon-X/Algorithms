#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

bool isEqual(double a, double b, double eps = 1e-9) {
    return fabs(a - b) < eps;
}

double determinant(vector<vector<double>>& m) {
    int n = m.size();
    double det = 1.0;
    
    for (int i = 0; i < n; i++) {        
        int piv = i;
        while (piv < n && isEqual(m[piv][i], 0.0)) {
            piv++;
        }
                
        if (piv == n) {
            return 0.0;
        }
                
        if (piv != i) {
            swap(m[i], m[piv]);
        det *= -1; 
        }
                
        double pivot_val = m[i][i];
        det *= pivot_val;
                
        for (int j = i + 1; j < n; j++) {
            double factor = m[j][i] / pivot_val;
            if (!isEqual(factor, 0.0)) {
                for (int k = i; k < n; k++) {
                    m[j][k] -= m[i][k] * factor;
                }
            }
        }
    }
    
    return det;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;    
    while (cin >> n) {
        vector<vector<double>> m(n, vector<double>(n));
                
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> m[i][j];
            }
        }
                
    vector<vector<double>> mc = m; 
        double det = determinant(mc);      
        cout << static_cast<int>(round(det)) << "\n";
    }
    
    return 0;
}