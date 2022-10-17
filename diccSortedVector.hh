#ifndef DICCSORTEDVECTOR_HH
#define DICCSORTEDVECTOR_HH

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <set>
#include "board.hh"

using namespace std;

class SortedVector {
    private:
        vector<string> SortedDicc;
        vector<int> Index;

        void fillIndex(int i, int j, char c);

    public:
        SortedVector(vector<string>& dicc);

        int checkPrefix(int i, int j, string& s);
        void localSearch(Board& board, int i, int j, int& ini, int& fin, string& s, vector<vector<bool>>& visitats, set<string>& foundWords);
        void findWords(Board& TomatoSoup, set<string>& foundWords);

};

#endif
