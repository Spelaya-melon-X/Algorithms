#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

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

// std::pair<int,int > Evclid(int a , int b ) {
//     if ( b == 0 ) {
//         return {1 ,0}; 
//     }
//     auto [x,y] = Evclid(b , a % b) ;  // x * b + y( a - b |a/b|)
//     return {y , x - y * (a / b)} ;
// }

std::tuple<long long , long long,  long long> ExtendedEuclid(long long a ,long long b ) {
    if ( b ==  0) {
        return {a , 1 , 0} ; 
    }
    auto [gcd , x1 ,y1] = ExtendedEuclid(b , a %b) ; 
    long long x = y1 ; 
    long long y = x1 - (a / b) * y1 ; 
    return {gcd , x , y} ;
}

long long modInverse(long long a, long long m) {
    auto [gcd, x, y] = ExtendedEuclid(a, m);
    if (gcd != 1) {

        return -1;  
    }
    return (x % m + m) % m;
}



// int gcd(int a, int b , int x , int y , int m ) {
//     if (a == 0 ) {
//         x = 0 ; y = 0 ; return b ; 
//     }
//     int x1 , y1 ; 
//     int d = gcd(b% a , a , x1 , y1 , m ) ; 
//     x = (y1 - (b / a) * x1 ) % m  ;
//     y = x1 % m  ; 
//     return d;
// }


int main() {
    long long a , n ; cin >> a >> n ; 
    cout << modInverse(a , n ) << " " ;

    // auto [x,y] = Evclid(a, -1) ; 
    // std::cout << x << " " << y << " " ; 
    // for ( int i = 1 ; i <= n ; i++){

    //     int ans = gcd(a , 1 , i , 0 ,n  ); 
    //     if (ans == 1) {
    //         cout << i << " " ; 
    //         return 0 ; 
    //     }
    // }
    // cout << -1 << " " ;



    return 0;
}