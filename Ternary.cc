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

void Ternary::findWords(Board& sopa, int i, int j, string& s, vector<vector<bool>>& visited, set<string>& found) {
    
    if (sopa.getCasella(i, j) > key and right != NULL) right->findWords(sopa, i, j, s, visited, found);
    else if (sopa.getCasella(i, j) < key and left != NULL) left->findWords(sopa, i, j, s, visited, found);
    else if (sopa.getCasella(i, j) == key) {
        if (is_word) found.insert(s);
        if (center == NULL) return;
    if (i > 0 && j > 0 && not visited[i-1][j-1]){
        s.push_back(sopa.getCasella(i-1, j-1));
            visited[i-1][j-1] = true;
            center->findWords(sopa, i-1, j-1, s, visited, found);
            visited[i-1][j-1] = false;

        s.pop_back(); 
    }

    if (i > 0 && j < sopa.getSize() - 1 && not visited[i-1][j+1]){
        s.push_back(sopa.getCasella(i-1, j+1));
            visited[i-1][j+1] = true;
            center->findWords(sopa, i-1, j+1, s, visited, found);
            visited[i-1][j+1] = false;
        s.pop_back();
    }

    if (i < sopa.getSize() - 1 && j > 0 && not visited[i+1][j-1]){
        s.push_back(sopa.getCasella(i+1, j-1));
            visited[i+1][j-1] = true;
            center->findWords(sopa, i+1, j-1, s, visited, found);
            visited[i+1][j-1] = false;
        s.pop_back(); 
    }

    if (i < sopa.getSize() - 1 && j < sopa.getSize() - 1 && not visited[i+1][j+1]){
        s.push_back(sopa.getCasella(i+1, j+1));
            visited[i+1][j+1] = true;
            center->findWords(sopa, i+1, j+1, s, visited, found);
            visited[i+1][j+1] = false;
        s.pop_back(); 
    }

    if (i > 0 && not visited[i-1][j]){
        s.push_back(sopa.getCasella(i-1, j));
            visited[i-1][j] = true;
            center->findWords(sopa, i-1, j, s, visited, found);
            visited[i-1][j] = false;
        s.pop_back(); 
    }

    if (i < sopa.getSize() - 1 && not visited[i+1][j]){
        s.push_back(sopa.getCasella(i+1, j));
            visited[i+1][j] = true;
            center->findWords(sopa, i+1, j, s, visited, found);
            visited[i+1][j] = false;
        s.pop_back(); 
    }

    if (j > 0 && not visited[i][j-1]){
        s.push_back(sopa.getCasella(i, j-1));
            visited[i][j-1] = true;
            center->findWords(sopa, i, j-1, s, visited, found);
            visited[i][j-1] = false;
        s.pop_back(); 
    }

    if (j < sopa.getSize() - 1 && not visited[i][j+1]){
        s.push_back(sopa.getCasella(i, j+1));
            visited[i][j+1] = true;
            center->findWords(sopa, i, j+1, s, visited, found);
            visited[i][j+1] = false;
        s.pop_back(); 
    }
    }
}
