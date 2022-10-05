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
        if (not p.insert(dicc[rnd]).second) --i;
        else cout << dicc[rnd] << ' ';
    }
    //p amb N randoms
}

void printSet(set<string>& S){
    for (set<string>::iterator it = S.begin(); it != S.end(); it++){
        cout << "Found " << *it << endl;
    }
}

int main() {
	srand(time(NULL));
    vector<string> dicc;
    set<string> solution;
    int nParaules = 6;
    int N = 8; //valor arbitrari
    
    unsigned int nPrefixes = 0;

    string x;
    while (cin >> x) {
        dicc.push_back(x);
        nPrefixes += x.size() - 1;
    }

    set<string> P;
    selectNRandom(P, dicc, nParaules);
    
    Board B = Board(N, P);
	B.print();

    //Trie
    DiccTrie trie(dicc);
    trie.findWords(B);
    cout << "-------" << endl;

    solution.clear();
    Bloom bloom(dicc, nPrefixes);
    bloom.findWords(B, solution);
    printSet(solution);
}
