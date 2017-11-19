#include <iostream>
#include "expr2.h"
#include <ctype.h>
#include <cstdlib>
#include <string.h>
#include <algorithm>
#include <string>
#include <sstream>
#include <fstream>
#include "global.h"
#include "numint.h"

using namespace std;

//function declaration
string gettoken(string &line);
void parse_define(string & line);
double parse_evaluate(string & line);
bool is_define(string & line);
double parse_numint(string & line);

//the main part of parse a string
int main(int argc, char** argv) {
  if(argc!=2){
    cerr<<"wrong number of argument"<<endl;
    exit(0);
  }
  string line;
  ifstream fin(argv[1],ios::in);
  while(getline(fin, line)){
    string command=gettoken(line);
    if(command=="define"){
      parse_define(line);
    }
    else if(command=="evaluate"){
      string temp=line;
      cout<<temp<<" = "<<parse_evaluate(line)<<endl;
    }
    else if(command=="numint"){
      cout<<"The integration is "<<parse_numint(line)<<endl;
    }
    else{
      cerr<<"no such command"<<endl;
      exit(0);
    }
  }
  fin.close();
  //delete functions
  for(auto iter=functionlist.begin();iter!=functionlist.end();iter++){
    delete *iter;
  }
  return EXIT_SUCCESS;
}
