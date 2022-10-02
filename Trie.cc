#include "Trie.hh"

Trie::Trie(char c) {
    is_word = false;
    children = vector<Trie *>(26, NULL);
}

bool Trie::getIsWord() {
    return is_word;
}

void Trie::setWord(string s, int i) {
    if (i == s.size()) {
        is_word = true;
        return;
    }

    if (children[s[i] - 'A'] == NULL) {
        children[s[i] - 'A'] = new Trie(s[i]);
    }
    children[s[i] - 'A']->setWord(s, i + 1);
}