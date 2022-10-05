#include <iostream>
#include <vector>
#include <string>
#include <set>
#include "board.hh"
#include "BloomFilter.hh"
#include "diccTrie.hh"
using namespace std;

void selectNRandom(set<string>& p, vector<string>& dicc, int n) {
    for (int i = 0; i < n; ++i) {
        int rnd = rand()%dicc.size();
		cout << dicc[rnd] << ' ';
        if (not p.insert(dicc[rnd]).second) --i;
    }
    //p amb N randoms
}
    
int main() {
	srand(time(NULL));
    vector<string> dicc;
    int nParaules = 6;
    int N = 8; //valor arbitrari

    string x;
    while (cin >> x) {
        dicc.push_back(x);
    }

    set<string> P;
    selectNRandom(P, dicc, nParaules);
    
    Board B = Board(N, P);
	B.print();

    //Trie
    DiccTrie trie(dicc);
    trie.findWords(B);
    cout << endl;
    BloomFilter bloom(dicc);
    dicc.findWords(B);
  
}
