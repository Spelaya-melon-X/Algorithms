#include <iomanip>
#include <iostream>
using namespace std;

float calculatePower(int base , int exp) {
    if (  exp == 0 ) {
        return 1 ;      
    }
    return calculatePower(base , exp-1 ) * base; 
}

int main() {
    int n, e ; cin >> n >> e ; 
    cout << std::fixed  <<  setprecision(2) << calculatePower(n,  e) ; 
    return 0;
}