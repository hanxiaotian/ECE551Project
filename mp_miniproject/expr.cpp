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
#include "numint.h"
#include "mcint.h"
#include "gradas.h"

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
  string line;                            //store one line of command read from file
  ifstream fin(argv[1],ios::in);
  while(getline(fin, line)){
    string command=gettoken(line);      //get first token from line, which indicate what command should be excuted
    if(command=="define"){
      parse_define(line);
    }
    else if(command=="evaluate"){
      string temp=line;
      cout<<temp<<" = "<<parse_evaluate(line)<<endl;
    }
    else if(command=="numint"){
      cout<<"The rectagular integration is "<<parse_numint(line)<<endl;
    }
    else if(command=="mcint"){
      cout<<"The Monte Carlo Integration is "<<parse_mcint(line)<<endl;
    }
    else if(command=="gradas"){
      cout<<"The maximum Gradient point is ("<<parse_gradas(line)<<")"<<endl;
    }
    else{                             //if first token is not a valid command,there will be error and exit
      cerr<<"no such command"<<endl;
      exit(0);
    }
  }
  fin.close();
  //delete functions which stored in a global vector
  for(auto iter=functionlist.begin();iter!=functionlist.end();iter++){
    delete *iter;
  }
  return EXIT_SUCCESS;
}
