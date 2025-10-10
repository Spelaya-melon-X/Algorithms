
#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <random>
#include <unordered_map>
#include <memory>
#include <set>

using namespace std;

struct Node {
    int value, priority, size;
    bool reversed;
    Node *left, *right, *parent;
    
    Node(int val) : value(val), priority(rand()), size(1), reversed(false),
                   left(nullptr), right(nullptr), parent(nullptr) {}
};

inline int get_size(Node* node) {
    return node ? node->size : 0;
}

inline void update_size(Node* node) {
    if (node) {
        node->size = 1 + get_size(node->left) + get_size(node->right);
    }
}

inline void push_reverse(Node* node) {
    if (node && node->reversed) {
        node->reversed = false;
        swap(node->left, node->right);
        if (node->left) {
            node->left->reversed ^= 1;
        }
        if (node->right) {
            node->right->reversed ^= 1;
        }
    }
}

pair<Node*, Node*> split(Node* node, int key) {
    if (!node) return make_pair(nullptr, nullptr) ; 
    
    push_reverse(node);
    int left_size = get_size(node->left);
    if (key <= left_size) {
        auto [left, right] = split(node->left, key);
        node->left = right;
        if (right) right->parent = node;
        update_size(node);
        return make_pair(left, node) ; 
    } else {
        auto [left, right] = split(node->right, key - left_size - 1);
        node->right = left;
        if (left) left->parent = node;
        update_size(node);
        return make_pair(node, right) ; 
    }
}

Node* merge(Node* left, Node* right) {
    if (!left) return right;
    if (!right) return left;
    
    push_reverse(left);
    push_reverse(right);
    
    if (left->priority > right->priority) {
        left->right = merge(left->right, right);
        if (left->right){
            left->right->parent = left;
        }
        
        update_size(left);
        return left;
    } else {
        right->left = merge(left, right->left);
        if (right->left) {
            right->left->parent = right;
        }
        update_size(right);
        return right;
    }
}

Node* rotate_left(Node* node, int k) {
    if (!node) {
        return nullptr;
    }
    
    push_reverse(node);
    int n = node->size;
    k %= n;
    if (k == 0) {
        return node;
    }
    
    auto a = split(node, k);
    auto [left , right] = a; 
    return merge(right, left);
}

Node* get_root(Node* node) {
    while (node->parent) {
        node = node->parent;
    }
    return node;
}

void traverse(Node* node, vector<int>& result) {
    if (!node) return;
    push_reverse(node);
    traverse(node->left, result);
    result.push_back(node->value);
    traverse(node->right, result);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m; cin >> n >> m;
    
    vector<Node*> nodes(n);
    for (int i = 0; i < n; ++i) {
        nodes[i] = new Node(i + 1);
    }
    
    while (m--) {
        char cmd; cin >> cmd;
        
        if (cmd == '+') {
            int i, j; cin >> i >> j;i--; j--;
            
            auto root_i = get_root(nodes[i]);
            auto root_j = get_root(nodes[j]);
            
            if (root_i != root_j) {
                merge(root_i, root_j);
            }
        } else if (cmd == '!') {
            int i, k;cin >> i >> k;i--;
            
            auto node = nodes[i];
            auto root = get_root(node);
            
            auto new_root = rotate_left(root, k);
            if (new_root != root) {
                new_root->parent = nullptr;
            }
        } else if (cmd == '-') {
            int i, k;cin >> i >> k;i--;
            
            auto node = nodes[i];
            auto root = get_root(node);
            
            auto [left, right] = split(root, k);
            if (left) left->parent = nullptr;
            if (right) right->parent = nullptr;
        }
    }
    
    set<Node*> roots;
    for (auto node : nodes) {
        roots.insert(get_root(node));
    }
    
    vector<vector<int> > vvv;
    vvv.reserve(roots.size());
    for (auto root : roots) {
        vector<int> arr;
        traverse(root, arr);
        vvv.emplace_back(std::move(arr));
    }
    
    sort(vvv.begin(), vvv.end());
    
    cout << vvv.size() << "\n";
    for (auto& arr : vvv) {
        cout << arr.size();
        for (int val : arr) {
            cout << " " << val;
        }
        cout << "\n";
    }
    
    for (auto node : nodes) {
        delete node;
    }
    
    return 0;
}