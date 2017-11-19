#include "global.h"
#include <string>

using namespace std;

double parse_mcint(string & line){
  string id=gettoken(line);
  if(findfunc(id)==-1){
    cerr<<"wrong function name"<<endl;
    exit(0);
  }
  Function * ptr=functionlist[findfunc(id)];
  int N=stoi(gettoken(line));
  vector<double> bounds;
  for(int i=0;i<2*ptr->variablenum();i++){
    bounds.push_back(stod(gettoken(line)));
  }
  double integration=0;
  for(int i=0;i<N;i++){
    
    for(size_t j=0;j<loop.size();j++) str=str+" "+to_string(loop[i]);
    str="("+id+" "+str+")";
    integration+=parse_evaluate(str);
  }
}
