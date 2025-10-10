#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

static int bad_x_index; 

struct Point {
    int x_ind; 
    int wh;    
};

struct Line {
    vector<Point> vec; 
};


int psevdoRandom() {
    return rand() % 2;
}


void fillingRandomXPermutation(vector<int> &x_perm, int n) {
    for (int i = 0; i < n; i++) {
        x_perm[i] = psevdoRandom();
    }
}


void changeX_Perm(vector<int> &x_perm) {
    x_perm[bad_x_index] = 1 - x_perm[bad_x_index];
}

bool isNormalPerm(const vector<Line> &form, const vector<int> &x_perm, int m) {
    for (int i = 0; i < m; i++) {
        bool clauseSatisfied = false;
        for (int j = 0; j < 3; j++) {
            int var_index = form[i].vec[j].x_ind - 1;
            int wh = form[i].vec[j].wh;
            if (x_perm[var_index] == wh) {
                clauseSatisfied = true;
                break;
            }
        }
        if (!clauseSatisfied) {

            int random_var = rand() % 3;
            bad_x_index = form[i].vec[random_var].x_ind - 1;
            return false;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    srand(time(0));
    
    int n, m;
    cin >> n >> m;
    
    vector<Line> form(m);
    vector<int> x_perm(n, 0);
    

    for (int i = 0; i < m; i++) {
        Line clause;
        for (int j = 0; j < 3; j++) {
            int x, wh;
            cin >> x >> wh;
            clause.vec.push_back({x, wh});
        }
        form[i] = clause;
    }
    

    const int MAX_TRIES = 10000;   
    const int MAX_FLIPS = 3 * n;     
    

    for (int tries = 0; tries < MAX_TRIES; tries++) {

        fillingRandomXPermutation(x_perm, n);
        

        for (int flips = 0; flips < MAX_FLIPS; flips++) {
            if (isNormalPerm(form, x_perm, m)) {

                for (int i = 0; i < n; i++) {
                    cout << x_perm[i];
                }
                cout << "\n";
                return 0;
            } else {

                changeX_Perm(x_perm);
            }
        }
    }
    
    return 0;
}
