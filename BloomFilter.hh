#ifndef BLOOMFILTER_HH
#define BLOOMFILTER_HH

#include <string>
#include <bitset>
using std::bitset;

class Bloom {

    private:

    // Bloom array. We set m = 100000 and k = 6
    static const uint32_t M = 100000;
    bitset<100000> B;

    int Hash1(string s);
    int Hash2(string s);
    int Hash3(string s);
    int Hash4(string s);
    int Hash5(string s);
    int Hash6(string s);


    public:

    Bloom(vector<string>& dict);

    void addWord(string s);
    bool checkWord(string s);
};

#endif