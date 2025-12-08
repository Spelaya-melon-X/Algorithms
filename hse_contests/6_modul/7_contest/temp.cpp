#include <iostream>
#include <malloc/_malloc_type.h>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

vector<int> z_to_pi(const vector<int>& z) {
    int n = z.size();
    if (n == 0) return {};
    
    vector<int> pi(n, 0);
    
    
    for (int i = 1; i < n; i++) {
        if (z[i] > 0) {
            int end_pos = i + z[i] - 1;
            pi[end_pos] = max(pi[end_pos], z[i]);
        }
    }
    
    
    for (int i = n - 2; i >= 0; i--) {
        pi[i] = max(pi[i], pi[i + 1] - 1);
    }
    
    return pi;
}

int main() {
    vector<int> z = {0, 0, 1, 0, 3, 0, 1};
    vector<int> pi = z_to_pi(z);
    
    for (int val : pi) cout << val << " ";
    return 0;
}