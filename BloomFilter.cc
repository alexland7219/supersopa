#include "BloomFilter.hh"
using namespace std;

Bloom::Bloom(vector<string>& s, unsigned int nPrefixes){
    // Initializing B and P, MB and MP
    MB = (uint32_t) ceil(s.size()*6. / -log(1.-exp(log(0.0001)/6)));
    MP = (uint32_t) ceil(nPrefixes*6 / -log(1-exp(log(0.0001)/6)));

    B.resize(MB); fill(B.begin(), B.end()-1, false);
    P.resize(MP); fill(P.begin(), P.end()-1, false);

    for (string str : s){
        string pre = "";

        for (int i = 0; i < str.size() - 1; ++i){
            pre.push_back(str[i]);
            addPrefix(pre);
        }

        addWord(str);
    }
};

int Bloom::hash1(string s, bool firstModulus){
    // Polinomic multiplication with prime coefficient
    // S'observa bona distribució uniforme quan p = 53
    uint32_t M;
    
    if (firstModulus) M = MB;
    else M = MP;
    
    int p = 53;
    uint32_t i = 1;

    for (int j = 0; j < s.size(); ++j){
        i += s[j] * pow(p, j);
        i %= M;
    }

    //if (firstModulus) cout << "hash 1 with string " << s << " returns " << i << endl;
    //if (!firstModulus) cout << "Hash 1 prefix " << s << " returns " << i << endl;

    return i;
};

int Bloom::hash2(string s, bool firstModulus){
    // Multiplication with prime numbers
    uint32_t M;

    if (firstModulus) M = MB;
    else M = MP;

    uint32_t i = 7;
    for (int j = 0; j < s.size(); ++j){
        i = (i * 127) + s[j];
        i %= M;
    }

    return i;
}

int Bloom::hash3(string s, bool firstModulus){
    // djb2 by Dan Bernstein http://www.cse.yorku.ca/~oz/hash.html
    uint32_t M;

    if (firstModulus) M = MB;
    else M = MP;
    
    unsigned long hash = 5381;
    int c;
    char * p = &s[0];

    while(c = *p++)
        hash = ((hash << 5) + hash) + c;

    return (hash % M);
}

int Bloom::hash4(string s, bool firstModulus){
    // PJW hash function https://www.cs.hmc.edu/~geoff/classes/hmc.cs070.200101/homework10/hashfuncs.html
    uint32_t M;

    if (firstModulus) M = MB;
    else M = MP;
    
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

int Bloom::hash5(string s, bool firstModulus){
    // Jenkins' one-at-a-time hash function http://www.burtleburtle.net/bob/hash/doobs.html
    uint32_t M;

    if (firstModulus) M = MB;
    else M = MP;
    
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

int Bloom::hash6(string s, bool firstModulus){
    // Murmur3 Cryptographic hashing function https://en.wikipedia.org/wiki/MurmurHash
    uint32_t M;

    if (firstModulus) M = MB;
    else M = MP;

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
    B[hash1(s, true)] = true;
    B[hash2(s, true)] = true;
    B[hash3(s, true)] = true;
    B[hash4(s, true)] = true;
    B[hash5(s, true)] = true;
    B[hash6(s, true)] = true;
}

void Bloom::addPrefix(string s){
    P[hash1(s, false)] = true;
    P[hash2(s, false)] = true;
    P[hash3(s, false)] = true;
    P[hash4(s, false)] = true;
    P[hash5(s, false)] = true;
    P[hash6(s, false)] = true;

}

bool Bloom::checkWord(string s){
    // If it returns true IT COULD BE A FALSE POSITIVE
    // If it returns false then IT IS NOT IN THE DICTIONARY
    return (B[hash1(s, true)] && B[hash2(s, true)] && B[hash3(s, true)] && B[hash4(s, true)] && B[hash5(s, true)] && B[hash6(s, true)]);
}

bool Bloom::checkPrefix(string s){
    return (P[hash1(s, false)] && P[hash2(s, false)] && P[hash3(s, false)] && P[hash4(s, false)] && P[hash5(s, false)] && P[hash6(s, false)]);
}

void Bloom::localSearch(Board& board, int i, int j, string& s, set<pair<int, int>>& visitats){
    // Supposing on (i, j) there's a valid prefix and has been marked as visited
    if (checkWord(s)) cout << "Found " << s << endl;

    if (i > 0 && j > 0){
        s.push_back(board.getCasella(i-1, j-1));
        
        if ((checkPrefix(s) || checkWord(s)) && visitats.insert(make_pair(i-1, j-1)).second){
            localSearch(board, i-1, j-1, s, visitats);
            visitats.erase(make_pair(i-1, j-1));
        }

        s.pop_back(); 
    }

    if (i > 0 && j < board.getSize() - 1){
        s.push_back(board.getCasella(i-1, j+1));
        
        if ((checkPrefix(s) || checkWord(s)) && visitats.insert(make_pair(i-1, j+1)).second){
            localSearch(board, i-1, j+1, s, visitats);
             visitats.erase(make_pair(i-1, j+1));
        }

        s.pop_back();
    }

    if (i < board.getSize() - 1 && j > 0){
        s.push_back(board.getCasella(i+1, j-1));
        
        if ((checkPrefix(s) || checkWord(s)) && visitats.insert(make_pair(i+1, j-1)).second){
            localSearch(board, i+1, j-1, s, visitats);
            visitats.erase(make_pair(i+1, j-1));
        }

        s.pop_back(); 
    }

    if (i < board.getSize() - 1 && j < board.getSize() - 1){
        s.push_back(board.getCasella(i+1, j+1));
        
        if ((checkPrefix(s) || checkWord(s)) && visitats.insert(make_pair(i+1, j+1)).second){
            localSearch(board, i+1, j+1, s, visitats);
            visitats.erase(make_pair(i+1, j+1));
        }

        s.pop_back(); 
    }

    if (i > 0){
        s.push_back(board.getCasella(i-1, j));
        
        if ((checkPrefix(s) || checkWord(s)) && visitats.insert(make_pair(i-1, j)).second){
            localSearch(board, i-1, j, s, visitats);
            visitats.erase(make_pair(i-1, j));
        }

        s.pop_back(); 
    }

    if (i < board.getSize() - 1){
        s.push_back(board.getCasella(i+1, j));
        
        if ((checkPrefix(s) || checkWord(s)) && visitats.insert(make_pair(i+1, j)).second){
            localSearch(board, i+1, j, s, visitats);
            visitats.erase(make_pair(i+1, j));
        }

        s.pop_back(); 
    }

    if (j > 0){
        s.push_back(board.getCasella(i, j-1));
        
        if ((checkPrefix(s) || checkWord(s)) && visitats.insert(make_pair(i, j-1)).second){
            localSearch(board, i, j-1, s, visitats);
            visitats.erase(make_pair(i, j-1));
        }

        s.pop_back(); 
    }

    if (j < board.getSize() - 1){
        s.push_back(board.getCasella(i, j+1));
        
        if ((checkPrefix(s) || checkWord(s)) && visitats.insert(make_pair(i, j+1)).second){
            localSearch(board, i, j+1, s, visitats);
            visitats.erase(make_pair(i, j+1));
        }

        s.pop_back(); 
    }

}

void Bloom::findWords(Board& board){
    for (int i = 0; i < board.getSize(); ++i){
        for (int j = 0; j < board.getSize(); ++j){

            string pre = "";
            pre.push_back(board.getCasella(i, j));
            
            if (checkPrefix(pre)){
                set<pair<int, int>> visitats;
                visitats.insert(make_pair(i, j));

                localSearch(board, i, j, pre, visitats);
            }
        }
    }
}
