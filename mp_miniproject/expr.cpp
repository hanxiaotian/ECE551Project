#include <iostream>
#include "expr.h"
#include <ctype.h>
#include <cstdlib>
#include <string.h>
#include <algorithm>
#include <string>
#include <sstream>
#include <fstream>
#include "global.h"

using namespace std;

//function declaration
void parse_define(string & line);
void parse_evaluate(string & line);
bool is_define(string & line);

//the main part of parse a string
int main(int argc, char** argv) {
  if(argc!=2){
    cerr<<"wrong number of argument"<<endl;
    exit(0);
  }
  string line;
  ifstream fin(argv[1],ios::in);
  while(getline(fin, line)){
    if(is_define(line)){
      parse_define(line);
    }
    else{
      parse_evaluate(line);
    }
  }
  fin.close();
  return EXIT_SUCCESS;
}
