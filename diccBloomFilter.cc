#include "diccBloomFilter.hh"

Bloom::Bloom(vector<string>& s){
    for (string str : s){
        addWord(str);
    }
}

int Bloom::Hash1(string s){
    // Polinomic multiplication
    // S'observa bona distribució uniforme quan p = 53
    int p = 53;
    uint32_t i = 1;

    for (int j = 0; j < s.size(); ++j){
        i += s[j] * pow(p, j)
        i %= M;
    }

    return i;
}

int Bloom:Hash2(string s){
    // Multiplication with prime numbers
    int i = 7;
    for (int j = 0; j < s.size(); ++j){
        i = (i * 127) + s[j];
        i %= M;
    }

    return i;
}