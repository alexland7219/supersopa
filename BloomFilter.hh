#ifndef BLOOMFILTER_HH
#define BLOOMFILTER_HH

#include <string>
#include <vector>
#include <cstring>
#include <math.h>
#include <set>
#include "board.hh"
using namespace std;

class Bloom {

    private:

    // Bloom array. We set m = 1000000 and k = 6
    static const uint32_t MB = 100000;
    static const uint32_t MP = 800000;
    vector<bool> B; // words
    vector<bool> P; // prefixes of words

    static int hash1(string s, bool firstModulus);
    static int hash2(string s, bool firstModulus);
    static int hash3(string s, bool firstModulus);
    static int hash4(string s, bool firstModulus);
    static int hash5(string s, bool firstModulus);
    static int hash6(string s, bool firstModulus);

    static inline uint32_t murmur32_scramble(uint32_t k);

    public:

    Bloom(vector<string>& s);

    void addWord(string s);
    bool checkWord(string s);
    void addPrefix(string s);
    bool checkPrefix(string s);

    void findWords(Board& board);
    void localSearch(Board& board, int i, int j, string& s, set<pair<int, int>>& visitats);
};

#endif