

// такс , смотри , условие задачки на фотке , можешь решить ее используя алгоритм в котором ты сначала строишь KD-дерева по точкам. 
// потом обновляешь значение точек в заданом прямоугоьлике , и делаешь запрос минимум по прямоугольнику


//такс , посмотри на свой предидущий запрос и улучши время его работы, ведь данный код ловит TL : 0.936 sec	31.89Mb	 

// давай вернемся к старой версии , только сделаем ленивые отложенные операции

// Решение: строим KD-дерево по фиксированному набору N точек (координаты и начальные значения).
//   В каждом узле:
//     - одна точка (x, y, curVal);
//     - bounding-box всего поддерева: minX, maxX, minY, maxY;
//     - minVal = минимум curVal по всему поддереву;
//     - lazyTag = пометка о том, что ВСЕ точки подкела нужно приравнять к tagVal.
//       (tagVal = -1 означает, что пометки нет).
//     - указатели на левое и правое поддеревья.

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


static const int MAXN = 262144;
static const long long INF = (long long)2e18;

// Структура для хранения исходных точек при построении KD-дерева
struct Point {
    long long x, y;
    long long val;
};

Point P[MAXN];
int  idxArr[MAXN]; // индексы точек при построении по алгор. "quickselect/median"

// Структура узла KD-дерева
struct Node {
    long long x, y;         // координаты точки, хранимой в этом узле
    long long val;          // текущая ценность именно этой точки
    long long minVal;       // минимум по всей точке + поддереву

    // Bounding-box всего поддерева:
    long long minX, maxX, minY, maxY;

    long long tag;          // lazy-метка: если != -1, то ВСЕ точки в этом поддереве должны иметь значение = tag
                            // (tag == -1 → значит, метки нет)

    int   lch, rch;         // индексы левого и правого ребёнка (−1, если нет)

    Node() {
        lch = rch = -1;
        tag = -1;
    }
} kd[MAXN];

int  build_ptr = 0; // следующий свободный индекс для нового узла

// Функция, которая строит KD-дерево "по месту" в массиве kd[].
// Принимает диапазон [l..r] в idxArr[], на котором лежат индексы точек P[].
// depth % 2 = 0 → делим по x, depth % 2 = 1 → делим по y.
// Возвращает индекс корня (в массиве kd[]).
int buildKD(int l, int r, int depth) {
    if (l > r) return -1;
    int mid = (l + r) >> 1;
    // Выбираем медиану по соответствующей координате:
    if ((depth & 1) == 0) {
        // по x
        nth_element(idxArr + l, idxArr + mid, idxArr + r + 1,
            [&](int a, int b) {
                return P[a].x < P[b].x;
            }
        );
    } else {
        // по y
        nth_element(idxArr + l, idxArr + mid, idxArr + r + 1,
            [&](int a, int b) {
                return P[a].y < P[b].y;
            }
        );
    }

    int myIndex = build_ptr++;
    int pid = idxArr[mid]; // индекс точки из исходного массива P[]

    // создаём узел:
    kd[myIndex].x = P[pid].x;
    kd[myIndex].y = P[pid].y;
    kd[myIndex].val = P[pid].val;
    kd[myIndex].tag = -1;
    // Bounding-box пока проинициализируем стандартно "под точку", остальное докидываем из детей:
    kd[myIndex].minX = kd[myIndex].maxX = kd[myIndex].x;
    kd[myIndex].minY = kd[myIndex].maxY = kd[myIndex].y;
    kd[myIndex].minVal = kd[myIndex].val;

    // Строим левого и правого ребёнка:
    kd[myIndex].lch = buildKD(l, mid - 1, depth + 1);
    kd[myIndex].rch = buildKD(mid + 1, r, depth + 1);

    // Обновляем bounding-box и minVal из детей:
    for (int ch : { kd[myIndex].lch, kd[myIndex].rch }) {
        if (ch == -1) continue;
        kd[myIndex].minX = min(kd[myIndex].minX, kd[ch].minX);
        kd[myIndex].maxX = max(kd[myIndex].maxX, kd[ch].maxX);
        kd[myIndex].minY = min(kd[myIndex].minY, kd[ch].minY);
        kd[myIndex].maxY = max(kd[myIndex].maxY, kd[ch].maxY);

        kd[myIndex].minVal = min(kd[myIndex].minVal, kd[ch].minVal);
    }
    return myIndex;
}

// "Push down" lazy-метки: если в kd[u].tag != -1, нужно
// присвоить tag всем вершинам-потомкам, обновить у них minVal и val.
void pushDown(int u) {
    if (u < 0) return;
    if (kd[u].tag == -1) return;
    long long T = kd[u].tag;
    // самому узлу всё уже присвоено (его val и minVal = T),
    // дальше распределяем метку детям:
    for (int ch : { kd[u].lch, kd[u].rch }) {
        if (ch < 0) continue;
        kd[ch].tag = T;
        kd[ch].val = T;
        kd[ch].minVal = T;
    }
    kd[u].tag = -1;
}

// Проверка: прямоугольник узла u полностью **вне** области [x1..x2]×[y1..y2]?
bool outside(int u,
             long long x1, long long y1, long long x2, long long y2)
{
    // если bbox(u).maxX < x1  или bbox(u).minX > x2
    // или bbox(u).maxY < y1  или bbox(u).minY > y2
    if ( kd[u].maxX < x1 || kd[u].minX > x2 ) return true;
    if ( kd[u].maxY < y1 || kd[u].minY > y2 ) return true;
    return false;
}

// Проверка: bounding-box узла u полностью **внутри** области [x1..x2]×[y1..y2]?
bool fullyInside(int u,
             long long x1, long long y1, long long x2, long long y2)
{
    if ( x1 <= kd[u].minX && kd[u].maxX <= x2
      && y1 <= kd[u].minY && kd[u].maxY <= y2 )
    {
        return true;
    }
    return false;
}

// Обновить (assign = присвоить) всем точкам в прямоугольнике [x1..x2]×[y1..y2] значение = V.
void updateRect(int u,
                long long x1, long long y1, long long x2, long long y2,
                long long V)
{
    if (u < 0) return;
    // 1) если bbox(u) полностью вне — ничего не делаем:
    if (outside(u, x1, y1, x2, y2)) {
        return;
    }
    // 2) если bbox(u) полностью внутри — "закрытая" область,
    //    присваиваем tag = V, minVal = V, val = V, и не спускаемся дальше:
    if (fullyInside(u, x1, y1, x2, y2)) {
        kd[u].tag    = V;
        kd[u].val    = V;
        kd[u].minVal = V;
        return;
    }
    // 3) Иначе — частично пересекается. 
    //    Сначала спустим свою метку вниз:
    pushDown(u);

    //    Поприменим к самой точке в узле, если она в прямоугольнике:
    if ( x1 <= kd[u].x && kd[u].x <= x2
      && y1 <= kd[u].y && kd[u].y <= y2 )
    {
        kd[u].val = V;
    }
    //    Рекурсивно заходим в детей:
    updateRect(kd[u].lch, x1, y1, x2, y2, V);
    updateRect(kd[u].rch, x1, y1, x2, y2, V);

    //    Восстанавливаем свой minVal = min( свой val, minVal(детей) )
    long long best = kd[u].val;
    if (kd[u].lch >= 0) best = min(best, kd[ kd[u].lch ].minVal);
    if (kd[u].rch >= 0) best = min(best, kd[ kd[u].rch ].minVal);
    kd[u].minVal = best;
}

// Запрос: найти минимум среди точек, лежащих в [x1..x2]×[y1..y2]. 
// Если внутри нет точек, вернёт INF.
long long queryRect(int u,
                    long long x1, long long y1, long long x2, long long y2)
{
    if (u < 0) return INF;
    // 1) если bbox(u) полностью вне — возвращаем INF
    if (outside(u, x1, y1, x2, y2)) {
        return INF;
    }
    // 2) если bbox(u) полностью внутри — можем сразу вернуть minVal поддерева
    if (fullyInside(u, x1, y1, x2, y2)) {
        return kd[u].minVal;
    }
    // 3) частично пересекается:
    //    спустим метку вниз, чтобы дети были в актуальном состоянии
    pushDown(u);

    //    проверим свою точку:
    long long ans = INF;
    if ( x1 <= kd[u].x && kd[u].x <= x2
      && y1 <= kd[u].y && kd[u].y <= y2 )
    {
        ans = kd[u].val;
    }
    //    рекурсивно ищем в детях:
    long long lef = queryRect(kd[u].lch, x1, y1, x2, y2);
    long long rig = queryRect(kd[u].rch, x1, y1, x2, y2);
    ans = min(ans, min(lef, rig));
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    for (int i = 0; i < N; i++) {
        long long xi, yi, vi;
        cin >> xi >> yi >> vi;
        P[i].x   = xi;
        P[i].y   = yi;
        P[i].val = vi;
        idxArr[i] = i;
    }
    // Построим KD-дерево из N точек (в узлах массива kd[]).
    build_ptr = 0;
    int root = buildKD(0, N - 1, 0);

    int M;
    cin >> M;
    while (M--) {
        char type;
        cin >> type;
        if (type == '=') {
            long long x1, y1, x2, y2, v;
            cin >> x1 >> y1 >> x2 >> y2 >> v;
            // На всякий, убедимся, что x1<=x2, y1<=y2
            if (x1 > x2) swap(x1, x2);
            if (y1 > y2) swap(y1, y2);
            updateRect(root, x1, y1, x2, y2, v);
        }
        else if (type == '?') {
            long long x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            if (x1 > x2) swap(x1, x2);
            if (y1 > y2) swap(y1, y2);
            long long ans = queryRect(root, x1, y1, x2, y2);
            if (ans == INF) {
                cout << "NO\n";
            } else {
                cout << ans << "\n";
            }
        }
    }
    return 0;
}
