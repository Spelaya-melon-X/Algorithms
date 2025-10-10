#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include "optimization.h"
using namespace std;

vector<int> mark;
stack<int> st;
vector<vector<int>> gr, obr_gr;
vector<int> comp;

void dfs(int v, vector<vector<int>>& gr) {
    if (mark[v]) return;
    mark[v] = 1;
    for (auto u : gr[v]) dfs(u, gr);
    st.push(v);
}

void dfs2(int v, vector<vector<int>>& obr_gr, int cc, vector<int>& comp) {
    comp[v] = cc;
    for (auto u : obr_gr[v]) {
        if (!comp[u]) dfs2(u, obr_gr, cc, comp);
    }
}

int main() {
    int n = readInt();
    int m = readInt();
    char colors[1000]; 
    readWord(colors); 


    gr.resize(2 * n);
    obr_gr.resize(2 * n);
    mark.assign(2 * n, 0);
    comp.assign(2 * n, 0);

    // Определяем допустимые цвета для каждой вершины
    vector<pair<char, char>> allowed(n);
    for (int i = 0; i < n; ++i) {
        if (colors[i] == 'R') allowed[i] = {'G', 'B'};
        else if (colors[i] == 'G') allowed[i] = {'R', 'B'};
        else allowed[i] = {'R', 'G'}; // Для 'B'
    }
// Обработка рёбер
for (int i = 0; i < m; ++i) {
    int u = readInt() - 1; // Переводим в 0-based
    int v = readInt() - 1;

    // Получаем допустимые цвета для u и v
    char u_color1 = allowed[u].first;
    char u_color2 = allowed[u].second;
    char v_color1 = allowed[v].first;
    char v_color2 = allowed[v].second;

    // Проверяем все 4 комбинации цветов
    // Комбинация 1: u_color1 и v_color1
    if (u_color1 == v_color1) {
        // Запрещаем (u_color1 ∧ v_color1) → добавляем (!u_color1 ∨ !v_color1)
        gr[2 * u].push_back(2 * v + 1);     // u_color1 → ¬v_color1
        obr_gr[2 * v + 1].push_back(2 * u);
        gr[2 * v].push_back(2 * u + 1);     // v_color1 → ¬u_color1
        obr_gr[2 * u + 1].push_back(2 * v);
    }

    // Комбинация 2: u_color1 и v_color2
    if (u_color1 == v_color2) {
        gr[2 * u].push_back(2 * v);         // u_color1 → ¬v_color2
        obr_gr[2 * v].push_back(2 * u);
        gr[2 * v + 1].push_back(2 * u + 1); // v_color2 → ¬u_color1
        obr_gr[2 * u + 1].push_back(2 * v + 1);
    }

    // Комбинация 3: u_color2 и v_color1
    if (u_color2 == v_color1) {
        gr[2 * u + 1].push_back(2 * v + 1); // u_color2 → ¬v_color1
        obr_gr[2 * v + 1].push_back(2 * u + 1);
        gr[2 * v].push_back(2 * u);         // v_color1 → ¬u_color2
        obr_gr[2 * u].push_back(2 * v);
    }

    // Комбинация 4: u_color2 и v_color2
    if (u_color2 == v_color2) {
        gr[2 * u + 1].push_back(2 * v);     // u_color2 → ¬v_color2
        obr_gr[2 * v].push_back(2 * u + 1);
        gr[2 * v + 1].push_back(2 * u);     // v_color2 → ¬u_color2
        obr_gr[2 * u].push_back(2 * v + 1);
    }
}

    // Первый проход DFS для порядка
    for (int i = 0; i < 2 * n; ++i) {
        if (!mark[i]) dfs(i, gr);
    }

    // Второй проход для компонент связности
    int cc = 0;
    while (!st.empty()) {
        int v = st.top();
        st.pop();
        if (!comp[v]) {
            dfs2(v, obr_gr, ++cc, comp);
        }
    }

    // Проверка на противоречия и формирование ответа
    string result(n, ' ');
    bool possible = true;
    for (int i = 0; i < n; ++i) {
        int var0 = 2 * i;     // Первый вариант цвета
        int var1 = 2 * i + 1; // Второй вариант цвета
        if (comp[var0] == comp[var1]) {
            possible = false;
            break;
        }
        // Выбираем цвет с большей компонентой
        result[i] = (comp[var0] > comp[var1]) ? allowed[i].first : allowed[i].second;
    }

    if (!possible) {
        writeWord("Impossible\n");
    } else {
        for (char c : result) writeChar(c);
        writeChar('\n');
    }

    return 0;
}