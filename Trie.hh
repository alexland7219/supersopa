#ifndef TRIE_HH
#define TRIE_HH

#include <vector>
#include <string>
using namespace std;

class Trie {

    private:
 
    bool is_word;
    vector<Trie *> children;

    public:

    Trie(char c);
    bool checkWord(string s, int i);
    void setWord(string s, int i);
};

#endif