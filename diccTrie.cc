#include "diccTrie.hh"

DiccTrie::DiccTrie(const vector<string>& dict) {
    root = new Trie('0');
    for (int i = 0; i < dict.size(); ++i) root->setWord(dict[i], 0);
}

bool DiccTrie::checkWord(string s) {
    return true;
}