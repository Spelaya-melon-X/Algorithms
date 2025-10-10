#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

class FenwickTree {
    vector<long long> tree;
    int size;
public:
    FenwickTree(int n) : size(n) {
        tree.resize(n + 2, 0);
    }

    void add(int i, long long val) {
        while (i <= size) {
            tree[i] += val;
            i += i & -i;
        }
    }

    long long sum(int i) {
        long long res = 0;
        while (i > 0) {
            res += tree[i];
            i -= i & -i;
        }
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<pair<char, int> > qs;
    vector<int> val;

    string op;
    int x;

    while (cin >> op >> x) {
        qs.emplace_back(op[0], x);
        val.push_back(x);
    }

    sort(val.begin(), val.end());
    val.erase(unique(val.begin(), val.end()), val.end());

    map<int, int> com;
    for (int i = 0; i < (int)val.size(); ++i)
        com[val[i]] = i + 1;  

    FenwickTree f(val.size());

    for (auto [ch, x] : qs) {
        if (ch == '+') {
            f.add(com[x], x); 
        } else if (ch == '?') {

            auto it = upper_bound(val.begin(), val.end(), x);
            if (it == val.begin()) {
                cout << 0 << '\n';
            } else {
                int idx = com[*(--it)];
                cout << f.sum(idx) << '\n';
            }
        }
    }

    return 0;
}
