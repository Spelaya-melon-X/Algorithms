#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int knapsackPTAS(vector<pair<int, int>>& items, int W, double epsilon) {
    int n = items.size();
    int maxValue = 0;
    // выборка максимального элемента по его ценности 
    for (auto& item : items) {
        maxValue = max(maxValue, item.first);
    }

    double K = epsilon * maxValue / n; // max / n -> среднее значение , а вот eps - это часть приближения 
    vector<pair<int, int>> scaledItems;
    for (auto& item : items) {
        /* 
        то есть елси выше среднего , то тогжа у нас буду значания >=1 , иначе 0 
        */
        int scaledValue = static_cast<int>(item.first / K); // узнавание сколько оно весит от максимального и округяляя веерх 
        scaledItems.emplace_back(scaledValue, item.second); // new value and old weight 
    }

    int maxScaledValue = 0;
    for (auto& item : scaledItems) {
        maxScaledValue += item.first;
    }

    vector<int> dp(maxScaledValue + 1, INT_MAX);
    dp[0] = 0;

    for (auto& item : scaledItems) {
        for (int j = maxScaledValue; j >= item.first; --j) {
            if (dp[j - item.first] != INT_MAX) { // so while value not equivalse Max element , dp go 
                dp[j] = min(dp[j], dp[j - item.first] + item.second); // пересчет динамики
            }
        }
    }

    for (int val = maxScaledValue; val >= 0; --val) {
        if (dp[val] <= W) {
            return static_cast<int>(val * K);
        }
    }

    return 0;
}

int main() {
    vector<pair<int, int>> items = {{60, 10}, {100, 20}, {120, 30}};
    int W = 50;
    double epsilon = 0.1;

    int approx = knapsackPTAS(items, W, epsilon);
    cout << "Approximate value: " << approx << endl;
    return 0;
}
