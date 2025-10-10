#include <climits>
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

int main() {
    long long  n ; cin >> n ; 
    if (n == 1) {
        int ans ; cin >> ans; 
        std::cout <<  ans; 
        return 0 ; 
    }
    // vector<int> a(n);
    long long min_vanya = INT_MAX  , max_masha = -1  , masha = 0 , vanya =0  ;
    for (int i = 0 ; i < n ; i++) {
        long long el ; cin >> el; 
        if ( i % 2 == 0) { // vanya 
            vanya += el; 
            // cout << i << " : " << vanya  << "\n"; 
            min_vanya = min(min_vanya , el) ; 
        }else {
            masha += el; 
            max_masha = max(max_masha , el); 
        }
    }
    // cout << vanya  << "\n"; 
    // cout << masha  << "\n"; 
    // cout << min_vanya  << "\n"; 
    // cout << max_masha  << "\n"; 
    long long answer = 0 ; 
    if (min_vanya > max_masha) {
        answer = vanya - masha ; 
    }else {
        answer = vanya - masha - 2* min_vanya + 2 * max_masha ; 

    }
    cout << answer ; 
    // vasya - i % 2 == 1 / masha i % 2 == 0
    // for (auto el : a ) {
    //     cout << el << " " ; 
    // }


//     11
// 4 10 7 5 4 5 3 8 3 2 5
// 0 1  2 3 4 5 6 7 8 9 10

// vanya = 4 + 7 + 4 + 3 + 3 + 5 = 26  prefix_vanya  = 26  , min_vanya = 3 
// masha = 10 + 5 + 5 + 8 + 2 = 30  prefix_masha = 30   , max_masha = 10 
// удоволеьстиве = (vanya - min_vanya + max_masha) - (masha - max_masha + min_vanya) 
// логично что нужно заменять минимальный у васи на максимальный у маши 

    return 0;
}