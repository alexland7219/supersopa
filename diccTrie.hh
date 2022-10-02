#ifndef DICCTRIE_HH
#define DICCTRIE_HH

#include "Trie.hh"
using namespace std;

class DiccTrie {

    private:
    Trie* root;

    public:

    DiccTrie(const vector<string>& dict);

    bool checkWord(string s);
};

#endif