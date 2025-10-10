#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <set>
using namespace std;




int main() {
    string str ; cin>> str; 
    std::unordered_map<string, bool> um ; 
    um[str] = true; 
    int count_week = 1 ; 
    for (int i = 0 ; i < str.size() ; i++) {
        for (int j = i ; j < str.size() ; j++) {
            string new_str = str; 
            new_str[i] = str[j]; 
            new_str[j] = str[i] ; 
            if (um.find(new_str) == um.end()) {
                um[new_str] = true; 
                count_week++; 
                
            }
        }
    }
    cout << count_week ; 
    
    

    return 0;
}