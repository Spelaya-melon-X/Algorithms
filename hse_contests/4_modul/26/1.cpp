#include <iostream>
#include <vector>
#include <string>

using namespace std;

/* 
- create - &#119886;&#119894;[&#119895;] = &#119909; &#8212; создать из &#119894;-й версии новую, в которой &#119895;-й элемент равен &#119909;, а остальные
элементы такие же, как в &#119894;-й версии.
- get &#119886;&#119894;[&#119895;] &#8212; сказать, чему равен &#119895;-й элемент в &#119894;-й версии.

idea : 
по сути  мы должны создать vector , и во время того , как идет добавление создавать новую версию , то есть допустим есть какой-то вектор из векторов ,
 который нужен для поддеержания поддержания версий , а также есть вектор , который из элементов из версии + новый элемент , плюс для того , чтобы ебаться с тем , 
 чтобы перевыделять память - мы будем это все строить на vector 
*/

struct Node {
    int value;
    Node* L, * R;
    
    Node(int val) : value(val), L(nullptr), R(nullptr) {}
    Node(Node* l, Node* r) : L(l), R(r), value(0) {}
};

vector<Node*> versions;
int array_size;

Node* build(const vector<int>& data, int l, int r) {
    if (l == r) {
        return new Node(data[l-1]);
    }
    int mid = (l + r) / 2;

    Node* l_c = build(data, l, mid);
    Node* r_c = build(data, mid+1, r);

    return new Node(l_c, r_c);
}

Node* update_version(Node* node, int l, int r, int j, int x) {
    if (l == r) {
        return new Node(x);
    }

    int mid = (l + r) / 2;

    if (j <= mid) {
        Node* new_left = update_version(node->L, l, mid, j, x);
        return new Node(new_left, node->R);

    } else {
        Node* new_right = update_version(node->R, mid+1, r, j, x);
        return new Node(node->L, new_right);
    }
}

int get_value(Node* node, int l, int r, int j) {
    if (l == r) {
        return node->value;
    }

    int mid = (l + r) / 2;

    if (j <= mid) {
        return get_value(node->L, l, mid, j);
    } else {
        return get_value(node->R, mid+1, r, j);
    }
}

void create(int i, int j, int x) {

    Node* new_root = update_version(versions[i], 1, array_size, j, x);
    versions.push_back(new_root);
}

int get(int i, int j) {
    return get_value(versions[i], 1, array_size, j);
}



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n; cin >> n;
    vector<int > fir(n);
    for ( int i = 0; i < n; ++i) {
        cin >> fir[i];
    }
    
    array_size = n;
    versions.push_back(build(fir, 1, n));
    
    int m; cin >> m;
    while (m--) {
        string cmd; cin >> cmd;
        if (cmd == "create") {
            int i, j, value; cin >> i >> j >> value;
            create(i - 1, j, value);
        } else if (cmd == "get") {
            int i, j; cin >> i >> j;
            cout << get(i - 1, j);
            cout << flush; cout << endl ; 
        }
    }


    // create(0, 0, 52) ; 
    // vector<int> test_2 = versions[1] ; 
    // for (auto e : test_2){
    //     cout << e << " " ; 
    // }

    // get(0, 0) ; 
    // get(1,0) ; 


    return 0;
}