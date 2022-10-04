#include "diccDHashing.hh"
//key = posicio en la llista
DHash::DHash(int c) {
  this->capacity = c;
  table = new list<string>[capacity];
  //list<string>::iterator it = table.begin();

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

bool DHash::afegeix(string paraula) {
  int intent = 0;
  bool empty = false;
  int pri = hash1(paraula);
  int sec = hash2(paraula);
  while (!empty && intent < dicc.size()) {
    if
  }

}




bool DHash::comprova(string paraula){
  int intent = 0;
  bool empty = false;

  while (!empty && intent < dicc.size()) {

  }


}
