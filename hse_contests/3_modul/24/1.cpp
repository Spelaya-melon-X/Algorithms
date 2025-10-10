#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>

using namespace std;


std::random_device rd; 
std::mt19937 gen(rd()) ; 
//comporators 

auto comp_less_2 = [](auto a , auto b ){ return a+a < b+b;  }; 
auto comp_good = [](auto a , auto b ){return a + b < b + a ; } ; 

string less_func(vector <string> test){ 
    int n = test.size() ; 
    std::sort(test.begin() , test.end() ,[](auto a , auto b ){ return a < b; }) ; 
    string str; 
    for (auto el : test){
        str += el ; 
    }
    return str; 

}

string less2_func(vector <string> test){
    int n = test.size() ; 
    std::sort(test.begin() , test.end() , comp_less_2) ; 
    string str; 
    for (auto el : test){
        str += el ; 
    }
    return str;  
}

string normal_func(vector< string> test){
    int n = test.size() ; 
    std::sort(test.begin() , test.end() , comp_good) ; 
    string str; 
    for (auto el : test){
        str += el ; 
    }
    return str; 
}

// random test 

// random string 

string random_string( int l){
    std::uniform_int_distribution<int>distrib(0,1) ; 

    std::string str ; 
    for ( int i = 0 ; i < l ;i++){
        str += (distrib(gen)) ? 'a' : 'b' ; 
    }

    return str; 
}

vector <string> random_vector(){
    std::uniform_int_distribution<int> dist(1 , 3); 
    int n = dist(gen); 
    vector <string> temp; 
    for ( int i =0 ; i < n ;i++){
        int k = dist(gen) ; 
        string str = random_string(k) ; 
        temp.push_back(str) ; 
    }
    return temp; 
}

void tesing_code(int ind ){

    if (ind == 1){

        while (true ){
            vector <string> test = random_vector() ; 
            if (less_func( test) != normal_func(test)){
                cout << test.size() << "\n" ; 
                for (auto i : test){
                    cout << i << " " ; 
                }
                return ; 
            }

        }

    } else {
        while (true ){
            vector <string> test = random_vector() ; 
            if (less2_func( test) != normal_func(test)){
                cout << test.size() << "\n" ; 
                for (auto i : test){
                    cout << i << " " ; 
                }
                return; 
            }

        }
    }

}

int main() {

    int ind ; cin >> ind; 
    tesing_code(ind) ; 



    return 0;
}