#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;


// 5 2 ( нельзя)
// BGBBGB => на 2 девочки максимум - 2 мальчика , на одну девочку => 2 мальчика ) 

// 6 3 
// BGBBGBBGB => 6 - 3*2 = 0 значит можно 


// 6 5 
// BGBBGBGBGBG

// 6 4
// BGB BGB GB GB

// 3 1 
// BGB => 3 - 2 > 0 (нельзя)
// 2 1 
// BGB можно 

// BG -> N-1 , M-1 
// BGB -> N-2 , M-1 (можно только тогда , когда последний элемент - м/ж)


// 7 4
// BGB BGB BGB BG



// 5 3 
// BGBBGBGB

int main() {
    int N , M ; cin >> N >> M ; 
    std::string stroka; 
    int flag = 0 ; 
    if ( N <  M ) {
        swap(N,M) ;
        flag = 1;  
    }

    string dopB , dop2 ; 
    if ( flag == 0 ) {
        dopB = "BG" ; 
        dop2 = "BGB";
    }else {
        dopB = "GB" ;
        dop2 = "GBG" ;  
    }
        
    if ( N - M*2 > 0 )  {
        cout << "NO SOLUTION" ; 
    }else if (N == M ){
        for ( int i = 0 ; i < N ; i++){
            stroka += dopB ; 
        } 
    } else   {
        for ( int i = 0 ; i < N - M ; i++){
            stroka += dop2 ; 
        }
        for ( int i = 0 ; i < M - ( N - M )  ; i++){
            stroka += dopB ; 
        }
    }


    cout << stroka ; 
    return 0;
}