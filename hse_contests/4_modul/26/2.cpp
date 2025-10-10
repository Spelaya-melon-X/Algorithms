#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;



struct Operation {
    int type;    // Тип операции: 1 (добавление) или -1 (удаление)
    int t;       // Базовая версия
    int m;       // Значение для добавления (только для type=1)
    int index;   // Порядковый номер операции
};

struct Version {
    deque<int> q;           // Состояние очереди в этой версии
    vector<int> children;    // Список дочерних версий
};

vector<Version> versions;    // Все версии очереди
vector<Operation> operations; // Все операции
vector<pair<int, int>> results; // Результаты (индекс операции, значение)

void dfs(int v_idx) {
    Version& current = versions[v_idx];
    
    // Если это операция удаления, сохраняем результат
    if (operations[v_idx].type == -1 && !current.q.empty()) {
        int val = current.q.front();
        results.emplace_back(operations[v_idx].index, val);
    }
    
    // Обрабатываем дочерние версии
    for (int child_idx : current.children) {
        // Создаем копию состояния очереди
        versions[child_idx].q = current.q;
        
        // Применяем операцию к копии
        if (operations[child_idx].type == 1) {
            versions[child_idx].q.push_back(operations[child_idx].m);
        } else {
            if (!versions[child_idx].q.empty()) {
                versions[child_idx].q.pop_front();
            }
        }
        
        // Рекурсивно обрабатываем дочернюю версию
        dfs(child_idx);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    
    // Инициализация нулевой версии (пустая очередь)
    versions.resize(n + 1);
    operations.resize(n + 1);
    operations[0] = {0, -1, -1, 0};
    
    // Чтение операций
    for (int i = 1; i <= n; ++i) {
        int operation_type;  // Переименованная переменная
        cin >> operation_type;
        
        if (operation_type == 1) {
            int t, m;
            cin >> t >> m;
            operations[i] = {1, t, m, i};
            versions[t].children.push_back(i);
        } else {
            int t;
            cin >> t;
            operations[i] = {-1, t, -1, i};
            versions[t].children.push_back(i);
        }
    }
    
    // Обход графа версий
    dfs(0);
    
    // Сортировка результатов по порядку операций
    sort(results.begin(), results.end());
    
    // Вывод результатов
    for (const auto& res : results) {
        cout << res.second << '\n';
    }
    
    return 0;
}