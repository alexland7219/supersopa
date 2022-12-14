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
            if (s == SortedDicc[k]) {
                Index[c - 'A'] = k;
                if (Index[SortedDicc[k-1][0] - 'A'] == -1) {
                    fillIndex(i, k-1, c);
                }
            }
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

void SortedVector::localSearch(Board& board, int i, int j, int& ini, int& fin, string& s, vector<vector<bool>>& visitats, set<string>& foundWords){
    // Supposing on (i, j) there's a valid prefix and has been marked as visited
    if (s == SortedDicc[ini]) foundWords.insert(s);

    int iniPrefix = -1;
    if (i > 0 && j > 0) {
        s.push_back(board.getCasella(i-1, j-1));

        iniPrefix = checkPrefix(ini, fin, s);
        if ((iniPrefix != -1) && !visitats[i-1][j-1]) {
			visitats[i-1][j-1] = true;
            localSearch(board, i-1, j-1, iniPrefix, fin, s, visitats, foundWords);
            visitats[i-1][j-1] = false;
        }

        s.pop_back();
    }

    if (i > 0 && j < board.getSize() - 1) {
        s.push_back(board.getCasella(i-1, j+1));

        iniPrefix = checkPrefix(ini, fin, s);
        if ((iniPrefix != -1) && !visitats[i-1][j+1]) {
			visitats[i-1][j+1] = true;
            localSearch(board, i-1, j+1, iniPrefix, fin, s, visitats, foundWords);
            visitats[i-1][j+1] = false;
        }

        s.pop_back();
    }

    if (i < board.getSize() - 1 && j > 0) {
        s.push_back(board.getCasella(i+1, j-1));

        iniPrefix = checkPrefix(ini, fin, s);
        if ((iniPrefix != -1) && !visitats[i+1][j-1]) {
			visitats[i+1][j-1] = true;
            localSearch(board, i+1, j-1, iniPrefix, fin, s, visitats, foundWords);
            visitats[i+1][j-1] = false;
        }

        s.pop_back();
    }

    if (i < board.getSize() - 1 && j < board.getSize() - 1) {
        s.push_back(board.getCasella(i+1, j+1));

        iniPrefix = checkPrefix(ini, fin, s);
        if ((iniPrefix != -1) && !visitats[i+1][j+1]) {
			visitats[i+1][j+1] = true;
            localSearch(board, i+1, j+1, iniPrefix, fin, s, visitats, foundWords);
            visitats[i+1][j+1] = false;
        }

        s.pop_back();
    }

    if (i > 0) {
        s.push_back(board.getCasella(i-1, j));

        iniPrefix = checkPrefix(ini, fin, s);
        if ((iniPrefix != -1) && !visitats[i-1][j]) {
			visitats[i-1][j] = true;
            localSearch(board, i-1, j, iniPrefix, fin, s, visitats, foundWords);
            visitats[i-1][j] = false;
        }

        s.pop_back();
    }

    if (i < board.getSize() - 1) {
        s.push_back(board.getCasella(i+1, j));

        iniPrefix = checkPrefix(ini, fin, s);
        if ((iniPrefix != -1) && !visitats[i+1][j]) {
			visitats[i+1][j] = true;
            localSearch(board, i+1, j, iniPrefix, fin, s, visitats, foundWords);
            visitats[i+1][j] = false;
        }

        s.pop_back();
    }

    if (j > 0){
        s.push_back(board.getCasella(i, j-1));

        iniPrefix = checkPrefix(ini, fin, s);
        if ((iniPrefix != -1) && !visitats[i][j-1]) {
			visitats[i][j-1] = true;
            localSearch(board, i, j-1, iniPrefix, fin, s, visitats, foundWords);
            visitats[i][j-1] = false;
        }

        s.pop_back();
    }

    if (j < board.getSize() - 1) {
        s.push_back(board.getCasella(i, j+1));

        iniPrefix = checkPrefix(ini, fin, s);
        if ((iniPrefix != -1) && !visitats[i][j+1]) {
			visitats[i][j+1] = true;
            localSearch(board, i, j+1, iniPrefix, fin, s, visitats, foundWords);
            visitats[i][j+1] = false;
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

                vector<vector<bool>> visitats(TomatoSoup.getSize(), vector<bool>(TomatoSoup.getSize(), false));
                visitats[i][j] = true;

                localSearch(TomatoSoup, i, j, ini, fin, pre, visitats, foundWords);
            }
        }
    }
}
