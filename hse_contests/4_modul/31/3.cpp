#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXG = 5000; 

int main() {
    int n; cin >> n;

    vector<int> g(n+1, 0);  
    vector<bool> used(MAXG, false);

    if (n >= 1) {
        for (int len = 1; len <= n; ++len) {
            vector<int> changed;
            for (int i = 1; i <= len; ++i) {
                int ll = i - 1 , rl = len - i;
                int l_st ; 
                if ( ll >= 2){
                    l_st = g[ll];
                }else {
                    l_st = 0;
                }

                int r_st ; 
                if ( rl >= 2){
                    r_st = g[rl];
                }else {
                    r_st = 0;
                }


                int ans = l_st ^ r_st; // xor ---> bacause i want the mex-funciton 
                if (ans < MAXG && !used[ans]) {
                    used[ans] = true;
                    changed.push_back(ans);
                }
            }

            int mex = 0;
            while (mex < MAXG && used[mex]) {
                ++mex;
            }
            g[len] = mex;

            for (int val : changed) {
                used[val] = false;
            }
        }
    }

    if (g[n] == 0) {
        cout << "Mueller" << endl;
    } else {
        cout << "Schtirlitz" << endl;
        vector<int> wins;
        for (int i = 1; i <= n; ++i) {
            int ll = i - 1 , rl = n - i;

            int l_st ; 
            if ( ll >= 2){
                l_st = g[ll];
            }else {
                l_st = 0;
            }

            int r_st ; 
            if ( rl >= 2){
                r_st = g[rl];
            }else {
                r_st = 0;
            }

            if ((l_st ^ r_st) == 0) {
                wins.push_back(i);
            }
        }
        sort(wins.begin(), wins.end());
        for (int pos : wins) {
            cout << pos << endl;
        }
    }

    return 0;
}