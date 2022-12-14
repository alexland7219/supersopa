#ifndef TERNARY_HH
#define TERNARY_HH

#include <iostream>
#include <string>
#include "board.hh"
using namespace std;

class Ternary {

    private:
    
    char key;
    bool is_word;
    Ternary* left;
    Ternary* center;
    Ternary* right;

    public:

    Ternary(char c);
    void setWord(string s, int i);
    void findWords(Board& sopa, int i, int j, string& s, vector<vector<bool>>& visited, set<string>& found);
};

#endif