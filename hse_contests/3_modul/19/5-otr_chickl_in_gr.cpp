#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

const int INF = 1e9;

struct Edge {
    int from, to, weight;
};

int main() {
    int n;
    cin >> n;

    vector<Edge> edges;
    vector<vector<int>> matrix(n, vector<int>(n, INF));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            string s;
            cin >> s;
            if (s == "max") {
                matrix[i][j] = INF;
            } else {
                matrix[i][j] = stoi(s);
                if (i != j && matrix[i][j] < INF) {
                    edges.push_back({i, j, matrix[i][j]});
                }
            }
        }
    }

    vector<int> dist(n, 0), parent(n, -1);
    int x = -1;

    for (int i = 0; i < n; ++i) {
        x = -1;
        for (auto e : edges) {
            if (dist[e.to] > dist[e.from] + e.weight) {
                dist[e.to] = dist[e.from] + e.weight;
                parent[e.to] = e.from;
                x = e.to;  // запоминаем последнюю обновленную вершину
            }
        }
    }

    if (x == -1) {
        cout << "Отрицательных циклов нет\n";
    } else {
        cout << "Есть отрицательный цикл: ";
        // Идем вверх по предкам, чтобы попасть внутрь цикла
        for (int i = 0; i < n; ++i) {
            x = parent[x];
        }

        // Восстанавливаем сам цикл
        vector<int> cycle;
        for (int v = x; ; v = parent[v]) {
            cycle.push_back(v);
            if (v == x && cycle.size() > 1) break;
        }
        reverse(cycle.begin(), cycle.end());

        for (int v : cycle) {
            cout << v + 1 << " ";
        }
        cout << endl;
    }

    return 0;
}
