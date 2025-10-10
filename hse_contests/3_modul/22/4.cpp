#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include "optimization.h"
using namespace std;

int main() {
    vector <string > num ; 
    string s ;  
    while (cin >> s){ч
        num.push_back(s);
    }

    sort(num.begin(), num.end(), [](const string& a, const string& b) {
        return a + b > b + a;  
    });

    string res = "";
    for (auto el : num){
        res += el;
    }
    cout << res << endl;

    return 0;
}