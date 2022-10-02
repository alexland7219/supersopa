#include "diccBloomFilter.hh"

Bloom::Bloom(vector<string>& s){
    for (string str : s){
        addWord(str);
    }
}

int Bloom::Hash1(string s){
    // Polinomic multiplication with prime coefficient
    // S'observa bona distribució uniforme quan p = 53
    int p = 53;
    uint32_t i = 1;

    for (int j = 0; j < s.size(); ++j){
        i += s[j] * pow(p, j)
        i %= M;
    }

    return i;
}

int Bloom::Hash2(string s){
    // Multiplication with prime numbers
    uint32_t i = 7;
    for (int j = 0; j < s.size(); ++j){
        i = (i * 127) + s[j];
        i %= M;
    }

    return i;
}

int Bloom::Hash3(string s){
    // djb2 by Dan Bernstein http://www.cse.yorku.ca/~oz/hash.html
    unsigned long hash = 5381;
    int c;
    char * p = &s[0];

    while(c = *p++)
        hash = ((hash << 5) + hash) + c;

    return (hash % M);
}

int Bloom::Hash4(string s){
    // PJW hash function https://www.cs.hmc.edu/~geoff/classes/hmc.cs070.200101/homework10/hashfuncs.html
    char * p = &s[0];
    unsigned long h = 0, g;

    while(*p){

        h = (h << 4) + *p++;
        g = h & 0xF000000;

        if (g != 0)
            h = h ^ (g >> 24);
            h = h ^ g;
    }

    return (h % 100000);
}