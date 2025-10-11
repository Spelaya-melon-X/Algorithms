#include <string> 
#include <iostream>
#include <vector>
using namespace std;

bool hasOccurrence(const string& text, const string& pattern) { //  Проверить, есть ли хотя бы одно вхождение 𝑠 в 𝑡.
    return text.find(pattern) != string::npos;
}

int countOccurrences(const string& text, const string& pattern) { // Подсчитать количество вхождений 𝑠 в 𝑡
    if (pattern.empty()) return 0;
    
    int count = 0;
    size_t pos = 0;
    while ((pos = text.find(pattern, pos)) != string::npos) {
        count++;
        pos += 1; 
    }
    return count;
}

int findAnyOccurrence(const string& text, const string& pattern) { //  Найти позицию любого вхождения 𝑠 в 𝑡, или вернуть−1, если таких нет.
    size_t pos = text.find(pattern);
    return (pos != string::npos) ? static_cast<int>(pos) : -1;
}


vector<int> findAllOccurrences(const string& text, const string& pattern) { // Вернуть множества всех вхождений 𝑠 в 𝑡.
    vector<int> positions;
    if (pattern.empty()) return positions;
    
    size_t pos = 0;
    while ((pos = text.find(pattern, pos)) != string::npos) {
        positions.push_back(static_cast<int>(pos));
        pos += 1;
    }
    return positions;
}


int main() {
    std::cout << hasOccurrence("Hello, world!", "world") << std::endl;
    std::cout << countOccurrences("Hello, world!", "world") << std::endl;
    std::cout << findAnyOccurrence("abbabab", "ab") << std::endl;
    std::vector<int> positions = findAllOccurrences("abbababa", "ab");
    for (int pos : positions) {
        std::cout << pos << " ";
    }
    std::cout << std::endl;
    return 0 ; 
}