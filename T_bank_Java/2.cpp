// OK 

#include <iostream>
#include <map>
#include <vector>
#include <climits>
#include <string>
#include <algorithm>
using namespace std;

string s; 
const string tbank = "tbank" , study = "study";

void patternCost(std::vector<int>& v , string tbank ) {
    for (int i = 0; i + 5 <= s.size(); ++i) {
        int c = 0;
        for (int j = 0; j < 5; ++j){
            if (s[i + j] != tbank[j]) {
                c++;
            }
        }
        v[i] = c;
    }
}

void findMinCombinedCost(int &ans , vector<int> &cost , vector<int> &minim) {
    for (int i = 0; i + 5 <= s.size(); ++i) {
        int j = i + 5;
        if (j + 5 <= s.size()) {
            ans = min(ans, cost[i] + minim[j]);
        }
    }
}

void computeMinSuf(vector<int> &minim , vector<int> &cost) {
    for (int i = s.size()- 1; i >= 0; --i){
        minim[i] = min(minim[i + 1], cost[i]);
    }
}

int main() {
    cin >> s;
    int n = s.size();

    vector<int> costtbank(n, 1e9), coststudy(n, 1e9);
    patternCost(costtbank , tbank);
    patternCost(coststudy, study);

    int ans = INT_MAX;

    
    vector<int> minim(n + 1, INT_MAX);

    computeMinSuf(minim , coststudy);
    findMinCombinedCost(ans , costtbank , minim);

    minim.assign(n + 1, INT_MAX);


    computeMinSuf(minim , costtbank);
    findMinCombinedCost(ans , coststudy , minim);

    
    for (int i = 0; i + 5 <= n; ++i) {
        for (int d = -4; d <= 4; ++d) {
            int j = i + d , changes = 0;
            bool flag = true;
            if (j < 0 || j + 5 > n) {
                continue;
            }
            map<int, char> mp;

            for (int k = 0; k < 5; ++k) {
                mp[i + k] = tbank[k];
            }

            for (int k = 0; k < 5; ++k) {
                int pos = j + k;
                if (mp.count(pos) && mp[pos] != study[k]) {
                    flag = false;
                    break;
                }
                mp[pos] = study[k];
            }

            if (!flag) {
                continue;
            }

            for (auto [pos, ch] : mp)
                if (s[pos] != ch) {
                    changes++;
                }

            ans = min(ans, changes);
        }
    }

    cout << ans << '\n';
    return 0;
}










//// OK 
// #include <iostream>
// #include <map>
// #include <vector>
// #include <climits>
// #include <string>
// #include <algorithm>


// using namespace std;

// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);

//     string s;
//     cin >> s;
//     int n = s.size();

//     const string tbank = "tbank";
//     const string study = "study";

//     vector<int> costtbank(n, 1e9), coststudy(n, 1e9);

    
//     for (int i = 0; i + 5 <= n; ++i) {
//         int c = 0;
//         for (int j = 0; j < 5; ++j)
//             if (s[i + j] != tbank[j]) c++;
//         costtbank[i] = c;
//     }

    
//     for (int i = 0; i + 5 <= n; ++i) {
//         int c = 0;
//         for (int j = 0; j < 5; ++j)
//             if (s[i + j] != study[j]) c++;
//         coststudy[i] = c;
//     }

//     int ans = INT_MAX;

    
//     vector<int> minim(n + 1, INT_MAX);
//     for (int i = n - 1; i >= 0; --i)
//         minim[i] = min(minim[i + 1], coststudy[i]);

//     for (int i = 0; i + 5 <= n; ++i) {
//         int j = i + 5;
//         if (j + 5 <= n)
//             ans = min(ans, costtbank[i] + minim[j]);
//     }

    
//     minim.assign(n + 1, INT_MAX);
//     for (int i = n - 1; i >= 0; --i)
//         minim[i] = min(minim[i + 1], costtbank[i]);

//     for (int i = 0; i + 5 <= n; ++i) {
//         int j = i + 5;
//         if (j + 5 <= n)
//             ans = min(ans, coststudy[i] + minim[j]);
//     }

    
//     for (int i = 0; i + 5 <= n; ++i) {
//         for (int d = -4; d <= 4; ++d) {
//             int j = i + d;
//             if (j < 0 || j + 5 > n) continue;

//             bool ok = true;
//             int changes = 0;
//             map<int, char> mp;

//             for (int k = 0; k < 5; ++k)
//                 mp[i + k] = tbank[k];

//             for (int k = 0; k < 5; ++k) {
//                 int pos = j + k;
//                 if (mp.count(pos) && mp[pos] != study[k]) {
//                     ok = false;
//                     break;
//                 }
//                 mp[pos] = study[k];
//             }

//             if (!ok) continue;

//             for (auto [pos, ch] : mp)
//                 if (s[pos] != ch) changes++;

//             ans = min(ans, changes);
//         }
//     }

//     cout << ans << '\n';
//     return 0;
// }
