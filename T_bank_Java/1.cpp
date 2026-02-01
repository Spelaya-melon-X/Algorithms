
//OK !
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

int main() {
    string str;cin >> str;
    std::sort(str.begin(), str.end());

    int i = 0;
    while (str[i] == '0') { ++i; }
    std::cout << str[i] + str.substr(0, i) + str.substr(i + 1)  << std::endl;
    return 0;
}



// //OK !
// #include <iostream>
// #include <algorithm>
// #include <string>

// int main() {
//     std::string s;
//     std::cin >> s;

    
//     std::sort(s.begin(), s.end());

    
//     int pos = 0;
//     while (s[pos] == '0') {
//         ++pos;
//     }

    
//     std::string result;
//     result += s[pos];               
//     result += s.substr(0, pos);     
//     result += s.substr(pos + 1);    

//     std::cout << result << std::endl;
//     return 0;
// }
