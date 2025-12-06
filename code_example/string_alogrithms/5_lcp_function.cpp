#include <string> 
#include <iostream>
using namespace std;

int lcp_two_strings(string s1, string s2) {
    int min_len = min(s1.length(), s2.length());
    for (int i = 0; i < min_len; i++) {
        if (s1[i] != s2[i]) {
            return i;  // столько символов совпало
        }
    }
    return min_len;  // все символы совпали
}

int main() {
    cout << lcp_two_strings("abc", "abd") << endl;  // 2
    cout << lcp_two_strings("hello", "hell") << endl;  // 4
    cout << lcp_two_strings("foo", "bar") << endl;  // 0
}