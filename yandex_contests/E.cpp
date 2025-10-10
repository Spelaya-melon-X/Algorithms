#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;



int main(){
    ios_base::sync_with_stdio(false); 
    cin.tie(nullptr);
    long long n, k; cin >> n >> k ; 
    int rest = n % 10;
    int ost = n % 10  ; 
    n += rest;
    while(k > 0){
        if(rest == 0 ){
            n += rest ; 
            rest = 0;
            std::cout <<  n ; 
            return 0 ; 
        }
        if (rest == 5) {
            n += 5; 
            rest = 0 ; 
            std::cout << n ; 
            return 0 ; 
        }
        else if(rest == 1 && k- 4 > 0 ){
            n += 2 + 4 + 8 + 6; 
            rest = 2 ;
            k-=4;  
        }
        else if(rest == 3 ){
            rest = 6 ;
        }
        else if(rest == 4 || rest == 9){
            rest = 8;
        }
        else if(rest == 7 || rest == 2){
            rest = 4;
        }
    }
    cout << n;
    return 0;
}