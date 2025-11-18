#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    string a, b;
    getline(cin, a);
    getline(cin, b);
    
    if (b.empty()) {
        cout << "0\n";
        return 0;
    }
    
    string s = b + '#' + a;
    int n = s.size();
    int m = b.size();
    
    vector<int> pi(n, 0);
    vector<int> positions;
    
    
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j])
            j = pi[j - 1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
        
        
        if (pi[i] == m) {
            positions.push_back(i - 2 * m + 1);  
        }
    }
    
    cout << positions.size() << "\n";
    for (int i = 0; i < positions.size(); i++) {
        if (i > 0) cout << " ";
        cout << positions[i];
    }
    if (!positions.empty()) cout << "\n";
    
    return 0;
}