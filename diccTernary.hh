#ifndef DICCTERNARY_HH
#define DICCTERNARY_HH

#include "Ternary.hh"
using namespace std;

class DiccTernary {

    private:
    Ternary* root;

    public:

    DiccTernary(const vector<string>& dict);

    void findWords(Board& sopa, set<string>& found);
};

#endif