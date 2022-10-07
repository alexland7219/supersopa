#include <iostream>
#include <fstream>
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

void printSet(set<string>& S, fstream& out){
    for (set<string>::iterator it = S.begin(); it != S.end(); it++){
        out << "Found " << *it << endl;
    }
}

int main() {

    // Randomitzar la seed
	srand(time(NULL));

    // El vector de paraules del diccionari llegit per stdin
    vector<string> dicc;

    // El conjunt de paraules trobades
    set<string> solution;

    int nParaules = 8; // Nombre de paraules a amagar
    int N = 30;        // Mida del tauler NxN
    
    // Nombre de prefixos totals de tot el diccionari
    unsigned int nPrefixes = 0;

    string x;
    while (cin >> x) {
        dicc.push_back(x);
        nPrefixes += x.size() - 1; // La paraula sencera no compta com a prefix
    }

    set<string> P;
    selectNRandom(P, dicc, nParaules);
    
    Board B = Board(N, P);
	B.print(); // Fem un print a stdout de el tauler i les paraules amagades

    // Es guardaran les paraules trobades, en ordre alfabètic, als fitxers
    // "trie.out", "bloom.out", ..., que es crearan de nou.
    fstream trieOut, bloomOut;
    trieOut.open("trie.out", fstream::out | fstream::trunc);
    bloomOut.open("bloom.out", fstream::out | fstream::trunc);

    if (trieOut.fail() || bloomOut.fail()){
        cout << "There's been an error opening an output file.\n" << endl;
        return -1;
    }

    DiccTrie trie(dicc);
    trie.findWords(B, solution);
    printSet(solution, trieOut);
    solution.clear();

    solution.clear();
    Bloom bloom(dicc, nPrefixes);
    bloom.findWords(B, solution);
    printSet(solution, bloomOut);
}
