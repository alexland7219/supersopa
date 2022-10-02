#ifndef TRIE_HH
#define TRIE_HH

#include <vector>
#include <string>
using namespace std;

class Trie {

    private:
 
    char val;
    bool is_word;
    vector<Trie *> children;

    public:

    Trie(char c);

    char getValue();
    bool getIsWord();
    void setWord(string s, int i);
};

#endif