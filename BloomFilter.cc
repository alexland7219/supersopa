#include "BloomFilter.hh"
using std::string, std::vector;

Bloom::Bloom(vector<string>& s){
    for (string str : s){
        addWord(str);
    }
};

int Bloom::hash1(string s){
    // Polinomic multiplication with prime coefficient
    // S'observa bona distribució uniforme quan p = 53
    int p = 53;
    uint32_t i = 1;

    for (int j = 0; j < s.size(); ++j){
        i += s[j] * pow(p, j);
        i %= M;
    }

    return i;
};

int Bloom::hash2(string s){
    // Multiplication with prime numbers
    uint32_t i = 7;
    for (int j = 0; j < s.size(); ++j){
        i = (i * 127) + s[j];
        i %= M;
    }

    return i;
}

int Bloom::hash3(string s){
    // djb2 by Dan Bernstein http://www.cse.yorku.ca/~oz/hash.html
    unsigned long hash = 5381;
    int c;
    char * p = &s[0];

    while(c = *p++)
        hash = ((hash << 5) + hash) + c;

    return (hash % M);
}

int Bloom::hash4(string s){
    // PJW hash function https://www.cs.hmc.edu/~geoff/classes/hmc.cs070.200101/homework10/hashfuncs.html
    char * p = &s[0];
    unsigned long h = 0, g;

    while(*p){

        h = (h << 4) + *p++;
        g = h & 0xF000000;

        if (g != 0){
            h = h ^ (g >> 24);
            h = h ^ g;
        }
    }

    return (h % M);
}

int Bloom::hash5(string s){
    // Jenkins' one-at-a-time hash function http://www.burtleburtle.net/bob/hash/doobs.html
    uint32_t hash = 0;

    for (int i = 0; i < s.size(); ++i){
        hash += s[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }

    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    
    return (hash % M); 
}

inline uint32_t Bloom::murmur32_scramble(uint32_t k){
    k *= 0xCC9E2D51;
    k = (k << 15) | (k >> 17);
    k *= 0x1B873593;
    return k;
}

int Bloom::hash6(string s){
    // Murmur3 Cryptographic hashing function https://en.wikipedia.org/wiki/MurmurHash

    uint32_t seed = 0;
    char* key = &s[0]; 

    // Let the seed be the sum of the characters
    for (char c : s) seed += c;

    uint32_t hash = seed;
    uint32_t k;

    // Read in groups of 4
    for (int i = s.size()>>2; i; i--){
        memcpy(&k, key, sizeof(uint32_t));
        key += sizeof(uint32_t);
        hash ^= murmur32_scramble(k);
        hash = (hash << 13) | (hash >> 19);
        hash = hash * 5 + 0xE6546B64;
    }

    k = 0;
    for (int i = s.size() & 3; i; i--){
        k <<= 8;
        k |= key[i-1];
    }

    hash ^= murmur32_scramble(k);

    hash ^= s.size();
    hash ^= (hash >> 16);
    hash *= 0x85EBCA6B;
    hash ^= (hash >> 13);
    hash *= 0xC2B2AE35;
    hash ^= (hash >> 16);

    return (hash % M);
}

void Bloom::addWord(string s){
    // For every hash functionw we evaluate and set the corresponding bit to 1
    B[hash1(s)] = 1;
    B[hash2(s)] = 1;
    B[hash3(s)] = 1;
    B[hash4(s)] = 1;
    B[hash5(s)] = 1;
    B[hash6(s)] = 1;
}

bool Bloom::checkWord(string s){
    // If it returns true IT COULD BE A FALSE POSITIVE
    // If it returns false then IT IS NOT IN THE DICTIONARY
    return (B[hash1(s)] && B[hash2(s)] && B[hash3(s)] && B[hash4(s)] && B[hash5(s)] && B[hash6(s)]);
}
