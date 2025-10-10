
#include <iostream>
#include <numeric>  // Для std::gcd
#include <cmath>
using namespace std;

// Функция f(x) = (x+1)² mod n
long long f(long long x, long long n) {
    return ((x + 1) * (x + 1)) % n;
}

// Функция, реализующая идею алгоритма Полларда (rho-алгоритм)
// Используем начальное значение seed (например, 2)
long long pollard(long long n, long long seed = 2) {
    long long x = seed, y = seed, d = 1;
    
    // Выполняем ограниченное число итераций
    for (long long i = 0; i < 100000 && d == 1; i++) {
        x = f(x, n);
        y = f(f(y, n), n);
        d = std::gcd( abs(x - y), n );
        
        // Если найден нетривиальный делитель, возвращаем его
        if (d > 1 && d < n) {
            return d;
        }
    }
    
    // Если делитель не найден, возвращаем -1
    return -1;
}

int main() {
    long long n;
    cin >> n;
    
    // Если число четное, то ответ очевиден
    if ( n == 2){
        std::cout<< "IMPOSSIBLE" ; 
        return 0 ; 
    }

    if(n % 2 == 0) {
        cout << 2 << " " << n / 2;
        return 0;
    }
    
    // Пробуем найти делитель с помощью алгоритма Полларда
    long long factor = pollard(n, 2);
    
    // Если делитель не найден или алгоритм не обнаружил нетривиального делителя,
    // выводим IMPOSSIBLE
    if(factor == -1 || factor == n) {
        cout << "IMPOSSIBLE";
    } else {
        cout << factor << " " << n / factor;
    }
    
    return 0;
}
