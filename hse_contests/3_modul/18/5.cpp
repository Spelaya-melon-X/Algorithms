#include <iostream>
#include <vector>
#include <unordered_set>
#include <random>
#include <algorithm>
#include "optimization.h" 

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; 
    cin >> n;
    int totalCards = 2 * n;

    vector<int> vec; 
    unordered_set<int> us; 

    for (int i = 0; i < totalCards; i++){
        int temp = readInt();
        vec.push_back(temp);
        us.insert(temp);
    }
    sort(vec.begin(), vec.end());


    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0, totalCards - 1);


    for (int i = 0; i < 500000; i++){
        int idx1 = dis(gen);
        int idx2 = dis(gen);
        if (idx1 == idx2) continue; 


        int a = vec[min(idx1, idx2)];
        int b = vec[max(idx1, idx2)];
        int d = b - a;
        if (d == 0) continue; 


        int leftCandidate = a;
        int countLeft = 0;
        while (us.count(leftCandidate)) {
            countLeft++;
            if (us.count(leftCandidate - d))
                leftCandidate -= d;
            else
                break;
        }


        int rightCandidate = b;
        int countRight = 0;
        while (us.count(rightCandidate)) {
            countRight++;
            if (us.count(rightCandidate + d))
                rightCandidate += d;
            else
                break;
        }


        int totalCount = countLeft + countRight - 1;
        if (totalCount >= n) {

            writeInt(leftCandidate, ' ');
            writeInt(d, '\n');
            return 0;
        }
    }

    for (int num : vec) {

        if (us.count(num) >= n) {
            writeInt(num, ' ');
            writeInt(0, '\n');
            return 0;
        }
    }
    return 0;
}
