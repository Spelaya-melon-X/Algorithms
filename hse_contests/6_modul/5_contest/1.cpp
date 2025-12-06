
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;
int N = 5000000; 

std::vector<int> is ;
// template <typename  T >  
// void bool_test(bool(*func) (T) , T obj) {
//     std::cout << "function result is : "  <<  ( func(obj) ?  "True" : "False" ) << "\n" ; 
// }

// template<typename T>
// void int_test(int (*func)(T), T obj) {
//     std::cout << "function result is: " << func(obj) << "\n";
// }

// template<typename T, typename... Args>
// void int_test(int (*func)(T, Args...), T obj, Args... args) {
//     std::cout << "function result is: " << func(obj, args...) << "\n";
// }


// template<typename T>
// void print_vetor(std::vector<T> vec) {
//     std::cout << "vector is: ";
//     for (auto el : vec) {
//         std::cout << el << " "  ;
//     }
// }



// void sieve_Er_nloglogn() {
//     is[1] = 1 ;
//     for ( int x = 2 ; x * x <= N ; x++) { 
//         if (!is[ x]) {
//             for ( int y = x * x ; y <= N ; y += x) {
//                 is[y] = 1 ;
//             }
//         }
//     }
// }

std::vector<long long > d ; // d[x] = the smallest prime divisor of x
std::vector<long long > primes ;
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


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n ; cin>> n ; 
    // is.resize(N + 1) ;
    d.resize(N + 1 , -1) ;

    // sieve_Er_nloglogn() ; 
    sieve_Er_n() ;
    // print_vetor(is) ;
    // print_vetor(d) ; 
    // print_vetor(primes) ;



    for ( int i = 1 ; i <= n ; i++){
        int t ; cin>> t; 
        std::cout << primes[t-1] << " " ;
        // if (std::find(primes.begin() , primes.end()  ,t ) != primes.end()) {
            // cout << "YES\n" ; 
        // } else { 
            // cout << "NO\n" ; 
        // }
    }


    return 0;
}