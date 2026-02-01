
#include <algorithm>
#include <string>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
int t ; 

int main() {
    cin >> t;

    while (t--) {
        string s; cin >> s;
        int n = s.size();
        bool flag = false;

        for (char c : s) {
            if (c == '1') {
                flag = true;
                break;
            }
        }

        if (!flag) {
            cout << 0 << '\n';
            continue;
        }


        string ss = s + s;

        int maxLen = 0 , currentSymb = 0;
        for (char c : ss) {
            if (c == '1') {
                currentSymb++;
                maxLen = max(maxLen, currentSymb);
            } else {
                currentSymb = 0;
            }
        }


        maxLen = min(maxLen, n);
        cout << ((maxLen+1)/2)  * ((maxLen +2) / 2) << std::endl; 
    }

    return 0;
}
