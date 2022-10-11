#include "Ternary.hh"

Ternary::Ternary(char c) {
    is_word = false;
    left = NULL;
    center = NULL;
    right = NULL;
    key = c;
}

void Ternary::setWord(string s, int i) {
    if (s[i] == key) {
        if (i == s.size() - 1) {
            is_word = true;
            return;
        }
        if (center == NULL) center = new Ternary(s[i + 1]);
        center->setWord(s, i + 1);
    }
    else if (s[i] > key) {
        if (right == NULL) right = new Ternary(s[i]);
        right->setWord(s, i);
    }
    else {
        if (left == NULL) left = new Ternary(s[i]);
        left->setWord(s, i);
    }
}

void Ternary::findWords(Board& sopa, int i, int j, set<pair<int, int>> visited, string s, set<string>& found) {
    if (i < 0 or j < 0 or i >= sopa.getSize() or j >= sopa.getSize() or visited.find(make_pair(i, j)) != visited.end()) return;
    
    if (sopa.getCasella(i, j) > key and right != NULL) right->findWords(sopa, i, j, visited, s, found);
    else if (sopa.getCasella(i, j) < key and left != NULL) left->findWords(sopa, i, j, visited, s, found);
    else if (sopa.getCasella(i, j) == key) {
        s.push_back(sopa.getCasella(i, j));
        visited.insert(make_pair(i, j));
        if (is_word) found.insert(s);
        if (center == NULL) return;
        center->findWords(sopa, i + 1, j, visited, s, found);
        center->findWords(sopa, i, j + 1, visited, s, found);
        center->findWords(sopa, i - 1, j, visited, s, found);
        center->findWords(sopa, i, j - 1, visited, s, found);
        center->findWords(sopa, i + 1, j + 1, visited, s, found);
        center->findWords(sopa, i + 1, j - 1, visited, s, found);
        center->findWords(sopa, i - 1, j + 1, visited, s, found);
        center->findWords(sopa, i - 1, j - 1, visited, s, found);
    }
}
