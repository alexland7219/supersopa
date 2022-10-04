#ifndef DICCDHASHING_HH
#define DICCDHASHING_HH

#include <string>
#include <list>




class DHash {

    private:
    int capacity;
    list<string> *table


    static int hash1(string s);

    //solver de les colisions de hash1
    static int hash2(string s);

    public:

    DHash(int tamany);

    void afegeix(string paraula);
    bool comprova(string paraula);
};

#endif
