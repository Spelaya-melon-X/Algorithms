
#include <algorithm>
#include <future>
#include <iostream>
#include <memory>
#include <vector>
#include <string>
using namespace std;

struct Node {
    int val;
    long long sum;
    int size;
    uint32_t pri;
    shared_ptr<Node> l, r;

    Node(int _v)
      : val(_v), sum(_v), size(1),
        pri((uint32_t)rand()<<16 ^ rand()),
        l(nullptr), r(nullptr) {}
};

shared_ptr<Node> clone(const shared_ptr<Node>& t) {
    return t ? make_shared<Node>(*t) : nullptr;
}


int sz(const shared_ptr<Node>& t) { return t ? t->size : 0; }

long long sm(const shared_ptr<Node>& t) { return t ? t->sum : 0; }

void recalc(shared_ptr<Node>& t) {
    if (!t) return;
    t->size = 1 + sz(t->l) + sz(t->r);
    t->sum  = t->val + sm(t->l) + sm(t->r);
}


void split(const shared_ptr<Node>& t, int k, shared_ptr<Node>& a, shared_ptr<Node>& b) {
    if (!t) { a = b = nullptr; return; }
    auto cur = clone(t);
    if (sz(cur->l) >= k) {
        split(cur->l, k, a, cur->l);
        b = cur;
    } else {
        split(cur->r , k - sz( cur->l) -  1, cur-> r,  b);
        a = cur;
    }
    recalc(a); recalc(b);
}



shared_ptr<Node> merge(const shared_ptr<Node>& a, const shared_ptr<Node>& b) {
    if (!a) return b;
    if (!b) return a;
    if (a->pri > b->pri) {
        auto cur = clone(a);
        cur->r = merge(cur->r, b);
        recalc(cur);
        return cur;
    } else {
        auto cur = clone(b);
        cur->l = merge(a, cur->l);
        recalc(cur);
        return cur;
    }
}



void print(shared_ptr<Node> t, int l, int r) {
    shared_ptr<Node> t1, t2, t3;
    split(t, r, t1, t3); split(t1, l, t1, t2);
    function<void(const shared_ptr<Node>&)> dfs = [&](auto u){
        if (!u) return;
        dfs(u->l);
        cout << u->val << ' ';
        dfs(u->r);
    };
    dfs(t2);
    t1 = merge(t1, t2); merge(t1, t3);
    cout << "\n";
}

long long summ(shared_ptr<Node> t, int l, int r) {
    shared_ptr<Node> t1, t2, t3;
    split(t, r, t1, t3); split(t1, l, t1, t2);
    long long ans = sm(t2);
    t1 = merge(t1, t2); merge(t1, t3);
    return ans;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    srand(712687126);

    int n; cin >> n;
    long long X1,A,B,M; cin >> X1 >> A >> B >> M;
    vector<int> X(n);
    X[0] = X1;
    for(int i=1;i<n;i++) X[i] = (A * X[i-1] + B) % M;

    shared_ptr< Node > root = nullptr;
    for(int x : X) root = merge(root, make_shared<Node>(x));

    vector< shared_ptr<Node> > versions;
    versions.push_back(root);

    int K; cin >> K;
    while(K--){
        string cmd; cin >> cmd;
        if(cmd[0]=='s'){
            int l,r; cin>>l>>r; --l;
            cout << summ(versions.back(), l, r) << "\n";
        }
        else if(cmd[0]== 'o'){
            int l,r; cin>>l>>r; --l;
            print(versions.back(), l, r);
        }
        else if(cmd[0]=='c'){
            int a,b,len; cin>>a>>b>>len;
            --a; --b;
            auto cur = versions.back();
            shared_ptr<Node> A1, A2, mid, B1, B2, trash;
            

            split(cur, a, A1, A2); split(A2, len, mid, A2);
        

            split(cur, b, B1, B2); split(B2, len, trash, B2);
            
            auto merged = merge(B1, mid);
            merged = merge(merged, B2);
            versions.push_back(merged);
        }
    }
    return 0;
}