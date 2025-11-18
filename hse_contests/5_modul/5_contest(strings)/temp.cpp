#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

int main() {
    int n ; cin >> n ; 
    int counter = 0 ; 

    for (int i = 0 ; i < n -i ; i++){
        if ( 2*n - i == i)  {
            counter++; 
        }if ( 2*n - i != i and (2 * n- i) % i == 0 ) {
            counter += 2 ; 
        }
    }
    cout << counter ; 

    return 0;
}