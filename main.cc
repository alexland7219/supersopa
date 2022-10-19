#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <chrono>
#include "board.hh"
#include "BloomFilter.hh"
#include "diccDHashing.hh"
#include "diccTernary.hh"
#include "diccSortedVector.hh"
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

    int nParaules = 20; // Nombre de paraules a amagar
    int N = 50;        // Mida del tauler NxN
    
    // Nombre de prefixos totals de tot el diccionari
    unsigned int nPrefixes = 0;

    string x;
    while (cin >> x) {
        transform(x.begin(), x.end(), x.begin(), ::toupper);
        dicc.push_back(x);
        nPrefixes += x.size() - 1; // La paraula sencera no compta com a prefix
    }

    set<string> P;
    selectNRandom(P, dicc, nParaules);
    
    Board B = Board(N, P);
	B.print(); // Fem un print a stdout de el tauler i les paraules amagades

    // Es guardaran les paraules trobades, en ordre alfabètic, als fitxers
    // "trie.out", "bloom.out", ..., que es crearan de nou.
    fstream bloomOut, dhashOut, ternaryOut, vectorOut;
    bloomOut.open("bloom.out", fstream::out | fstream::trunc);
    dhashOut.open("dhash.out", fstream::out | fstream::trunc);
    ternaryOut.open("ternary.out", fstream::out | fstream::trunc);
    vectorOut.open("vector.out", fstream::out | fstream::trunc);

    if (bloomOut.fail() || dhashOut.fail() || ternaryOut.fail() || vectorOut.fail()){
        cout << "There's been an error opening an output file.\n" << endl;
        return -1;
    }

    // Per a mesurar el temps de cada algorisme
    chrono::steady_clock::time_point startTime = chrono::steady_clock::now();

    Bloom bloom(dicc, nPrefixes, 0.00001); // On la última constant és la probabilitat de falsos positius, en tant per u.
    bloom.findWords(B, solution);
    
    chrono::steady_clock::time_point finishTime = chrono::steady_clock::now();
    chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(finishTime - startTime);
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

    startTime = chrono::steady_clock::now();

    DiccTernary ternary(dicc);
    ternary.findWords(B, solution);

    finishTime = chrono::steady_clock::now();
    time_span = chrono::duration_cast<chrono::duration<double>>(finishTime - startTime);
    ternaryOut << "Ternary took " << time_span.count()*1000 << " milliseconds\n" << endl;

    printSet(solution, ternaryOut);
    solution.clear();

    startTime = chrono::steady_clock::now();

    SortedVector sVector(dicc);
    sVector.findWords(B, solution);

    finishTime = chrono::steady_clock::now();
    time_span = chrono::duration_cast<chrono::duration<double>>(finishTime - startTime);
    vectorOut << "SortedVector took " << time_span.count()*1000 << " milliseconds\n" << endl;

    printSet(solution, vectorOut);
    solution.clear();
}
