#include "Trie.hh"

Trie::Trie(char c) {
    is_word = false;
    children = vector<Trie *>(26, NULL);
}

void Trie::setWord(string s, int i) {
    if (i == s.size()) {
        is_word = true;
        return;
    }

    if (children[s[i] - 'A'] == NULL) children[s[i] - 'A'] = new Trie(s[i]);
    children[s[i] - 'A']->setWord(s, i + 1);
}

void Trie::findWords(Board& sopa, int i, int j, set<pair<int, int>> visited, string s) {
    int n = sopa.getSize();
    if (i < 0 or j < 0 or i >= n or j >= n or visited.find(make_pair(i, j)) != visited.end() or children[sopa.getCasella(i, j) - 'A'] == NULL) return;

    s.push_back(sopa.getCasella(i, j));

    if (children[sopa.getCasella(i, j) - 'A']->is_word) cout << "Found " << s << endl;
    visited.insert(make_pair(i, j));

    children[sopa.getCasella(i, j) - 'A']->findWords(sopa, i + 1, j, visited, s);
    children[sopa.getCasella(i, j) - 'A']->findWords(sopa, i, j + 1, visited, s);
    children[sopa.getCasella(i, j) - 'A']->findWords(sopa, i - 1, j, visited, s);
    children[sopa.getCasella(i, j) - 'A']->findWords(sopa, i, j - 1, visited, s);
    children[sopa.getCasella(i, j) - 'A']->findWords(sopa, i + 1, j + 1, visited, s);
    children[sopa.getCasella(i, j) - 'A']->findWords(sopa, i + 1, j - 1, visited, s);
    children[sopa.getCasella(i, j) - 'A']->findWords(sopa, i - 1, j + 1, visited, s);
    children[sopa.getCasella(i, j) - 'A']->findWords(sopa, i - 1, j - 1, visited, s);
}