#include <iostream>
#include <vector>
#include <string>
using namespace std;


vector<int> compute_prefix_function(const string& s) {
    int n = s.length();
    vector<int> pi(n, 0);
    
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        
        while (j > 0 && s[i] != s[j]) {
            j = pi[j - 1];
        }
        
        if (s[i] == s[j]) {
            j++;
        }
        
        pi[i] = j;
    }
    return pi;
}

vector<int> kmp_search(const string& text, const string& pattern) {
    vector<int> occurrences;
    int n = pattern.length();
    int m = text.length();
    
    if (n == 0) return occurrences;
    
    // Вычисляем префикс-функцию для pattern
    vector<int> pi = compute_prefix_function(pattern);
    
    int j = 0; // длина текущего совпавшего префикса pattern
    for (int i = 0; i < m; i++) {
        while (j > 0 && text[i] != pattern[j]) {
            j = pi[j - 1];
        }
        
        if (text[i] == pattern[j]) {
            j++;
        }
        
        if (j == n) {
            occurrences.push_back(i - n + 1);
            j = pi[j - 1]; // продолжаем поиск следующих вхождений
        }
    }
    
    return occurrences;
}


vector<int> kmp_with_separator(const string& text, const string& pattern) {
    vector<int> occurrences;
    string combined = pattern + '#' + text;
    vector<int> pi = compute_prefix_function(combined);
    
    int n = pattern.length();
    for (int i = n + 1; i < combined.length(); i++) {
        if (pi[i] == n) {
            occurrences.push_back(i - 2 * n - 1);
        }
    }
    
    return occurrences;
}

int main() {
    string text = "abababcabababc";
    string pattern = "ababc";
    
    vector<int> result = kmp_search(text, pattern);
    
    cout << "Pattern found at positions: ";
    for (int pos : result) {
        cout << pos << " ";
    }
    // Вывод: 2 9
}