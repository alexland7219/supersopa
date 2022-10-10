#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <chrono>
#include "board.hh"
#include "BloomFilter.hh"
#include "diccTrie.hh"
#include "diccDHashing.hh"
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
        out << *it << endl;
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
    fstream trieOut, bloomOut, dhashOut;
    trieOut.open("trie.out", fstream::out | fstream::trunc);
    bloomOut.open("bloom.out", fstream::out | fstream::trunc);
    dhashOut.open("dhash.out", fstream::out | fstream::trunc);

    if (trieOut.fail() || bloomOut.fail() || dhashOut.fail()){
        cout << "There's been an error opening an output file.\n" << endl;
        return -1;
    }

    // Per a mesurar el temps de cada algorisme
    chrono::steady_clock::time_point startTime = chrono::steady_clock::now();

    DiccTrie trie(dicc);
    trie.findWords(B, solution);

    chrono::steady_clock::time_point finishTime = chrono::steady_clock::now();
    chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(finishTime - startTime);
    trieOut << "Trie took " << time_span.count()*1000 << " milliseconds\n" << endl;

    printSet(solution, trieOut);
    solution.clear();

    startTime = chrono::steady_clock::now();

    Bloom bloom(dicc, nPrefixes);
    bloom.findWords(B, solution);
    
    finishTime = chrono::steady_clock::now();
    time_span = chrono::duration_cast<chrono::duration<double>>(finishTime - startTime);
    bloomOut << "Bloom Filter took " << time_span.count()*1000 << " milliseconds\n" << endl;

    printSet(solution, bloomOut);
    solution.clear();

    startTime = chrono::steady_clock::now();

    DHash dhash(nPrefixes, dicc);
    dhash.findWords(B, solution);

    finishTime = chrono::steady_clock::now();
    time_span = chrono::duration_cast<chrono::duration<double>>(finishTime - startTime);
    dhashOut << "Double Hashing took " << time_span.count()*1000 << " milliseconds\n" << endl;

    printSet(solution, dhashOut);
    solution.clear();
}
