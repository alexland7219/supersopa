#include "diccTernary.hh"

DiccTernary::DiccTernary(const vector<string>& dict) {
    root = new Ternary(dict[0][0]);
    for (int i = 0; i < dict.size(); ++i) {
        root->setWord(dict[i], 0);
    }
}

void DiccTernary::findWords(Board& sopa, set<string>& found) {
    vector<vector<bool>> visited(sopa.getSize(), vector<bool>(sopa.getSize(), false));
    for (int i = 0; i < sopa.getSize(); ++i) {
        for (int j = 0; j < sopa.getSize(); ++j) {
            string s = "";
            s.push_back(sopa.getCasella(i, j));
            //visited.insert(make_pair(i, j));
            visited[i][j] = true;
            root->findWords(sopa, i, j, s, visited, found);
            //visited.erase(make_pair(i, j));
            visited[i][j] = false;
        }
    }
}