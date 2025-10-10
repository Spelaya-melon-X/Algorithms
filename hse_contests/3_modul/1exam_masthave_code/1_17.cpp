



#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <cstdlib>
#include "optimization.h"
using namespace std;

static int bad_x_index; 
struct Point{
    int x_ind; 
    bool wh  ; 
};

struct Line{
    std::vector <Point> vec; 
}; 

int psevdoRandom(){
    return std::rand() % 2 ; 
}

void fillingRandomXPermutation(std::vector <int> &x_perm   ){
    for ( int i = 0 ;i < x_perm.size() ;i++){
        x_perm[i] = psevdoRandom(); 
    }


}

void changeX_Perm(std::vector <int> &x_perm){
    x_perm[bad_x_index] = 1 - x_perm[bad_x_index]; 
 
}

bool isNormalPerm(const vector<Line>& form, const vector<int>& x_perm) {
    int m = form.size();
    for (int i = 0; i < m; i++) {
        if ( x_perm[ form[i].vec[0].x_ind ] == form[i].vec[0].wh || x_perm[ form[i].vec[1].x_ind ] == form[i].vec[1].wh || x_perm[ form[i].vec[2].x_ind ] == form[i].vec[2].wh ) {
        } else {
            int random_var = std::rand() % 3;
            bad_x_index = form[i].vec[random_var].x_ind;
            return false;
        }
    }
    return true;
}



int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    

    mt19937 gen(static_cast<unsigned>(time(nullptr)));
    int n = readInt(); 
    int m = readInt(); 

    std::vector<Line> form(m) ; 
    std::vector <int> x_perm(n); 

    for (int i = 0 ; i < m ; i++){
        Line stroka ; 
        for (int j = 0 ; j < 3 ; j++){
            int x = readInt();
            bool wh = readInt();
            stroka.vec.push_back({x-1, wh }); 
        }
        form[i] = stroka; 
    }

    const int MAX_TRIES = 1000000;   
    const int MAX_FLIPS = 3 * n;     
    

    for (int tries = 0; tries < MAX_TRIES; tries++) {

        fillingRandomXPermutation(x_perm);
        

        for (int flips = 0; flips < MAX_FLIPS; flips++) {
            if (isNormalPerm(form, x_perm)) {
                string ans;
                ans.reserve(n);
                for (int i = 0; i < n; i++) {
                    ans.push_back(x_perm[i] ? '1' : '0');
                }
                writeWord(ans.c_str());
                return 0;
            } else {
                changeX_Perm(x_perm);
            }
        }
    }



    return 0;
}