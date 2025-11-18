

#include <iostream>
#include <vector> 
#include <unordered_map>
#include <algorithm>

using namespace std;
using ull = unsigned long long;

struct DoubleHash {
    vector<ull> h1, p1;
    vector<ull> h2, p2;
    const ull B1 = 1000003ull;    
    const ull B2 = 1000033ull;    

    DoubleHash(const string &s) {
        int n = s.size();
        h1.assign(n + 1, 0); p1.assign(n + 1, 1);
        h2.assign(n + 1, 0); p2.assign(n + 1, 1);
        for (int i = 0; i < n; ++i) {
            h1[i + 1] = h1[i] * B1 + (unsigned char)s[i];
            p1[i + 1] = p1[i] * B1;
            h2[i + 1] = h2[i] * B2 + (unsigned char)s[i];
            p2[i + 1] = p2[i] * B2;
        }
    }
    
    pair<ull,ull> get(int l, int r) const {
        ull A = h1[r] - h1[l] * p1[r - l];
        ull B = h2[r] - h2[l] * p2[r - l];
        return {A, B};
    }
};


struct PairHash {
    size_t operator()(const pair<ull,ull> &x) const noexcept {
        
        return (size_t)(x.first ^ (x.second + 0x9e3779b97f4a7c15ULL + (x.first<<6) + (x.first>>2)));
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;
    string a, b;
    cin >> a >> b;
    

    DoubleHash ha(a), hb(b);

    int low = 0, high = n;
    int best = 0;
    int bestPosB = -1;

    while (low <= high) {
        int mid = (low + high) / 2;
        bool found = false;
        int foundPosB = -1;

        if (mid == 0) {
            
            found = true;
            foundPosB = 0;
        } else {
            unordered_map<pair<ull,ull>, vector<int>, PairHash> mp;
            mp.reserve(max(1, n - mid + 1) * 2);

            
            for (int i = 0; i + mid <= n; ++i) {
                auto h = ha.get(i, i + mid);
                mp[h].push_back(i);
            }

            
            for (int j = 0; j + mid <= n; ++j) {
                auto h2 = hb.get(j, j + mid);
                auto it = mp.find(h2);
                if (it == mp.end()) continue;
                
                for (int posA : it->second) {
                    
                    
                    if (a.compare(posA, mid, b, j, mid) == 0) {
                        found = true;
                        foundPosB = j;
                        break;
                    }
                }
                if (found) break;
            }
        }

        if (found) {
            best = mid;
            bestPosB = foundPosB;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    if (best == 0) {
        cout << "\n";
    } else {
        cout << b.substr(bestPosB, best) << "\n";
    }
    return 0;
}
