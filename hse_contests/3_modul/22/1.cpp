#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <string>

using namespace std;
int main() {
    int n ,m ; cin >> n >> m ; 
    std::unordered_map< std::string, char> um;
    

    for (int i = 0;  i < n ; ++i) {
        char l; cin >>    l;
        cin.ignore( 2); 
        string cc;cin >> cc;
        um[cc]= l;
    }
    string obr; cin >> obr;

    string br, temp;
    for (char c : obr) {
        temp += c;
        if (um.count(temp)) {
            br += um[temp];
            temp.clear();
        }
    }
    cout << br ; 

    return 0;
}
