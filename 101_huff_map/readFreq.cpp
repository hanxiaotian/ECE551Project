#include <stdio.h>
#include <cstdlib>
#include "readFreq.h"
#include <fstream>
#include <iostream>

using namespace std;

void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256 ) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  uint64_t *result=new uint64_t[257]();
  ifstream file;
  file.open(fname);
  int c;
  while((c=file.get())!=EOF){
    result[c]++;
  }
  if(c==EOF) result[256]++;
  file.close();
  return result;
}
