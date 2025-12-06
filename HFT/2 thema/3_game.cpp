#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <utility>
using namespace std;

// 2 ... 8 ==> [3 ... 7] => (7 - 3)/ 2 = 2
// +1 .. +1 

std::pair<int, int>  checker(int n , int k  , int a , int b ) {
    int cntn = 0 , cntk = 0 ;
    for( int i = a ; i <= b ; i++ ) {
        if ( i % n == 0 && i != 0 ) {
            cntn++ ; 
        }
        if ( i % k == 0 && i != 0 ) {
            cntk++ ; 
        }
    }
    return {cntn , cntk} ;
}

std::pair<int , int> my_solution( int n , int k , int a ,int b ) {

    // return {(( b - a) / n) + totaln + beg ,  (( b - a - 1) / k) + totalk + beg2} ; 
    // return {floor(( b - a) / n) + totaln + beg ,  floor(( b - a - 1) / k) + totalk + beg2} ; 
    return {floor(b / n) - floor((a - 1) / n)  , floor(b / k) - floor((a - 1) / k) } ; 
}
// std::pair<int, int> f( int n , int a , int b) {

// }

int main() {
    std::cin.sync_with_stdio(false);
    std::cin.tie(nullptr);
    long long  n , k , a, b; cin >> n >> k >> a >> b;
    // auto p = checker(n ,  k, a ,b ) ; 
    // cout << p.first << " " << p.second << "\n";
// test
    // for ( int i = 0 ; i < 25 ; i ++) {
    //     for ( int j = 0 ; j < i  ; j ++) {
    //         cout << "\n";
    //         auto p = checker(n ,  k, j ,i ) ; 
    //         auto p2 = my_solution(n ,  k, j ,i ) ;
    //         std::cout << "chcekr : i : "  << i << " j : " << j << " n : " << p.first << " k : " << p.second << "\n";
    //         std::cout << "solutu : i : "  << i << " j : " << j << " n : " << p2.first << " k : " << p2.second << "\n";

    //         cout << "\n";

    //     }
    // }
    
    // auto p = checker(n ,  k, a ,b ) ;
    std::cout << ((b / n) - ((a - 1) / n) ) -  ( (b / k) - ((a - 1) / k ) ) << "\n"; 


    // std::cout << p.first - p.second << "\n" ;



    return 0;
}