#include "diccDHashing.hh"
//key = posicio en el vector
DHash::DHash(int c, vector<string> paraules) {
  this->capacity = c;
  table = new vector<string>[capacity];
  for (int i = 0; i < capacity; ++i) table[i] = ".";
  for (string s : paraules) {
    //prefix
  }

}



int DHash::hash1(string s){
  //multipliquem per prime
  int hash = 7;
  for (int i = 0; i < strlen; i++) {
      hash = hash*31 + charAt(i);
  }
  return hash;
};


int DHash::hash2(string s) {
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c;

    return hash;
}

void DHash::afegeix(string paraula) {
  int intent = 0;
  bool empty = false;
  int pri = hash1(paraula);
  int sec = hash2(paraula);
  int id = pri % this->capacity;
  while (!empty && intent < dicc.size()) {
    if (table[id] != ".") {
      //espai lliure
      table[id] = paraula;
      empty = true;
    }
    else {
      id = (id + sec) % this->capacity;
      ++intent;
    }
  }
  //intent potencialment = capacity

}




void DHash::comprova(string prefix_complet, set<string>& found){
  int intent = 0;
  bool trobat = false;
  int pri = hash1(paraula);
  int sec = hash2(paraula);
  int id = pri % this->capacity;
  while (!trobat && intent < dicc.size()) {
    if (vector[id] == prefix_complet) {
      trobat = true;
      found.insert(prefix_complet);
    }
    else if (vector[id] == ".") {
      //hem arribat a un final
      break;
    }
    else {
      //no està la palabra en la casilla inicial, pero podria estar
      id = (id + sec) % this->capacity;
      ++intent;
    }
  }


}
