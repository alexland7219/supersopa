#ifndef BLOOMFILTER_HH
#define BLOOMFILTER_HH

#include <string>
#include <bitset>
#include <vector>
#include <cstring>
#include <math.h>
using std::bitset, std::string, std::vector;

class Bloom {

    private:

    // Bloom array. We set m = 100000 and k = 6
    static const uint32_t M = 100000;
    bitset<100000> B;

    static int hash1(string s);
    static int hash2(string s);
    static int hash3(string s);
    static int hash4(string s);
    static int hash5(string s);
    static int hash6(string s);

    static inline uint32_t murmur32_scramble(uint32_t k);

    public:

    Bloom(vector<string>& s);

    void addWord(string s);
    bool checkWord(string s);
};

#endif