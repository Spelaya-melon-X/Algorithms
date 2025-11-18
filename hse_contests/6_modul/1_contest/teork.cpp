#include <vector>
using namespace std;

struct Vertex {
    static const int ALPHABET = 26;
    vector<int> next;
    bool isEnd;
    Vertex() : next(ALPHABET, -1), isEnd(false) {}
};

vector<Vertex> trie(1); 
int root = 0;


void add(const vector<int> &s) {
    int v = root;
    for (int c : s) {
        if (trie[v].next[c] == -1) {
            trie[v].next[c] = trie.size();
            trie.emplace_back();
        }
        v = trie[v].next[c];
    }
    trie[v].isEnd = true;
}

bool dfs_min_string(int v, vector<int> &path, vector<int> &res) {
    if (trie[v].isEnd) {
        res = path;
        return true;
    }
    for (int c = 0; c < Vertex::ALPHABET; c++) {
        if (trie[v].next[c] != -1) {
            path.push_back(c);
            if (dfs_min_string(trie[v].next[c], path, res))
                return true;
            path.pop_back();
        }
    }
    return false;
}

vector<int> lowerbound(const vector<int> &s) {
    vector<int> path;          
    vector<int> res;           
    int v = root;

    for (int i = 0; i < (int)s.size(); i++) {
        int c = s[i];
        if (trie[v].next[c] != -1) {
            path.push_back(c);
            v = trie[v].next[c];
            continue;
        }
        for (int nc = c + 1; nc < Vertex::ALPHABET; nc++) {
            if (trie[v].next[nc] != -1) {
                path.push_back(nc);
                v = trie[v].next[nc];
                dfs_min_string(v, path, res);
                return res;
            }
        }
        while (!path.empty()) {
            int last = path.back();
            path.pop_back();
            v = root;
            for (int ch : path)
                v = trie[v].next[ch];
            for (int nc = last + 1; nc < Vertex::ALPHABET; nc++) {
                if (trie[v].next[nc] != -1) {
                    path.push_back(nc);
                    v = trie[v].next[nc];
                    dfs_min_string(v, path, res);
                    return res;
                }
            }
        }
        return {};
    }
    if (trie[v].isEnd)
        return s;
    dfs_min_string(v, path, res);
    return res;
}
