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
            if (temp == -1) {
                gr[i][j] = 10000; 
            }else {
                gr[i][j] = temp;        
            }
        }
    }
    for (int k = 0 ; k < n ;k++){
        for ( int i = 0 ; i < n ;i++){
            for ( int j = 0 ;j  < n ;j++){
                relax(gr[i][j] , gr[k][j] + gr[i][k]); 
            }
        }
    }
    int dd = 0 ; 
    int mm = 10000 ; 
    for ( int i = 0 ; i < n ;i++){
        int e = 0 ; 
        for ( int j = 0 ; j < n ;j++){
            if ( i != j && gr[i][j] < 10000){
                e = max(e , gr[i][j]); 
            }
        }
        mm =min( mm , e); 
        dd = max(dd , e);
    }
    cout << dd << "\n";
    cout << mm << "\n";
    return 0;
}