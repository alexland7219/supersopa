#include "diccTrie.hh"

DiccTrie::DiccTrie(const vector<string>& dict) {
    root = new Trie('0');
    for (int i = 0; i < dict.size(); ++i) root->setWord(dict[i], 0);
}

void DiccTrie::findWords(Board& sopa, set<string>& found) {
    for (int i = 0; i < sopa.getSize(); ++i) {
        for (int j = 0; j < sopa.getSize(); ++j) {
            set<pair<int, int>> visited;
            string s;
            root->findWords(sopa, i, j, visited, s, found);
        }
    }
}