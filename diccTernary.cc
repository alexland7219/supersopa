#include "diccTernary.hh"

DiccTernary::DiccTernary(const vector<string>& dict) {
    root = new Ternary(dict[0][0]);
    for (int i = 0; i < dict.size(); ++i) {
        root->setWord(dict[i], 0);
    }
}

void DiccTernary::findWords(Board& sopa, set<string>& found) {
    for (int i = 0; i < sopa.getSize(); ++i) {
        for (int j = 0; j < sopa.getSize(); ++j) {
            set<pair<int, int>> visited;
            string s = "";
            s.push_back(sopa.getCasella(i, j));
            visited.insert(make_pair(i, j));
            root->findWords(sopa, i, j, s, visited, found);
            visited.erase(make_pair(i, j));
        }
    }
}