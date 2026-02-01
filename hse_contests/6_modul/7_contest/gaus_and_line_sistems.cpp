#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

template <typename T>
bool isEqual(T a, T b) {
    return abs(a - b) < 1e-9;
}

template <typename T>
void print_matrix(const vector<vector<T>>& m) {
    for (int i = 0; i < m.size(); i++) {
        for (int j = 0; j < m[0].size(); j++) {
            cout << m[i][j] << " ";
        }
        cout << "\n";
    }
}




template <typename T>
vector<vector<T> > get_expanded_matrix(vector<vector<T>> &A, vector<T> &b) {
    int n = A.size();

    vector<vector<T>> a(n, vector<T>(n + 1));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = A[i][j];
        }
        a[i][n] = b[i];
    }

    return a;
}


template <typename T>
vector<vector<T> > get_triangular_matrix (vector<vector<T>> &A, vector<T> &b) {
    int n = A.size();
    vector<vector<T>> a = get_expanded_matrix(A, b);

    // Прямой ход для получения ТРЕУГОЛЬНОЙ матрицы
    for (int i = 0; i < n; i++) {
        
        int j = i; // Ищем строку с ненулевым элементом в i-м столбце (начиная с i-й строки)
        while (j < n && isEqual(a[j][i], static_cast<T>(0.0))) {   j++; }
        
        if (j == n) { throw runtime_error("Матрица вырождена (определитель = 0)"); }
    
        if (j != i) { swap(a[i], a[j]); }
        
        for (int j = i + 1; j < n; j++) { // Зануляем i-й столбец в строках НИЖЕ текущей (j > i)
            if (!isEqual(a[j][i], static_cast<T>(0.0))) {
                T coef = a[j][i] / a[i][i];
                for (int k = i; k <= n; k++) {  // начиная с i, а не с 0!
                    a[j][k] -= a[i][k] * coef;
                }
            }
        }
    }

    return a;
}

template <typename T>
vector<T> get_solution_vector_from_triangular_matrix(vector<vector<T>> A, vector<T> b) {
    int n = A.size();
    vector<vector<T>> a = get_triangular_matrix(A, b);
    vector<T> x(n); // Обратный ход: восстановление решения из треугольной матрицы
    for (int i = n - 1; i >= 0; i--) {
        x[i] = a[i][n];
        for (int j = i + 1; j < n; j++) {
            x[i] -= a[i][j] * x[j];
        }
        x[i] /= a[i][i];
    }
    return x;
}

// ВАРИАНТ 2: Получение ДИАГОНАЛЬНОЙ матрицы (как в конспекте строка 9)
template <typename T>
vector<T> get_solution_vector_from_diagonal_matrix(vector<vector<T>> A, vector<T> b) {
    int n = A.size();
    vector<vector<T>> a = get_expanded_matrix(A, b);

    for (int i = 0; i < n; i++) {
        int j = i;
        while (j < n && isEqual(a[j][i], static_cast<T>(0.0)))  {
            j++;
        }
        
        if (j == n) { throw runtime_error("Матрица вырождена (определитель = 0)"); }
        
        if (j != i) { swap(a[i], a[j]); }
        
        for (int j = 0; j < n; j++) { // Зануляем i-й столбец во ВСЕХ других строках (j != i)
            if (j != i && !isEqual(a[j][i], static_cast<T>(0.0))) {
                T coef = a[j][i] / a[i][i];
                for (int k = i; k <= n; k++) {  // начиная с i!
                    a[j][k] -= a[i][k] * coef;
                }
            }
        }
    }

    vector<T> x(n);
    for (int i = 0; i < n; i++) {
        x[i] = a[i][n] / a[i][i];
    }
    
    return x;
}


// full guass 
template <typename T>
vector<T> gauss(vector<vector<T>> A, vector<T> b) {
    int n = A.size();

    
    if (n != b.size()) {
        throw runtime_error("Размеры A и b не совпадают");
    }

    vector<vector<T>> a(n, vector<T>(n + 1));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = A[i][j];
        }
        a[i][n] = b[i];
    }

    cout << "Начальная матрица:\n";
    print_matrix(a);

    
    for (int i = 0; i < n; i++) {
        
        if (isEqual(a[i][i], 0.0)) {
            int j = i + 1;  
            while (j < n && isEqual(a[j][i], 0.0)) {
                j++;
            }
            
            if (j == n) {
                throw runtime_error("Матрица вырождена (определитель = 0)");
            }
            
            
            swap(a[i], a[j]);
            cout << "Поменяли строки " << i << " и " << j << ":\n";
            print_matrix(a);
        }

        
        T diag = a[i][i];
        if (!isEqual(diag, 0.0)) {
            for (int k = i; k <= n; k++) {
                a[i][k] /= diag;
            }
        }

        
        for (int j = 0; j < n; j++) {
            if (j != i && !isEqual(a[j][i], 0.0)) {
                T coef = a[j][i] / a[i][i];
                for (int k = i; k <= n; k++) {
                    a[j][k] -= a[i][k] * coef;
                }
                cout << "Вычли строку " << i << " из строки " << j << ":\n";
                print_matrix(a);
            }
        }
    }

    
    vector<T> ans(n);
    for (int i = 0; i < n; i++) {
        ans[i] = a[i][n];
    }

    return ans;
}


int main() {

    
    vector<vector<long double>> A = {{2, 1}, {1, 3}};
    vector<long double> b = {5, 6};
    

    
    try {
        vector<long double> x1 = get_solution_vector_from_triangular_matrix(A, b);
        cout << "Треугольная форма:\n";
        cout << "x = " << x1[0] << ", y = " << x1[1] << endl;
        
        vector<long double> x2 = get_solution_vector_from_diagonal_matrix(A, b);
        cout << "\nДиагональная форма:\n";
        cout << "x = " << x2[0] << ", y = " << x2[1] << endl;
        
        // Проверка
        cout << "\nПроверка:\n";
        cout << "2*" << x1[0] << " + " << x1[1] << " = " << 2*x1[0] + x1[1] 
             << " (ожидалось 5)\n";
        cout << x1[0] << " + 3*" << x1[1] << " = " << x1[0] + 3*x1[1] 
             << " (ожидалось 6)\n";
    }
    catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }
    
    return 0;
}

