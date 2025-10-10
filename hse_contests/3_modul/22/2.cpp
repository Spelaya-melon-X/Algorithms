#include <vector>
#include <iostream>
#include <queue> 
#include <string> 
#include <unordered_map>
using namespace std; 


struct MinHeapNode { 
	char data; 
	int countt; 

	MinHeapNode *left, *right; 

	MinHeapNode(char data_, int freq_): left(NULL) , right(NULL) , data(data_) , countt(freq_) {} 
}; 


struct comparator { 
	bool operator()(MinHeapNode* l, MinHeapNode* r) {  return (l->countt > r->countt); } 
}; 


void recCode(struct MinHeapNode* root, string str , unordered_map < char, string > &um )  { 
	if (!root)  return; 

	if (root->data != '\0') 
        um[root->data] = str; 


	recCode(root->left, str + "0" , um ); 
	recCode(root->right, str + "1" , um ); 
} 


unordered_map <char , string  >  HuffmanCodes(vector <char> data, vector <int> &countt) { 
	struct MinHeapNode *left, *right, *top; 

	priority_queue<MinHeapNode*, vector<MinHeapNode*>, comparator>  minHeap; 

	for (int i = 0; i < data.size(); ++i) {
		minHeap.push(new MinHeapNode(data[i], countt[i])); 
    }

	while (minHeap.size() > 1) {  
		auto left = minHeap.top();  minHeap.pop(); 

		auto right = minHeap.top(); minHeap.pop(); 

		auto  top = new MinHeapNode('\0', left->countt + right->countt); 
		top->left = left;  top->right = right; 
		minHeap.push(top); 
	} 
    unordered_map <char ,string  > um ;  
	recCode(minHeap.top(), "" , um ); 
    return um ; 
} 

int main() { 
    string s ; cin >> s; 

    unordered_map<char , int> um_ ; 
    for ( auto c : s){
        um_[c]++;
    }

    vector <char> arr ; 
    vector <int> countt ; 
    for ( auto [f,e] : um_){
        arr.push_back(f); 
        countt.push_back(e); 
    }


    
	unordered_map<char , string > um = HuffmanCodes(arr, countt); 
    string a = ""; 
    for (auto el : s){
        a += um[el] ; 
    }


    if (um_.size() == 1) {
        char c2 = arr[0];
        string s2(s.size(), '0');  
        cout << 1 << " " << s2.size() << '\n';
        cout << c2 << ": " << 0 << '\n';
        cout << s2 << '\n';
        return 0;
    }



    cout << um_.size() << " " << a.size() << "\n"; 
    for (auto [cc , ss] : um){
        cout << cc << ": " << ss << '\n'; 
    }
    cout << a << '\n'; 


	return 0; 
} 


