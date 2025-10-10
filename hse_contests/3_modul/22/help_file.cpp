

int main() {
    string s;
    cin >> s;

    unordered_map<char, int> um_;
    for (auto c : s) {
        um_[c]++;
    }

    vector<char> arr;
    vector<int> countt;
    for (auto [f, e] : um_) {
        arr.push_back(f);
        countt.push_back(e);
    }


    if (um_.size() == 1) {
        char singleChar = arr[0];
        string encodedString(s.size(), '0');  // Закодированная строка из '0'
        cout << 1 << " " << encodedString.size() << '\n';
        cout << singleChar << ": " << 0 << '\n';
        cout << encodedString << '\n';
        return 0;
    }

    // Обработка общего случая
    unordered_map<char, string> um = HuffmanCodes(arr, countt);
    string a = "";
    for (auto el : s) {
        a += um[el];
    }

    cout << um_.size() << " " << a.size() << "\n";
    for (auto [cc, ss] : um) {
        cout << cc << ": " << ss << '\n';
    }
    cout << a << '\n';

    return 0;
}