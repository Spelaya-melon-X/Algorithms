#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>qx
#include <numeric>
#include "optimization.h"
using namespace std;

__int128_t f(__int128_t x , __int128_t n  ){
    return (x  + 1)* (x + 1)% n;
}

__int128_t finder(__int128_t n , __int128_t seed = 2 ){
    __int128_t x = seed ; 
    __int128_t y = seed; 
    __int128_t divisor = 1; 
    for (__int128_t i = 0 ;i < 1000000 && divisor == 1 ; i++){
        x = f(x,n ) ; 
        y = f ( f ( y , n )  , n);  
        divisor = std::gcd((x - y) , n ) ;  

        if ( divisor > 1 and divisor < n ) return divisor ; 
    }
    return -1 ; 
}

int  main() {

    while( !isEof() ){
        __int128_t n = readInt(); 
        __int128_t s = finder( n , 2
        ); 
        if ( n == 2){
            writeWord("IMPOSSIBLE") ;continue;; 
        }
        if(n % 2 == 0) {
            writeInt(2, ' ') ; writeInt(n / 2 , '\n' ); continue;; 
        }
        if ( s == - 1 or s == n ){
            writeWord("IMPOSSIBLE\n"); continue;
        } else if (s < 2 ){
            writeWord("IMPOSSIBLE\n"); continue;; 
        } else {
            writeInt(s, ' ') ; writeInt(n / s , '\n'); continue;; 
        }
    }
    return 0; 
}