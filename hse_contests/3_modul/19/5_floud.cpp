// задача : 
/* 
Есть 5 городов, между некоторыми из них есть дороги с известной длиной.
 Нужно найти кратчайшее расстояние между каждой парой городов (то есть построить матрицу кратчайших 
 путей между всеми парами городов).
*/

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;
void relax(int &a  , int b ) {a = min(a , b); }

int main() {
    //read 
    int n  ; cin >> n ; 
    vector <vector <int > > gr(n , vector <int> (n , 0)); 
    for (int i = 0 ; i < n ;i++){
        for ( int j = 0 ; j < n ;j++){
            int temp ; cin >> temp ; 
            if (temp == "max") {
                gr[i][j] = 100000; 
            }else {
                gr[i][j] = temp;        
            }
        }
    }
    for ( int k = 0 ; k < n ;k++){
        for ( int i = 0 ; i < n ;i++){
            for ( int j = 0 ;j  < n ;j++){
               relax(gr[i][j] , gr[i][k] + gr[k][j]) ; 
            }
        }
    }

    //cout 
    for (int i = 0 ; i < n ;i++){
        for ( int j = 0 ; j < n ; j++){
            cout << gr[i][j] << " "; 
        }
        cout << '\n'; 
    }
    
    return 0;
}