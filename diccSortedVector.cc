#include "diccSortedVector.hh"

SortedVector::SortedVector(vector<string>& dicc) {
    SortedDicc.resize(dicc.size());
    SortedDicc = dicc;
    sort(SortedDicc.begin(), SortedDicc.end());

    Index = vector<int>(26, -1);
    char ini = SortedDicc[0][0];
    char fin = SortedDicc[SortedDicc.size() - 1][0];
    Index[ini - 'A'] = 0;

    if (ini != fin) { // si hay al menos otra letra más
        fillIndex(0, SortedDicc.size() - 1, fin);
    }
}

void SortedVector::fillIndex(int i, int j, char c) {
    if (i < j) { // estamos buscando el char
        int k = (i + j) / 2; // cogemos la mediana
        char q = SortedDicc[k][0];
        if (q < c) { // encontramos un char menor al que buscamos
            if (Index[q - 'A'] == -1) { // si no lo tenemos indexado lo hacemos
                fillIndex(i, k, q);
            }
            fillIndex(k+1, j, c);
        }
        else {
            string s;
            s = c;
            if (s == SortedDicc[k]) Index[c - 'A'] = k;
            else fillIndex(i, k, c);
        }
    }
    else Index[c - 'A'] = i; // tenemos la primera posición donde aparece el char
}

int SortedVector::checkPrefix(int i, int j, string& s) {
    if (i < j) { // estamos buscando el prefix
        int k = (i + j) / 2; // cogemos la mediana

        if (s < SortedDicc[k]) {
            if (s.size() <= SortedDicc[k].size() && s[s.size()-1] == SortedDicc[k][s.size()-1]) {
                return checkPrefix(i, k, s);
            }
            else return checkPrefix(i, k-1, s);
        }
        else if (s > SortedDicc[k]) {
            return checkPrefix(k+1, j, s);
        }
        else return k;
    }

    else if (s.size() <= SortedDicc[i].size() && s[s.size()-1] == SortedDicc[i][s.size()-1]) return i;

    else return -1;
}

void SortedVector::localSearch(Board& board, int i, int j, int& ini, int& fin, string& s, set<pair<int, int>>& visitats, set<string>& foundWords){
    // Supposing on (i, j) there's a valid prefix and has been marked as visited
    if (s == SortedDicc[ini]) foundWords.insert(s);

    int iniPrefix = -1;
    if (i > 0 && j > 0) {
        s.push_back(board.getCasella(i-1, j-1));

        iniPrefix = checkPrefix(ini, fin, s);
        if ((iniPrefix != -1) && visitats.insert(make_pair(i-1, j-1)).second) {
            localSearch(board, i-1, j-1, iniPrefix, fin, s, visitats, foundWords);
            visitats.erase(make_pair(i-1, j-1));
        }

        s.pop_back();
    }

    if (i > 0 && j < board.getSize() - 1) {
        s.push_back(board.getCasella(i-1, j+1));

        iniPrefix = checkPrefix(ini, fin, s);
        if ((iniPrefix != -1) && visitats.insert(make_pair(i-1, j+1)).second) {
            localSearch(board, i-1, j+1, iniPrefix, fin, s, visitats, foundWords);
             visitats.erase(make_pair(i-1, j+1));
        }

        s.pop_back();
    }

    if (i < board.getSize() - 1 && j > 0) {
        s.push_back(board.getCasella(i+1, j-1));

        iniPrefix = checkPrefix(ini, fin, s);
        if ((iniPrefix != -1) && visitats.insert(make_pair(i+1, j-1)).second) {
            localSearch(board, i+1, j-1, iniPrefix, fin, s, visitats, foundWords);
            visitats.erase(make_pair(i+1, j-1));
        }

        s.pop_back();
    }

    if (i < board.getSize() - 1 && j < board.getSize() - 1) {
        s.push_back(board.getCasella(i+1, j+1));

        iniPrefix = checkPrefix(ini, fin, s);
        if ((iniPrefix != -1) && visitats.insert(make_pair(i+1, j+1)).second) {
            localSearch(board, i+1, j+1, iniPrefix, fin, s, visitats, foundWords);
            visitats.erase(make_pair(i+1, j+1));
        }

        s.pop_back();
    }

    if (i > 0) {
        s.push_back(board.getCasella(i-1, j));

        iniPrefix = checkPrefix(ini, fin, s);
        if ((iniPrefix != -1) && visitats.insert(make_pair(i-1, j)).second) {
            localSearch(board, i-1, j, iniPrefix, fin, s, visitats, foundWords);
            visitats.erase(make_pair(i-1, j));
        }

        s.pop_back();
    }

    if (i < board.getSize() - 1) {
        s.push_back(board.getCasella(i+1, j));

        iniPrefix = checkPrefix(ini, fin, s);
        if ((iniPrefix != -1) && visitats.insert(make_pair(i+1, j)).second) {
            localSearch(board, i+1, j, iniPrefix, fin, s, visitats, foundWords);
            visitats.erase(make_pair(i+1, j));
        }

        s.pop_back();
    }

    if (j > 0){
        s.push_back(board.getCasella(i, j-1));

        iniPrefix = checkPrefix(ini, fin, s);
        if ((iniPrefix != -1) && visitats.insert(make_pair(i, j-1)).second) {
            localSearch(board, i, j-1, iniPrefix, fin, s, visitats, foundWords);
            visitats.erase(make_pair(i, j-1));
        }

        s.pop_back();
    }

    if (j < board.getSize() - 1) {
        s.push_back(board.getCasella(i, j+1));

        iniPrefix = checkPrefix(ini, fin, s);
        if ((iniPrefix != -1) && visitats.insert(make_pair(i, j+1)).second) {
            localSearch(board, i, j+1, iniPrefix, fin, s, visitats, foundWords);
            visitats.erase(make_pair(i, j+1));
        }

        s.pop_back();
    }

}

void SortedVector::findWords(Board& TomatoSoup, set<string>& foundWords) {
    for (int i = 0; i < TomatoSoup.getSize(); ++i) {
        for (int j = 0; j < TomatoSoup.getSize(); ++j) {

            string pre = "";
            pre.push_back(TomatoSoup.getCasella(i, j));

            int ini = Index[pre[0] - 'A'];
            if (ini != -1) {
                int fin = SortedDicc.size() - 1;
                char k = pre[0] + 1;

                while (k <= 'Z') {
                    if (Index[k - 'A'] != -1) {
                        fin = Index[k - 'A'];
                        k = 'Z' + 1;
                    }
                    else ++k;
                }

                set<pair<int, int>> visitats;
                visitats.insert(make_pair(i, j));

                localSearch(TomatoSoup, i, j, ini, fin, pre, visitats, foundWords);
            }
        }
    }
}
