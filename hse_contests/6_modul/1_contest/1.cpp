#include <iostream>
#include <numeric>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <cmath> 
#include <iomanip>

#define  ui unsigned int 
using namespace std;

// int big_prime_num = 71107009 ; 
// int BASE = 131 ; 
// std::string str ;
// std::vector<std::vector<int> > lcp; 
// std::vector<int > hashh ,  poww ; 
// std::vector<std::string> s ; 


// bool is_prime(int num ) {
//     if ( num < 2) return false; 
//     for (int i = 2 ; i< sqrt(num) +1 ; i++) {
//         if (num % i == 0) {
//             return false;
//         }
//     }
//     return true;
// } 

// ui get_prime() {
//     ui big_prime = 1  ; 
//     for (int i = 1 ; i < UINT_MAX ; i+= 32) {
//         if (is_prime( i)) {
//             big_prime = i; 
//             std::cout << big_prime << "\n" ; 
//         }
//     }
//     return big_prime ; 
// }

// template <typename  T>  
// void test_tf(bool(*func) (T) , T obj) {
//     std::cout << "function result is : "  <<  ( func(obj) ?  "True" : "False" ) << "\n" ; 
// }



// void build_hashes(std::string &s) {
//     int n = s.size() ; 
//     poww.resize(n); 
//     hashh.resize(n);  
//     poww[0] = 0 ;
//     for (int  i = 1 ; i <= n ;i++)  {
//         poww[i] = (poww[-1] * BASE ) % big_prime_num ; 
//     }
//     hashh[0] = 0 ; 
//     for (int i = 0 ; i < n ;i++) {
//         hashh[i+1] = (hashh[i] * BASE + s[i] ) % big_prime_num ; 
//     }
// }

// int get_hash (int l , int r) {
//     return  (hashh[r+1] - hashh[l] * poww[r-l+1] % big_prime_num + big_prime_num) % big_prime_num;
// }


// void create_lcp(const std::string str ) {
//     lcp[str.size()-1][str.size()-1] = 0 ; 
//     for (int i =0 ; i < str.size()-1 ; i++) {
//         for ( int j = 0 ; j < str.size()-1 ;j++) {
//             if (str[i] == str[j]) {
//                 lcp[i][j] = 1 + lcp[i+1][j+1] ; 
//             }else {
//                 lcp[i][j] = 0 ; 
//             }
//         }
//     }
// }



// template <typename T> 
// void pv(const std::vector<T> &vec) {
//     for ( const auto el : vec ) {
//         cout << el << " " ; 
//     }
// }

// template <typename T> 
// void pvv(const std::vector<std::vector<T>> &s ) {
//     for ( const auto v : s) {
//         for ( const auto el : v) {
//             std::cout << el << " " ; 
//         }
//         std::cout << "\n" ; 
//     }
// }


// int get_pos(std::vector<std::string> s , std::string str ) {
//     int i = 0 ; 
//     for (auto substrr : s ) {
//         if (substrr == str ) {
//             return i; 
//         }
//         i++; 
//     }
//     return -1; 
// }


// template <typename  T> 
// bool comporator(const T s1 , const T  s2   ) {
//     int pos1 = get_pos(s, s1) ; 
//     int pos2 = get_pos(s, s2) ; 
//     int symb = lcp[pos1][pos2] ; 
//     int l = 0 , r = str.size() - max(s1.size() , s2.size()) ;
//     while ( l <= r) {
//         int mid = ( l + r) / 2 ; 
//         if (get_hash( pos1 , pos1 + mid -1) == get_hash( pos2, pos2 + mid -1) ) {
//             l = mid + 1 ;
//         }else {
//             r = mid -1; 
//         }
//     }
//     int len_pref = r ; 

//     if ( pos1 + len_pref >= str.size()) {
//         return -1; 
//     }
//     if (pos2 + len_pref >= str.size() ){
//         return 1; 
//     }    
//     return str[pos1 + len_pref] < str[pos2 + len_pref] ? -1 : 1 ; 
// }

vector<int> build_suffix_array(const string& s) {
    int n = s.size();
    vector<int> sa(n), rnk(n), tmp(n);
    for (int i = 0; i < n; i++) {
        sa[i] = i;
        rnk[i] = s[i];
    }
    for (int k = 1; k < n; k <<= 1) {
        auto cmp = [&](int i, int j) {
            if (rnk[i] != rnk[j]) return rnk[i] < rnk[j];
            int ri = i + k < n ? rnk[i + k] : -1;
            int rj = j + k < n ? rnk[j + k] : -1;
            return ri < rj;
        };
        sort(sa.begin(), sa.end(), cmp);
        tmp[sa[0]] = 0;
        for (int i = 1; i < n; i++)
            tmp[sa[i]] = tmp[sa[i - 1]] + cmp(sa[i - 1], sa[i]);
        rnk = tmp;
        if (rnk[sa[n - 1]] == n - 1) break;
    }
    return sa;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    getline(cin, s);

    auto sa = build_suffix_array(s);
    for (int i = 0; i < sa.size(); i++)
        cout << sa[i]+1 << (i + 1 == sa.size() ? '\n' : ' ');
}






    // std::getline(cin , str);

    // lcp.resize(str.size(), std::vector<int>(str.size()));
    // for ( int i = 0 ; i < str.size() ; i++) {
    //     s.push_back(str.substr(i , str.size() - i)) ; 
    // }

    // std::sort(s.begin() , s.end() , [&] (int i , int j ) {return  s.substr(i) < s.substr(j); });
    // create_lcp(str) ; 
    // pvv(lcp) ;





    // test_tf(is_prime , 5) ; 
    // std::cout << get_prime() ; 
    // pv(s) ; 
