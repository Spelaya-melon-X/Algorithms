#include <bits/stdc++.h>
using namespace std;

const long long BASE = 1000000000; 
typedef vector<long long> bigint;


bigint to_bigint(const string &s) {
    bigint res;
    for (int i = (int)s.size(); i > 0; i -= 9) {
        int l = max(0, i - 9);
        res.push_back(stoll(s.substr(l, i - l)));
    }
    reverse(res.begin(), res.end());
    return res;
}


int cmp(const bigint &a, const bigint &b) {
    if (a.size() != b.size()) return (a.size() < b.size()) ? -1 : 1;
    for (size_t i = 0; i < a.size(); i++)
        if (a[i] != b[i]) return (a[i] < b[i]) ? -1 : 1;
    return 0;
}


void sub(bigint &a, const bigint &b) {
    int n = a.size(), m = b.size();
    long long carry = 0;
    for (int i = 0; i < n; i++) {
        long long bi = (i < m ? b[m - 1 - i] : 0);
        a[n - 1 - i] -= bi + carry;
        if (a[n - 1 - i] < 0) { a[n - 1 - i] += BASE; carry = 1; }
        else carry = 0;
    }
    while (!a.empty() && a[0] == 0) a.erase(a.begin());
    if (a.empty()) a.push_back(0);
}


string to_string(const bigint &a) {
    string res = std::to_string(a[0]);
    for (size_t i = 1; i < a.size(); i++) {
        string block = std::to_string(a[i]);
        res += string(9 - block.size(), '0') + block;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string sa, sb;
    while (cin >> sa >> sb) {
        bigint A = to_bigint(sa), B = to_bigint(sb);

        if (cmp(A, B) < 0) {
            cout << "0\n" << sa << "\n";
            continue;
        }

        bigint cur;
        vector<int> quot;

        for (long long d : A) {
            cur.push_back(d);
            while (!cur.empty() && cur[0] == 0) cur.erase(cur.begin());
            if (cmp(cur, B) < 0) {
                quot.push_back(0);
                continue;
            }
            
            long long q = (cur.size() > B.size() ? BASE : cur[0]) / B[0];
            if (q > BASE - 1) q = BASE - 1;
            bigint prod = B;
            for (long long &x : prod) x *= q;
            sub(cur, prod);
            quot.push_back(q);
        }

        string qstr;
        for (int d : quot) qstr += std::to_string(d);
        cout << trim(qstr) << "\n";
        cout << trim(sa) << "\n"; 
    }
}
