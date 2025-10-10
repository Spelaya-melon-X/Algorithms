#include <iostream>
#include <vector>
#include "optimization.h"
using namespace std;

using ll = long long;
const int MAXN = 1'000'00;

struct SegmentTree {
    int size;
    vector<ll> tree;

    SegmentTree(int n) : size(n), tree(2 * n, 0) {}


    void build() {
        for (int i = size - 1; i > 0; --i) {
            tree[i] = tree[2 * i] + tree[2 * i + 1];
        }
    }

    ll query(int l, int r) const {
        ll res = 0;
        for (l += size, r += size; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res += tree[l++];
            if (r & 1) res += tree[--r];
        }
        return res;
    }

    void update(int idx, int value) {
        idx += size;
        tree[idx] += value;
        for (idx >>= 1; idx >= 1; idx >>= 1) {

            tree[idx] = tree[2 * idx] + tree[2 * idx + 1];
        }
    }
};

int main() {
    int n;
    while ((n = readInt()) != 0) {
        SegmentTree st(MAXN); 
        vector<int> levels(n, 0); 

        for (int i = 0; i < n; i++) {
            int x = readInt(), y = readInt();

            int level = st.query(0, x + 1); 
            if (level < n) { 
                levels[level]++;
            }

            st.update(x, 1);
        }


        for (int i = 0; i < n; i++) {
            writeInt(levels[i], '\n');
        }
        flush(); 
    }

    return 0;
}