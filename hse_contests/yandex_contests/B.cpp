#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    double a , b , c , v0 ,v1 , v2 ;  cin>> a >> b >> c >> v0 >> v1 >> v2 ; 

    double path1_a = ((double)a/ v0 + (double)c / v1 + (double)b / v2) ; //std::cout << path1_a << "\n";
    double path2_a = (double)a/ v0 +  (double)a / v1 + (double)b / v0 + (double)b/ v1 ;  //std::cout << path2_a << "\n";
    double path3_a = (double)a/ v0 + (double)c / v1 + (double)c / v2 + (double)a / v2 ; //std::cout << path3_a << "\n";

    double path4_a = a / v0 + a /v1 + a /v0 + c / v0 + b/ v1; 
    double path4_a_2 = a / v0 + a /v1 + a /v0 + c / v0 + c/v1 + a / v1 ; 

    double path4_b = b/v0 + b/ v1 + b/ v0 + c / v0 + a/v1 ; 
    double path4_b_2 = b/v0 + b/ v1 + b/ v0 + c / v0 + c/v1 + b / v1;

    double path1_b = (double)b/ v0 + (double)c / v1 + (double)a / v2 ; //std::cout << path1_b << "\n";
    double path2_b = (double)b / v0 + (double)b/ v1 + (double)a / v0 + (double)a/ v1 ;//std::cout << path2_b << "\n";
    double path3_b = (double)b/ v0 + (double)c / v1 +(double) c / v2 + (double)b / v2 ;//std::cout << path3_b << "\n";

    double patha_genius = a/v0 + c/ v0 + c/v1 + a / v2 ; //std::cout << patha_genius << "\n";
    double pathb_genius = b/v0 + c/ v0 + c / v1 + b/ v2 ; //std::cout << pathb_genius << "\n";


    double answer = min({path1_a , path2_a , path3_a , path4_a , path4_a_2 , path4_b , path4_b_2 , path1_b , path2_b , path3_b , patha_genius , pathb_genius}) ; 
    std::cout << answer << "\n";




    return 0;
}