#include <iostream>
#include <vector>
#include <string>
#include <cstring>
using namespace std;

const int N = 100010;

int Next[N][26];
int word_id[N];  
int cnt = 1;


// вот так нужно добавлять слова в бор 
void add(const string& s, int id) {
    int v = 0;
    for (char ch : s) {
        int c = ch - 'a';
        if (Next[v][c] == -1) {
            Next[v][c] = cnt++;
        }
        v = Next[v][c];
    }
    word_id[v] = id;  
}


// фукнция которая находит слова в тексте и помечает найденные - как нашеол / не нашел 
void wow(std::string &text , vector<bool> &found) {
    for (int start = 0; start < text.size(); start++) {
        int v = 0;
        for (int pos = start; pos < text.size(); pos++) {
            int c = text[pos] - 'a';
            if (Next[v][c] == -1) break;
            
            v = Next[v][c];
            if (word_id[v] != -1) {
                found[word_id[v]] = true;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string text;
    getline(cin, text);
    int M; cin >> M;
    
    memset(Next, -1, sizeof(Next));
    memset(word_id, -1, sizeof(word_id));
    
    vector<string> words(M);
    vector<bool> found(M, false);
    
    
    for (int i = 0; i < M; i++) {
        cin >> words[i];
        add(words[i], i);
    }
    
    wow(text, found);

    
    for (int i = 0; i < M; i++) {
        cout << (found[i] ? "Yes" : "No") << '\n';
    }
    
    return 0;
}