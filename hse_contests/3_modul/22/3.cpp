#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <random>
#include <limits>
#include <numbers>
#include <iomanip>
#include <algorithm>
using namespace std;



int main() {
    int n , m ; cin >> n >> m ; 
    vector <pair<float , float > > vp ; 
    for (int i = 0 ; i < n ;i++){
        float v , w ; cin>> v >> w ; 
        vp.emplace_back(std::make_pair(v , w)) ; 
    }
    sort(vp.begin() , vp.end() , [](pair <float , float> a , pair <float, float >  b) {return (a.first / a.second  > b.first / b.second) ; } ) ; 

    float total = 0.0 ; 
    for ( int i = 0 ; i< n ; i++){
        if (m >= vp[i].second) {
            total += (float)vp[i].first ; 
            m-= vp[i].second; 
        }else {
            float dr = m / vp[i].second ; 
            total += (float)vp[i].first * dr ; 
            break ;
        }
    }

    std::cout << std::fixed << std::showpoint;
    std::cout << std::setprecision(3);
    std::cout << total << std::endl;
    




    return 0;
}