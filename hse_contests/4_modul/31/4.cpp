
// такс б можеШЬ РЕШИТЬ данную задачу на С++ , идея примерна такая , тебе нужно найти мин значение функции для каждой вершины графа , используя пошлагове присовение значения через очередь и анализ сосдених вершиЕ также нужно поддерживать корзину . для текущий значеницй mex , и поседоваельно обговлять состояния вершин с учетом их исх ребер 
#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vi> g(n), rg(n);
    vi outdeg(n, 0);
    for(int i = 0; i < m; i++){
        int x, y;
        cin >> x >> y;
        --x; --y;
        g[x].push_back(y);
        rg[y].push_back(x);
        outdeg[x]++;
    }
    // Максимальный возможный mex <= max_outdeg + 1
    int maxd = 0;
    for(int v = 0; v < n; v++) 
        maxd = max(maxd, outdeg[v]);
    int MAXK = maxd + 1;

    // seen[v][c] = true, если среди уже присвоенных детям v встречено значение c
    vector<vector<char>> seen(n);
    vi mex(n, 0);
    for(int v = 0; v < n; v++){
        seen[v].assign(outdeg[v] + 2, 0);
    }

    // Кол-во уже присвоенных (определённых) детей
    vi rem_assigned(n, 0);
    // Флаги "уже в очереди" для текущего k
    vector<char> inq(n, 0);
    // Текущие метки вершин (-1 = не определено)
    vi f(n, -1);
    vector<char> assigned(n, 0);

    // Buckets: bucket[k] = список вершин с текущим mex == k
    vector<vi> bucket(MAXK + 1);
    for(int v = 0; v < n; v++){
        bucket[0].push_back(v);
    }

    // Основной цикл по k = 0..MAXK
    for(int k = 0; k <= MAXK; k++){
        if(bucket[k].empty()) continue;

        // Для каждого k заводим отдельный good_count и good_flag
        vi good_count(n, 0);
        vector<char> good_flag(n, 0);
        queue<int> q;

        // Сначала садим в очередь все v с mex==k и все дети уже "удовлетворены" (rem_assigned == outdeg)
        for(int v : bucket[k]){
            if(!assigned[v] && rem_assigned[v] == outdeg[v]){
                q.push(v);
                inq[v] = 1;
            }
        }

        // Обрабатываем очередь
        while(!q.empty()){
            int v = q.front(); q.pop();
            inq[v] = 0;
            if(assigned[v]) continue;
            assigned[v] = 1;
            f[v] = k;

            // Для каждого родителя p вершины v
            for(int p : rg[v]){
                if(assigned[p]) continue;

                // === 1) обновляем seen/p->mex ===
                if(f[v] < (int)seen[p].size() && !seen[p][f[v]]){
                    seen[p][f[v]] = 1;
                    // подтягиваем mex[p]
                    while(mex[p] < (int)seen[p].size() && seen[p][mex[p]])
                        mex[p]++;
                    // кладём p в bucket нового mex
                    if(mex[p] <= MAXK)
                        bucket[mex[p]].push_back(p);
                }

                // === 2) обновляем rem_assigned ===
                rem_assigned[p]++;
                // если после этого p удовлетворяет условиям при текущем k
                if(mex[p] == k && rem_assigned[p] + good_count[p] == outdeg[p] && !inq[p]){
                    q.push(p);
                    inq[p] = 1;
                }

                // === 3) помечаем p как good_flag и «распространяем» это дальше ===
                if(!good_flag[p]){
                    good_flag[p] = 1;
                    // для каждого предка v2,p->другой уровень
                    for(int v2 : rg[p]){
                        if(assigned[v2]) continue;
                        good_count[v2]++;
                        if(mex[v2] == k && rem_assigned[v2] + good_count[v2] == outdeg[v2] && !inq[v2]){
                            q.push(v2);
                            inq[v2] = 1;
                        }
                    }
                }
            }
        }
        // Освобождаем очередь-флаги inq для следующего k
        // (они уже сняты внутри)
    }

    // Все ещё не определённые получат -1 по условию
    // Выводим f[0..n-1]
    for(int i = 0; i < n; i++){
        cout << f[i] << (i + 1 < n ? ' ' : '\n');
    }
    return 0;
}
