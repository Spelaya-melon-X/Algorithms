#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

int countDigits( int a) {
    if ( a == 0 ) {
        return 0; 
    }
    return ( countDigits(a / 10)) +1; 
}

int main() {
    int n ; cin>> n ; 
    std::cout << countDigits(n)    ; 
    return 0;
}