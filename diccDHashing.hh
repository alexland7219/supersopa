#ifndef DICCDHASHING_HH
#define DICCDHASHING_HH

#include <string>
#include <vector>
#include <set>
#include <cmath>
#include <iostream>
#include "board.hh"
using namespace std;

class DHash {

    private:
    vector<string> table;
    vector<string> tablePrefixes;

    int hash1(string s);
    int nextprime(unsigned int k);
    bool fermatTest(unsigned int p, unsigned int tests);

    //solver de les colisions de hash1
    int hash2(string s);

    public:

    DHash(unsigned int n_prefixes, vector<string>& dicc);

    void addWord(string& paraula);
    void addPrefix(string& pre);
    bool checkWord(string& word);
    bool checkPrefix(string& word);

    void findWords(Board& board, set<string>& foundWords);
    void localSearch(Board& board, int i, int j, string& s, vector<vector<bool>>& visitats, set<string>& foundWords);

};

#endif
