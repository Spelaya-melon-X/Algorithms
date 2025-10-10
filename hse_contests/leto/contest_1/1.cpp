    #include <iostream>
    #include <vector>
    #include <string>
    #include <algorithm>
    #include <unordered_map>
    #include <ctime>
    #include <iomanip>

    #include "../optimization.h"
    using namespace std;
    
    
    int main() {
        int n = readInt() ; 
        std::vector<int> vec(n) ; 

        for (int i =0 ; i < n ;i++) {
            int elem = readInt() ; 
            vec[i] = elem ; 
        }
        clock_t st_1 = clock(); 

        for ( int i = n ; i > 0 ; i--) {
            // writeInt(vec[i-1] ,' ' ); 
            cout << vec[i-1] << " " ; 
        }
        clock_t en_1 = clock() ; 
        double el_t_1 = (double)(en_1 - st_1)/CLOCKS_PER_SEC ; 
        cout << " \n"; 

        clock_t st_2 = clock(); 
        reverse(vec.begin(), vec.end()) ; 
        for ( auto i = 0 ; i < n  ; i++) {
            // writeInt(vec[i], ' ') ; 
            cout << vec[i] << " " ; 
        }
        clock_t en_2 = clock() ; 

        double el_t_2 = (double)(en_1 - st_1)/CLOCKS_PER_SEC ; 


        std::cout << "Время выполнения: " << std::fixed << std::setprecision(6) << el_t_1  << " секунд" << std::endl;
        std::cout << "Время выполнения: " << std::fixed << std::setprecision(6) << el_t_2  << " секунд" << std::endl;


        return 0;
    }