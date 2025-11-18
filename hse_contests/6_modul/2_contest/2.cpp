#include <iostream>
#include <string>
#include <cstring>
#include <vector>
using namespace std;

const int N = 100010;

int Next[N][26];
bool is_end[N];int subtree_size[N];  
int cnt = 1;
bool sizes_dirty = true;


void calc_sizes(int v) {
    if ( is_end[v] ) {
        subtree_size[v] =1; 
    }else {
        subtree_size[v] = 0;
    }
    
    for (int c = 0; c < 26; c++) {
        if (Next[v][c] != -1) {
            int to = Next[v][c];
            calc_sizes(to);
            subtree_size[v] += subtree_size[to];
        }
    }
}


string find_kth(int k) {

    // if (sizes_dirty) {
    //     memset(subtree_size, 0, sizeof(subtree_size));
    //     calc_sizes(0);
    //     sizes_dirty = false;
    // }

    string result = "";
    int v = 0;
    
    while (k > 0) {
        if (is_end[v]) {
            k--;
            if (k == 0) break;
        }
        
        for (int c = 0; c < 26; c++) {
            if (Next[v][c] == -1) continue;
            
            int to = Next[v][c];
            if (subtree_size[to] < k) {
                k -= subtree_size[to];
            } else {
                result += char('a' + c);
                v = to;
                break;
            }
        }
    }
    
    return result;
}





void add(const string& s) {
    int v = 0;
    vector<int> path;

    for (char ch : s) {
        int c = ch - 'a';
        path.push_back(v);
        if (Next[v][c] == -1) {
            Next[v][c] = cnt++;
        }
        v = Next[v][c];
    }
    is_end[v] = true;
    path.push_back(v);


    for (int i = path.size() - 1; i >= 0; i--) {
        int node = path[i];
        int old_size = subtree_size[node];
        subtree_size[node] = is_end[node] ? 1 : 0;
        
        for (int c = 0; c < 26; c++) {
            if (Next[node][c] != -1) {
                subtree_size[node] += subtree_size[Next[node][c]];
            }
        }
        

        if (i > 0 && old_size == subtree_size[node]) {
            break;
        }
    }

}





int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    memset(Next, -1, sizeof(Next));
    memset(is_end, false, sizeof(is_end));
    memset(subtree_size, 0, sizeof(subtree_size));
    
    int n; cin >> n;
    
    for (int i = 0; i < n; i++) {
        string command;
        cin >> command;
        
        if (command[0] >= 'a' && command[0] <= 'z') {            
            add(command);            

        } else {            
            int k = stoi(command);
            cout << find_kth(k) << '\n';
        }
    }
    
    return 0;
}