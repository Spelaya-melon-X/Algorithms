    #include <iostream>
    #include <vector> 
    #include <algorithm>
    #include <numeric>
    #include <stack> 

    using namespace std;
    using ll = long long;

    struct Treee {
        int n;
        vector<int> t;

        Treee(int _n): n(_n), t(4*n, 0) {}

        void build(int v, int tl, int tr, const vector<int>& a) {
            if (tl == tr) {
                t[v] = a[tl];
            } else {
                int tm = (tl + tr) >> 1;
                build(v<<1, tl, tm, a);
                build(v<<1|1, tm+1, tr, a);

                t[v] = max(t[v<<1], t[v<<1|1]);
            }
        }

        void update(int v, int tl, int tr, int pos, int val) {
            if (tl == tr) {
                t[v] = val;
            } else {
                int tm = (tl + tr) >> 1;
                if (pos <= tm){
                    update(v<<1, tl, tm, pos, val);
                }
                else{
                    update(v<<1|1, tm+1, tr, pos, val);
                }

                t[v] = max(t[v<<1], t[v<<1|1]);
            }
        }

        int find_first(int v, int tl, int tr, int l, int x) {
            if (tr < l || t[v] < x) {
                return -1;
            }
            if (tl == tr) {
                return tl;
            }
            int tm = (tl + tr) >> 1 , res = -1;
            if (l <= tm) {
                res = find_first(v<<1, tl, tm, l, x);
                if (res != -1) { 
                    return res;
                }
                return find_first(v<<1|1, tm+1, tr, l, x);
            } else {
                return find_first(v<<1|1, tm+1, tr, l, x);
            }
        }
    };

    int main(){
        ios::sync_with_stdio(false);
        cin.tie(nullptr);

        int n, m; cin >> n >> m;
        vector<int> a(n+1);
        for (int i = 1; i <= n; i++) {
            int temp ; cin>> temp; a[i] = temp;
        }

        Treee st(n);
        st.build(1, 1, n, a);

        while (m--) {
            int type, i, x; cin >> type >> i >> x;
            if (type == 0) {
                st.update(1, 1, n, i, x);
            } else {
                int ans = st.find_first(1, 1, n, i, x);
                cout << ans << "\n";
            }
        }
        return 0;
    }
