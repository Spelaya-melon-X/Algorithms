#include <iostream>
#include <string>
#include <cstring>

using namespace std;

int main() {
    string text = "abacabaabacaba";
    string pattern = "aba";
    
    // Поиск всех вхождений с помощью функций
    cout << "All occurrences: ";
    for (size_t pos = text.find(pattern);   pos != string::npos;  pos = text.find(pattern, pos + 1)) {
        cout << pos << " ";
    }
    cout << endl;

    // Поиск всех вхождений с помощью указателей 
    const char* textPtr = text.c_str();
    const char* patternPtr = pattern.c_str();

    cout << "All occurrences (pointers): ";
    for (const char* p = textPtr; (p = strstr(p, patternPtr)) != nullptr; p++) {
        cout << p - textPtr << " ";
    }

}