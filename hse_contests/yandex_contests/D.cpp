#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
using namespace std;

int main() {
    int n , k ; cin >> n >> k;
    std::unordered_map<long long, int> um ; 
    std::set<long long> s; 
    vector<long long> answer; 
    for (int i = 0 ; i < n ;i++) {
        int el ; cin >> el; 
        s.insert(el) ; 
        um[el]++; 
    }
    if (k== 0) {
        cout << " "; 
    }

    int len = s.size(); 
    if (  len == k ) {
        for (auto el : s) {
            cout << el << " " ; 
        }
        cout << "\n" ; 
    }else if (len > k )  {
        int ind = 0 ; 
        for (auto el : s ){
            if (ind == k ) break; 
            cout << el << " "; 
            ind++ ; 
        }
    } else { // len < k;
        int cc = k-len ; 
        for (auto el : s) {
            answer.push_back(el) ;
        }
        for (int i = 0 ; i < n ; i++) {
            if (cc == 0) break;
            um[answer[i]]-- ; 
            while (um[answer[i]] > 0 && cc != 0 ) {
                um[answer[i]]-- ; 
                cc-- ;
                answer.push_back(answer[i]) ;
            }
        }
        for (auto el : answer) {
            cout << el << " " ; 
        }
        
    }
    
    return 0;
}