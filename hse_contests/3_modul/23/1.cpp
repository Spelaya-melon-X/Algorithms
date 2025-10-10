
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
// #include <termcolor/termcolor.hpp>
#include <random> 
#include <algorithm> 

using namespace std;
std::random_device rd; 
std::mt19937 gen(rd()) ; 

struct E{
    int cost ; 
    int weight ; 
};  

auto f  = [](const E& a, const E& b) {
            return (double)a.cost / a.weight > (double)b.cost / b.weight;};


std::vector<E> generator_random_test( int n  , int A , int B , int C , int D ){
    std::uniform_int_distribution<int> rand_wieght(A , B); 
    std::uniform_int_distribution<int> rand_cost(C , D); 
    vector <E > temp_v ; 
    for (int i = 0 ; i < n ; i++){
        E e ; 
        e.cost = rand_cost(gen); 
        e.weight = rand_wieght(gen); 
        temp_v.emplace_back(e);
    }
    return temp_v ; 
}

bool check(vector <E> res_1 , vector <E> res_2){
    int n = res_1.size() , m = res_2.size(); 
    if ( n != m ) return false;
    sort(res_1.begin() , res_1.end() , f) ; 
    sort(res_2.begin() , res_2.end() , f) ; 
    for ( int i = 0 ; i < n ; i++){
        if ( res_1[i].cost != res_2[i].cost or res_1[i].weight != res_2[i].weight){
            return false; 
        }
    }
    return true; 
}





vector<E> normal_knacksack(int n, int W, vector<E> test) {
    vector<int> dp(W + 1, 0);
    vector<int> parent(W + 1, -1);       
    vector<int> item_taken(W + 1, -1);   

    for (int i = 0; i < n; i++) {
        for (int w = W; w >= test[i].weight; --w) {
            if (dp[w] < dp[w - test[i].weight] + test[i].cost) {
                dp[w] = dp[w - test[i].weight] + test[i].cost;
                parent[w] = w - test[i].weight;
                item_taken[w] = i;                
            }
        }
    }

    int w = max_element(dp.begin(), dp.end()) - dp.begin(); 
    vector<E> answer;

    while (w > 0 && item_taken[w] != -1) {
        int idx = item_taken[w];
        answer.push_back(test[idx]);
        w = parent[w];
    }

    return answer;
}



vector<E> bad_knacksack(int n , int W , vector <E> test){
    
    vector <E> answer; 
    int total_cost = - 1;
    
    
    for ( int i = 0 ; i < n ; i++){
        if (test[i].weight > W) continue;
        int curW = W - test[i].weight;
        vector <E> temp; 
        int temp_cost =  test[i].cost;
        temp.emplace_back(test[i]); 
         

        vector<E> ost;
        for (int j = 0; j < n; j++) {
            if (j != i) ost.push_back(test[j]);
        }

        sort(ost.begin(), ost.end(), f);

        for ( auto [c ,w ] : ost){
            if ( curW >= w ){
                temp.push_back({c, w}); 
                W -= w ; 
                temp_cost += c ; 

            }
        }
        if (temp_cost > total_cost){
            total_cost = temp_cost ; 
            answer = temp ; 
        }
    }
    return answer; 
}

std::vector <E> checker(int n  ,int W,  int A , int B , int C , int D){
    while ( true){
        std::vector <E> test = generator_random_test(n , A , B , C , D); 

        vector <E> res_1 = normal_knacksack(n , W , test); 
        vector <E> res_2 = bad_knacksack(n , W , test); 
        if (!check(res_1 , res_2)){
            return test ; 
        }
    }

}


void print_bad_test(int n , int W , vector <E> temp){
    cout << n <<" " << W << "\n"; 
    for ( auto [c , w] : temp){
        cout << w << " " << c << "\n" ; 
    }
}

int main() {
    int n , W ; cin>> n >> W ; 
    int A , B , C , D ; cin >> A >> B >> C >> D ; 
    vector<E> ans = checker(n , W , A , B , C , D) ; 
    print_bad_test(n , W , ans); 


    return 0;
}