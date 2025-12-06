#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;
const int N = 1000 ; 
std::vector<int> is(N + 1) ;


template <typename  T >  
void bool_test(bool(*func) (T) , T obj) {
    std::cout << "function result is : "  <<  ( func(obj) ?  "True" : "False" ) << "\n" ; 
}

template<typename T>
void int_test(int (*func)(T), T obj) {
    std::cout << "function result is: " << func(obj) << "\n";
}

template<typename T, typename... Args>
void int_test(int (*func)(T, Args...), T obj, Args... args) {
    std::cout << "function result is: " << func(obj, args...) << "\n";
}

void sieve_Er_nloglogn() { // получается массив is , где is[x] = 1 если x простое
    is[1] = 1 ;
    for ( int x = 2 ; x * x <= N ; x++) {
        if (!is[ x]) {
            for ( int y = x * x ; y <= N ; y += x) {
                is[y] = 1 ;
            }
        }
    }
}


vector<int> inv( N + 1 , 0 );  // p = p /a * a + p % a 
void inv_a(int p ) {
    inv[1] = 1 ;
    for (int a = 2 ;a <= N; a++) {
        inv[a] = p/a * a  * ( - inv[p%a]) ; 
    }
}



std::vector<int> d(N + 1 , -1) ; // d[x] = the smallest prime divisor of x
std::vector<int> primes ;
void sieve_Er_n() {
    for ( int y = 2 ; y <= N ;y++) {
        if ( d[y] == - 1) {
            primes.push_back(y) ;
            d[y] = y ;
        }
        for ( int x = 0 ; x < primes.size() && primes[x] <= d[y] && y * primes[x] <= N ; x++) {
            d[y * primes[x]] = primes[x] ;
        }
    }
}

void sieve_Er_n_2 (){
    for ( int i = 2 ; i <= N ; i++) {
        if (d[i] == -1 ) {
            d[i] = primes.size() ;  // <-- index 
            primes.push_back(i) ;
        }
    }
    for ( int i = 2 ; i <= N ; i++) {
        for ( int j = 0 ; j < primes.size() && primes[j] <= d[i] && i * primes[j] <= N ; j++) {
            d[i * primes[j]] = primes[j] ; 
        }
    }
}


int gcd(int a , int b ) {
    return b == 0 ? a :  gcd( b, a % b ); 
}

// todo : 
// vector<int> deg ;  
// void  degn( int x ) {
//     deg[n] = d[ x \ p[x] ] == d[x] ? deg[p[x]] + 1 : 1 ;
// }


int gcd_2( int a , int b) {
    while (b) {
        b = a % b ;
        a = b ; 
        swap ( a , b ) ;
    }
    return a ;
}

// todo: 
// a^{-1} =_p = a^(p - 2) -- про деление

// X ^Y  =_p = Ans  , Y  - не довать никому ( sqrt p ) log y зарпятать , 

// КТО : система , по модулю p_i : x =_P_i = a_i   ( работает за sqrt p_i )

// RSA : 

// Prim factorization : 0 , 1 ,2 , ... p - 1 g = { g^0 , g^1 , g^2 , ... g^(p - 1) } => g маленькое число   

std::pair<int,int > Evclid(int a , int b ) {
    if ( b == 0 ) {
        return {1 ,0}; 
    }
    auto [x,y] = Evclid(b , a % b) ;  // x * b + y( a - b |a/b|)
    return {y , x - y * (a / b)} ;
}


int obr_evclid( int a , int m  ) // a * x + m * y = 1 => x = a^-1 mod m
{
    auto [x,y] = Evclid(a , m) ; 
    return (x + m ) % m ; 
}

int pow_a( int a , int n ) { // a^n = ( a^ 2)^ (n / 2 ) * ( 1 or a ) - за log n 
    int res = 1 ; 
    while ( n > 0) {
        if ( n % 2 == 1) {
            res *= a ; 
        }
        a *= a ; 
        n /= 2 ;
    }
    return res ;
}

int sum_a_log ( int a, int n) {
    int res = 0; 
    while ( n > 0) {
        if ( n % 2 == 1)  {
            res += a; 
        }
        a += a; 
        n /= 2; 
    }
    return res ; 
}

const int MOD = 1e9 + 7;
// a * b = k * m + r  => r = a * b - k * m => k = a * b/ m +- 1 
long double fast( int a , int b ) {
    long double res = 1 ; 

}

//  дискретный log  
// g^x =_p a . корневая оптимизация : x = y * \sqrt{p} + z 
//  такая задача решается так : a/S положим в хэш-таблицу и поискать в 2 множестве  - это алгоритм дискретного лога за \sqrt{pls}





int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    sieve_Er_nloglogn();

    int_test(pow_a , 2 , 4) ;
    int_test(sum_a_log , 2 , 4) ;


    return 0;
}