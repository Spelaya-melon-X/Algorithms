#include <iostream>
#include <vector>

using namespace std;

int main() {
    int a, b;
    cin >> a >> b;
    
    int k, l;
    cin >> k >> l;
    
    vector<int> v1(k);
    for (int i = 0; i < k; ++i) {
        cin >> v1[i];
    }
    
    vector<int> m2(l);
    for (int i = 0; i < l; ++i) {
        cin >> m2[i];
    }
    
    // DP-таблица: dp[i][j][turn] = true, если позиция (i, j) выигрышная для игрока turn
    // turn = 0 - первый игрок, turn = 1 - второй игрок
    vector<vector<vector<bool>>> dp(a + 1, vector<vector<bool>>(b + 1, vector<bool>(2, false)));
    
    // Базовый случай: если обе кучи пусты, текущий игрок проигрывает
    dp[0][0][0] = false; // Первый игрок не может сделать ход
    dp[0][0][1] = false; // Второй игрок не может сделать ход
    
    // Заполняем DP-таблицу
    for (int i = 0; i <= a; ++i) {
        for (int j = 0; j <= b; ++j) {
            // Ход первого игрока
            if (i > 0 || j > 0) {
                bool canWinFirst = false;
                for (int u : v1) {
                    if (i >= u && !dp[i - u][j][1]) { // Оставляем второму игроку проигрышную позицию
                        canWinFirst = true;
                        break;
                    }
                    if (j >= u && !dp[i][j - u][1]) { // Оставляем второму игроку проигрышную позицию
                        canWinFirst = true;
                        break;
                    }
                }
                dp[i][j][0] = canWinFirst;
                
                // Ход второго игрока
                bool canWinSecond = false;
                for (int u : m2) {
                    if (i >= u && !dp[i - u][j][0]) { // Оставляем первому игроку проигрышную позицию
                        canWinSecond = true;
                        break;
                    }
                    if (j >= u && !dp[i][j - u][0]) { // Оставляем первому игроку проигрышную позицию
                        canWinSecond = true;
                        break;
                    }
                }
                dp[i][j][1] = canWinSecond;
            }
        }
    }
    
    // Результат для начальной позиции (a, b)
    if (dp[a][b][0]) {
        cout << "First\n";
    } else {
        cout << "Second\n";
    }
    
    return 0;
}