#include "global.h"
#include <string>
#include <time.h>

using namespace std;

double dRand(double fMin, double fMax)
{
  double f=(double)rand()/RAND_MAX;
  return fMin+f*(fMax-fMin);
}

double parse_mcint(string & line){
  srand(time(NULL));
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
    string str;
    for(int l=0;l<ptr->variablenum();l++){
      str=str+" "+to_string(dRand(bounds[2*l],bounds[2*l+1]));
    }
    str="("+id+" "+str+")";
    integration+=parse_evaluate(str);
  }
  for(int l=0;l<ptr->variablenum();l++){
    integration*=bounds[2*l+1]-bounds[2*l];
  }
  return integration/N;
}
