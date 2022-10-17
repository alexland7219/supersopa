#include "BloomFilter.hh"
using namespace std;

Bloom::Bloom(vector<string>& s, unsigned int nPrefixes, float pFalsePositive){
    // Initializing B and P, MB and MP
    MB = (uint32_t) ceil(s.size()*6. / -log(1.-exp(log(pFalsePositive)/6)));
    MP = (uint32_t) ceil(nPrefixes*6 / -log(1-exp(log(pFalsePositive)/6)));

    B.resize(MB); fill(B.begin(), B.end()-1, false);
    P.resize(MP); fill(P.begin(), P.end()-1, false);

    /*
    h1.open("h1", fstream::out | fstream::trunc); h2.open("h2", fstream::out | fstream::trunc); 
    h3.open("h3", fstream::out | fstream::trunc); h4.open("h4", fstream::out | fstream::trunc); 
    h5.open("h5", fstream::out | fstream::trunc); h6.open("h6", fstream::out | fstream::trunc);
    */

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
    // Fowler-Noll-Vo hash function FNV-1
    uint32_t M;
   
    if (firstModulus) M = MB;
    else M = MP;

    uint64_t hash = 0xcbf29ce484222325;

    for (int i = 0; i < s.size(); ++i){
        hash *= 0x100000001b3;
        hash ^= (uint8_t) s[i];
    }

    return (hash % M);

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
    // SDBM hash function http://www.cse.yorku.ca/~oz/hash.html
    uint32_t M;

    if (firstModulus) M = MB;
    else M = MP;
    
    unsigned int hash = 0;
    unsigned int i    = 0;

    char * str = &s[0];

    for (i = 0; i < s.size(); ++str, ++i)
    {
        hash = (*str) + (hash << 6) + (hash << 16) - hash;
    }

    return (hash % M);
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
    /*
    h1 << hash1(s, true) << endl;
    h2 << hash2(s, true) << endl;
    h3 << hash3(s, true) << endl;
    h4 << hash4(s, true) << endl;
    h5 << hash5(s, true) << endl;
    h6 << hash6(s, true) << endl;
    */
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

void Bloom::localSearch(Board& board, int i, int j, string& s, vector<vector<bool>>& visitats, set<string>& foundWords){
    // Supposing on (i, j) there's a valid prefix and has been marked as visited
    if (checkWord(s)) foundWords.insert(s);

    if (i > 0 && j > 0){
        s.push_back(board.getCasella(i-1, j-1));
        
        if ((checkPrefix(s) || checkWord(s)) && !visitats[i-1][j-1]){
			visitats[i-1][j-1] = true;
            localSearch(board, i-1, j-1, s, visitats, foundWords);
			visitats[i-1][j-1] = false;
        }

        s.pop_back(); 
    }

    if (i > 0 && j < board.getSize() - 1){
        s.push_back(board.getCasella(i-1, j+1));
        
        if ((checkPrefix(s) || checkWord(s)) && !visitats[i-1][j+1]){
			visitats[i-1][j+1] = true;
            localSearch(board, i-1, j+1, s, visitats, foundWords);
            visitats[i-1][j+1] = false;
        }

        s.pop_back();
    }

    if (i < board.getSize() - 1 && j > 0){
        s.push_back(board.getCasella(i+1, j-1));
        
        if ((checkPrefix(s) || checkWord(s)) && !visitats[i+1][j-1]){
			visitats[i+1][j-1] = true;
            localSearch(board, i+1, j-1, s, visitats, foundWords);
            visitats[i+1][j-1] = false;
        }

        s.pop_back(); 
    }

    if (i < board.getSize() - 1 && j < board.getSize() - 1){
        s.push_back(board.getCasella(i+1, j+1));
        
        if ((checkPrefix(s) || checkWord(s)) && !visitats[i+1][j+1]){
			visitats[i+1][j+1] = true;
            localSearch(board, i+1, j+1, s, visitats, foundWords);
            visitats[i+1][j+1] = false;
        }

        s.pop_back(); 
    }

    if (i > 0){
        s.push_back(board.getCasella(i-1, j));
        
        if ((checkPrefix(s) || checkWord(s)) && !visitats[i-1][j]){
            visitats[i-1][j] = true;
            localSearch(board, i-1, j, s, visitats, foundWords);
            visitats[i-1][j] = false;
        }

        s.pop_back(); 
    }

    if (i < board.getSize() - 1){
        s.push_back(board.getCasella(i+1, j));
        
        if ((checkPrefix(s) || checkWord(s)) && !visitats[i+1][j]){
			visitats[i+1][j] = true;
            localSearch(board, i+1, j, s, visitats, foundWords);
            visitats[i+1][j] = false;
        }

        s.pop_back(); 
    }

    if (j > 0){
        s.push_back(board.getCasella(i, j-1));
        
        if ((checkPrefix(s) || checkWord(s)) && !visitats[i][j-1]){
			visitats[i][j-1] = true;
            localSearch(board, i, j-1, s, visitats, foundWords);
            visitats[i][j-1] = false;
        }

        s.pop_back(); 
    }

    if (j < board.getSize() - 1){
        s.push_back(board.getCasella(i, j+1));
        
        if ((checkPrefix(s) || checkWord(s)) && !visitats[i][j+1]){
			visitats[i][j+1] = true;
            localSearch(board, i, j+1, s, visitats, foundWords);
            visitats[i][j+1] = false;
        }

        s.pop_back(); 
    }

}

void Bloom::findWords(Board& board, set<string>& foundWords){
    for (int i = 0; i < board.getSize(); ++i){
        for (int j = 0; j < board.getSize(); ++j){

            string pre = "";
            pre.push_back(board.getCasella(i, j));
            
            if (checkPrefix(pre)){
				vector<vector<bool>> visitats(board.getSize(), vector<bool>(board.getSize(), false));
                visitats[i][j] = true;

                localSearch(board, i, j, pre, visitats, foundWords);
            }
        }
    }
}
