#include "Trie.hh"

Trie::Trie(char c) {
    is_word = false;
    children = vector<Trie *>(26, NULL);
}

bool Trie::checkWord(string s, int i) {
    if (i == s.size()) return is_word;
    if (children[s[i] - 'A'] == NULL) return false;
    return children[s[i] - 'A']->checkWord(s, i + 1);
}

void Trie::setWord(string s, int i) {
    if (i == s.size()) {
        is_word = true;
        return;
    }

    if (children[s[i] - 'A'] == NULL) children[s[i] - 'A'] = new Trie(s[i]);
    children[s[i] - 'A']->setWord(s, i + 1);
}