#include <set>
#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    set<int> s;
    string cmd;
    int x;
    
    while (cin >> cmd >> x) {
        if (cmd[0] == 'i') {
            s.insert(x);

        }
        else if (cmd[0] == 'd') {
            s.erase(x);
        }
        else if (cmd[0] == 'e'){ 
            std::cout << (s.count(x) ? "true" : "false") << '\n';
        }
            
        else if (cmd[0] == 'n') {
            auto it = s.upper_bound(x);
            if (it!= s.end()){
                std::cout <<  to_string(*it) << '\n' ; 
            }else {
                cout << "none\n" ; 
            }

        }
        else if (cmd[0] == 'p') {
            auto it = s.lower_bound(x);
            if ( it != s.begin()){
                it--;
                std::cout <<  to_string(*it) << '\n' ; 
            }else {
                cout << "none\n" ; 
            }


        }
    }
}