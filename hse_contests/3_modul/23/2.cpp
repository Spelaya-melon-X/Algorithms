#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct J {
    int a; 
    int  b; 
    int  id;
};

auto f = [](const J& a1, const J& b1) { return a1.a <= b1.a;};
auto g = [](const J& a2, const J& b2) { return a2.a > b2.a;};

int main() {

    int n; cin >> n;

    vector<int> A(n), B(n);
    for (int i = 0; i < n; ++i) {
        int temp ; cin >> temp; A[i] = temp; 
    }
    for (int i = 0; i < n; ++i) {
        int temp; cin >> temp ; B[i] = temp; 
    }


    vector<J> P_1, P_2;

    for (int i = 0; i < n; ++i) {
        if (A[i] <= B[i]){
            J j ; 
            j.a = A[i] ; j.b = B[i] ; j.id = i+1 ; 
            P_1.emplace_back(j);
        }
        else {
            J j ;
            j.a = A[i] ; j.b = B[i] ; j.id = i+1; 
            P_2.emplace_back(j);
        }
    }

    sort(P_1.begin(), P_1.end(), f);

    sort(P_2.begin(), P_2.end(), g );

vector<J> sch;
    for (auto& job : P_1) {
        sch.push_back(job);
    }
    for (auto& job : P_2)
     sch.push_back(job);


    for (size_t i = 0; i < sch.size(); ++i) {
        cout << sch[i].id << (i + 1 < sch.size() ? ' ' : '\n');
    }


    int time1 = 0, time2 = 0;
    vector<int> sec_sch;
    for (auto& job : sch) {
        time1 += job.a;
        time2 = max(time2, time1) + job.b;
        sec_sch.push_back(job.id);
    }

    cout << time2 << '\n';  


    for (size_t i = 0; i < sch.size(); ++i) {
        cout << sch[i].id << (i + 1 < sch.size() ? ' ' : '\n');
    }


    for (size_t i = 0; i < sec_sch.size(); ++i) {
        cout << sec_sch[i] << (i + 1 < sec_sch.size() ? ' ' : '\n');
    }

    return 0;
}