#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <random>
#include <limits>
#include <numbers>
#include <iomanip>
using namespace std;

bool norm(double coor_x, double coor_y, double r, double vec_x, double vec_y) {
    return (double)(vec_x - coor_x) * (vec_x - coor_x) + (double)(vec_y - coor_y) *(vec_y - coor_y) <= r * r;
}


int main() {
    const int SIZE = 10000000; 

    double coor_x1 , coor_y1 , r_1 ; std::cin >> coor_x1  >> coor_y1>> r_1 ; 
    double coor_x2 ,coor_y2,  r_2 ; std::cin >> coor_x2 >> coor_y2 >> r_2 ; 
    double coor_x3 ,coor_y3 , r_3 ; std::cin >> coor_x3 >> coor_y3 >> r_3; 

    int count = 0 ; 

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(-3.0, 3.0); 



    for ( int i = 0 ;i < SIZE; i++){
        double vec_x = dis(gen); 
        double vec_y = dis(gen); 
        // cout << vec_x << " " << vec_y << endl; 



        if (norm(coor_x1 , coor_y1 , r_1 , vec_x , vec_y ) && 
            norm (coor_x2 , coor_y2 , r_2 , vec_x , vec_y) && 
            norm (coor_x3 , coor_y3 , r_3, vec_x , vec_y )){
                count++; 
            }


    }

    double  area = 1.0 * count / SIZE *36.0; 
    std::cout << std::fixed << std::showpoint;
    std::cout << std::setprecision(6);
    std::cout << area << std::endl;
    

    // for ( auto el : vec){
    //     cout << el << std::endl; 
    // }
    return 0;
} 