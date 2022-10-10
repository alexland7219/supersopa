#include "diccDHashing.hh"
//key = posicio en el vector
DHash::DHash(unsigned int nPrefixes, vector<string>& dicc) {
  
  table.resize(nextprime(dicc.size()*2));
  tablePrefixes.resize(nextprime(nPrefixes*2));

  for (int i = 0; i < table.size(); ++i) table[i] = ".";
  for (int i = 0; i < tablePrefixes.size(); ++i)
    tablePrefixes[i] = ".";
  for (string s : dicc) {
    addWord(s);

    string pre = "";

    for (int i = 0; i < s.size() - 1; ++i){
      pre.push_back(s[i]);
      addPrefix(pre);
    }

  }

}

int DHash::nextprime(unsigned int k){
  // Retorna el primer > k mínim
  bool is_prime = false;
  while (!is_prime){
    ++k;
    is_prime = isPrime(k, 300);
  }

  cout << k << " is a prime number" << endl;
  return k;
}

// Necessari per a la exponenciació modular
unsigned long long mod_pow(unsigned long long base, unsigned long long exponent, unsigned long long modulus)
{
    if (exponent == 0) return 1;
    unsigned long long aux = 1;
    while(exponent > 1) {
        if (exponent % 2 != 0) {
            aux *= base;
            aux %= modulus;
        }
        base *= base;
        base %= modulus;
        exponent /= 2;
    }
    return (base*aux) % modulus;
}

bool DHash::isPrime(unsigned int p, unsigned int tests){
	if ((p % 2 == 0 && p != 2) || p < 2)
		return false;

	if (p == 2) return true;
	
  for (int i = 0; i < 100; ++i){
    unsigned int a = rand()%(p-2);
    a += 2;

    if (p % a == 0) return false;
    else if (mod_pow(a, p-1, p) != 1) return false;

  }
  
  return true;
}

int DHash::hash1(string s){
  //multipliquem per prime
  int hash = 7;
  for (int i = 0; i < s.size(); i++) {
      hash = hash*31 + s[i];
  }
  return hash % table.size();
};


int DHash::hash2(string s) {
    unsigned long hash = 5381;
    int c;

    char * str = &s[0];

    while (c = *str++)
        hash = ((hash << 5) + hash) + c;

    return (hash % tablePrefixes.size()-1) + 1;
}

void DHash::addWord(string& paraula) {
  unsigned int intent = 0;
  unsigned int pri = hash1(paraula);
  unsigned int sec = hash2(paraula);
  unsigned int id = pri;

  while (intent < table.size()) {
    if (table[id] == ".") {
      //espai lliure
      table[id] = paraula;
      break;
    }
    else {
      id = (id + sec) % table.size();
      ++intent;
    }
  }
}

void DHash::addPrefix(string& pre){
  unsigned int intent = 0;
  unsigned int pri = hash1(pre);
  unsigned int sec = hash2(pre);
  unsigned int id = pri;

  while (intent < tablePrefixes.size()) {
    if (tablePrefixes[id] == ".") {
      //espai lliure
      tablePrefixes[id] = pre;
      break;
    }
    else {
      id = (id + sec) % tablePrefixes.size();
      ++intent;
    }
}

}



bool DHash::checkWord(string& word){
  int intent = 0;

  int pri = hash1(word);
  int sec = hash2(word);
  int id = pri % table.size();

  while (intent < table.size()) {
    if (table[id] == word) return true;
    else if (table[id] == ".") return false;

    else {
      //no està la palabra en la casilla inicial, pero podria estar
      id = (id + sec) % table.size();
      ++intent;
    }
  }

  return false;
}

bool DHash::checkPrefix(string& word){
  int intent = 0;

  int pri = hash1(word);
  int sec = hash2(word);
  int id = pri % tablePrefixes.size();

  while (intent < tablePrefixes.size()) {
    if (tablePrefixes[id] == word) return true;
    else if (tablePrefixes[id] == ".") return false;

    else {
      //no està la palabra en la casilla inicial, pero podria estar
      id = (id + sec) % tablePrefixes.size();
      ++intent;
    }
  }

  return false;
}


void DHash::localSearch(Board& board, int i, int j, string& s, set<pair<int, int>>& visitats, set<string>& foundWords){
    // Supposing on (i, j) there's a valid prefix and has been marked as visited
    if (checkWord(s)) foundWords.insert(s);

    if (i > 0 && j > 0){
        s.push_back(board.getCasella(i-1, j-1));
        
        if ((checkPrefix(s) || checkWord(s)) && visitats.insert(make_pair(i-1, j-1)).second){
            localSearch(board, i-1, j-1, s, visitats, foundWords);
            visitats.erase(make_pair(i-1, j-1));
        }

        s.pop_back(); 
    }

    if (i > 0 && j < board.getSize() - 1){
        s.push_back(board.getCasella(i-1, j+1));
        
        if ((checkPrefix(s) || checkWord(s)) && visitats.insert(make_pair(i-1, j+1)).second){
            localSearch(board, i-1, j+1, s, visitats, foundWords);
             visitats.erase(make_pair(i-1, j+1));
        }

        s.pop_back();
    }

    if (i < board.getSize() - 1 && j > 0){
        s.push_back(board.getCasella(i+1, j-1));
        
        if ((checkPrefix(s) || checkWord(s)) && visitats.insert(make_pair(i+1, j-1)).second){
            localSearch(board, i+1, j-1, s, visitats, foundWords);
            visitats.erase(make_pair(i+1, j-1));
        }

        s.pop_back(); 
    }

    if (i < board.getSize() - 1 && j < board.getSize() - 1){
        s.push_back(board.getCasella(i+1, j+1));
        
        if ((checkPrefix(s) || checkWord(s)) && visitats.insert(make_pair(i+1, j+1)).second){
            localSearch(board, i+1, j+1, s, visitats, foundWords);
            visitats.erase(make_pair(i+1, j+1));
        }

        s.pop_back(); 
    }

    if (i > 0){
        s.push_back(board.getCasella(i-1, j));
        
        if ((checkPrefix(s) || checkWord(s)) && visitats.insert(make_pair(i-1, j)).second){
            localSearch(board, i-1, j, s, visitats, foundWords);
            visitats.erase(make_pair(i-1, j));
        }

        s.pop_back(); 
    }

    if (i < board.getSize() - 1){
        s.push_back(board.getCasella(i+1, j));
        
        if ((checkPrefix(s) || checkWord(s)) && visitats.insert(make_pair(i+1, j)).second){
            localSearch(board, i+1, j, s, visitats, foundWords);
            visitats.erase(make_pair(i+1, j));
        }

        s.pop_back(); 
    }

    if (j > 0){
        s.push_back(board.getCasella(i, j-1));
        
        if ((checkPrefix(s) || checkWord(s)) && visitats.insert(make_pair(i, j-1)).second){
            localSearch(board, i, j-1, s, visitats, foundWords);
            visitats.erase(make_pair(i, j-1));
        }

        s.pop_back(); 
    }

    if (j < board.getSize() - 1){
        s.push_back(board.getCasella(i, j+1));
        
        if ((checkPrefix(s) || checkWord(s)) && visitats.insert(make_pair(i, j+1)).second){
            localSearch(board, i, j+1, s, visitats, foundWords);
            visitats.erase(make_pair(i, j+1));
        }

        s.pop_back(); 
    }

}





void DHash::findWords(Board& board, set<string>& foundWords){
    for (int i = 0; i < board.getSize(); ++i){
        for (int j = 0; j < board.getSize(); ++j){

            string pre = "";
            pre.push_back(board.getCasella(i, j));
            
            if (checkPrefix(pre)){
                set<pair<int, int>> visitats;
                visitats.insert(make_pair(i, j));

                localSearch(board, i, j, pre, visitats, foundWords);
            }
        }
    }
}
