#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MIN_B = -10000;
const int MAX_B = 10000;
const int RANGE = MAX_B - MIN_B + 1;

struct Seq {
    int min_bal , total_bal , len , orig_idx , min_bal_rev;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n; cin >> n;
    vector<string> sss(n);
    for (int i = 0; i < n; i++) {
        cin >> sss[i];
    }
    
    vector<Seq> arr;
    for (int i = 0; i < n; i++) {
        string s = sss[i];
        int cur = 0 , minb = 0;
        for (char c : s) {
            if (c == '(') cur++;
            else cur--;
            if (cur < minb) minb = cur;
        }
        Seq seq = {minb, cur, (int)s.length(), i, 0};
        if (cur < 0) {
            string s_rev = s;
            reverse(s_rev.begin(), s_rev.end());
            for (char& c : s_rev) {
                if (c == '(') c = ')';
                else if (c == ')') c = '(';
            }
            int cur_rev = 0 , minb_rev = 0;
            for (char c : s_rev) {
                if (c == '(') cur_rev++;
                else cur_rev--;
                if (cur_rev < minb_rev) minb_rev = cur_rev;
            }
            seq.min_bal_rev = minb_rev;
        }
        arr.push_back(seq);
    }
    
    vector<Seq> groupA, groupB;
    for (const Seq& s : arr) {
        if (s.total_bal >= 0) groupA.push_back(s);
        else groupB.push_back(s);
    }
    
    sort(groupA.begin(), groupA.end(), [](const Seq& a, const Seq& b) { return a.min_bal > b.min_bal; });
    
    sort(groupB.begin(), groupB.end(), [](const Seq& a, const Seq& b) { return a.min_bal_rev > b.min_bal_rev; });
    
    vector<Seq> sor_arr;
    for (const auto& a : groupA) sor_arr.push_back(a);
    for (const auto& a : groupB) sor_arr.push_back(a);
    
    vector<vector<int> >  dp(n+1, vector<int>(RANGE, -1000000000));
    vector<vector<int> > fr_b(n+1, vector<int>(RANGE, -1));
    vector<vector<int> >  used_seq(n+1, vector<int>(RANGE, -1));
    
    dp[0][0 - MIN_B] = 0;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < RANGE; j++) {
            dp[i+1][j] = dp[i][j];
        }
        const Seq& seq = sor_arr[i];
        for (int j = 0; j < RANGE; j++) {
            if (dp[i][j] < 0) continue;
            int real_bal = j + MIN_B;

            if (real_bal + seq.min_bal < 0) continue;
            int n_bal = real_bal + seq.total_bal;

            if (n_bal < MIN_B || n_bal > MAX_B) continue;
            int new_j = n_bal - MIN_B;

            int nl = dp[i][j] + seq.len;

            if (nl > dp[i+1][new_j]) {
                dp[i+1][new_j] = nl;
                fr_b[i+1][new_j] = real_bal;
                used_seq[i+1][new_j] = i;
            }
        }
    }
    
    int max_l = dp[n][0 - MIN_B];
    if (max_l < 0) max_l = 0;
    vector<int> norm ;
    int cur_j = 0 - MIN_B;
    for (int layer = n; layer >= 1; layer--) {
        if (used_seq[layer][cur_j] == -1) continue;

        int i_am_sorted = used_seq[layer][cur_j];
        norm .push_back(sor_arr[i_am_sorted].orig_idx);
        int bivshiy_balance = fr_b[layer][cur_j];
        cur_j = bivshiy_balance - MIN_B;
    }
    reverse(norm .begin(), norm .end());
    
    vector<int> order(n, -1);
    int pos = 1;
    for (int idx : norm ) {
        order[idx] = pos++;
    }
    

    vector<int> result;
    for (int i = 0; i < n; i++) {
        if (order[i] != -1) {
            result.push_back(i+1);
        }
    }
    
    cout << max_l << " " << result.size() << "\n";
    for (int i = 0; i < result.size(); i++) {
        cout << result[i] << (i < result.size()-1 ? " " : "");
    }
    cout << "\n";
    
    return 0;
}