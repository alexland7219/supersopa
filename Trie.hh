#ifndef TRIE_HH
#define TRIE_HH

#include <iostream>
#include <vector>
#include <string>
#include "board.hh"
using namespace std;

class Trie {

    private:
 
    bool is_word;
    vector<Trie *> children;

    public:

    Trie(char c);
    void setWord(string s, int i);
    void findWords(Board& sopa, int i, int j, set<pair<int, int>> visited, string s);
};

#endif