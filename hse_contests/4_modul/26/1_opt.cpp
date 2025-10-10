#include <vector>
#include <unordered_map>
#include <optimization.h>

#define FAST_ALLOCATOR_MEMORY 1e8

using namespace std;

int Ver = 1;

struct Request {
    int j;
    int ans;
};

vector<vector<Request*>> requests;
vector<int> arr;

struct Node {
    int version;
    int j;
    int value;
    vector<int> changes;
};

vector<Node*> versions;
vector<Request*> reqs;
vector<int> answers;
void dfs(int a) {
    int temp;
    auto &v = versions[a];
    if (v->j != -1) {
        temp = arr[v->j];
        arr[v->j] = v->value;
    }

    for (auto &r : requests[v->version]) {
        r->ans = arr[r->j];
    }
    for (auto ch : v->changes) {
        dfs(ch);
    }
    if (v->j != -1)
        arr[v->j] = temp;
}

int main() {
    int n;
    int m;
    char req[10];
    requests.reserve(100002);
    answers.reserve(100002);
    while(!isEof()) {
        Ver = 1;

        for (auto ptr : versions) {
            if (ptr) delete ptr;
        }
        
        
        n = readInt();
        arr.clear();
        arr.resize(n+1);
        reqs.clear();
        
        for (int i = 1; i <= n; i++) {
            arr[i] = readInt();
        }
        
        requests.clear();
        m = readInt();
        
        versions.clear();
        versions.resize(m + 2, nullptr);
        requests.resize(m + 2);
        versions[1] = new Node{1, -1, -1, {}};

        vector<Request> all_requests;
        all_requests.reserve(m);
        
        int version;
        int j;
        int value;
        while (m--) {
            readWord(req);
            switch (req[0]) {
                case 'g':
                    version = readInt();
                    j = readInt();
                    all_requests.push_back({j, -1});
                    requests[version].push_back(&all_requests.back());
                    break;
                case 'c':
                    version = readInt();
                    j = readInt();
                    value = readInt();
                    auto new_node = new Node{++Ver, j, value};
                    versions[version]->changes.push_back(Ver);
                    versions[new_node->version] = new_node;
                    break;
            }
        }
        dfs(1);
        for (const Request& r : all_requests) { 
            writeInt(r.ans);
            writeChar('\n');
        }
    }
    return 0;
}