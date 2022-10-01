#ifndef BOARD_HH
#define BOARD_HH

#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

class Board {

    private:

    vector<vector<char>> board; // tauler del Joc
    bool place_string(string s, int i, int posx, int posy);
    char randomLetter();

    public:

    Board(int n, const set<string>& p);

    char getCasella(int x, int y);

	void print();
};

#endif
