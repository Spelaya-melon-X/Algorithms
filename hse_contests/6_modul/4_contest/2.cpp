#include <iostream> 
#include <vector> 
#include <map> 
#include <string>
using namespace std;

struct Suff {
    struct NOde {
        int link = -1 , len = 0;
        map  <char,int> next ;
    };

    vector<NOde> st;
    int last;

    Suff(int n) { 
        st.reserve(2*n); st.push_back(NOde()); last = 0;
    }

    long long add_char(char c) {
        int cur = st.size();
        st.push_back(NOde());
        st[cur].len =  st[last].len  + 1;

        int p = last;

        while (p !=  -1 &&  !st[p].next.count(c)) {
            st[p].next[c] = cur;
            p = st[p].link;
        }

        if (p == -1) 
            st[cur].link = 0;
        else {
            int q = st[p].next[c];
            if (st[p].len + 1 == st[q].len) {
                st[cur].link = q;

            } 
            else {
                int clone = st.size();

                st.push_back(st[q]);
                st[clone].len = st[p].len + 1;

                while (p != -1 && st[p].next[c] == q) {
                    st[p].next[c] = clone;
                    p = st[p].link;

                }

                st[q].link = st[cur].link = clone;
            }
        }

        last = cur;

        return st[cur].len - st[st[cur].link].len;
    }

};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s; cin >> s;

    Suff Suff(s.size());

    long long total = 0;
    for (char c : s) {
        total += Suff.add_char(c);
        cout << total << std::endl ;
    }
}
