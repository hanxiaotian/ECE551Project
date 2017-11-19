#include "global.h"
#include <string>

using namespace std;

double parse_numint(string & line){
  string id=gettoken(line);
  if(findfunc(id)==-1){
    cerr<<"wrong function name"<<endl;
    exit(0);
  }
  Function * ptr=functionlist[findfunc(id)];
  double step=stod(gettoken(line));
  vector<double> bounds;
  vector<double> loop;
  for(int i=0;i<2*ptr->variablenum();i++){
    string token=gettoken(line);
    if(i%2!=0) bounds.push_back(stod(token)-step/2);
    if(i%2==0){
      bounds.push_back(stod(token)+step/2);
      loop.push_back(*bounds.rbegin());
    }
  }
  double integration=0;
  while(*loop.rbegin()<*bounds.rbegin()){
    loop[0]+=step;
    string str;
    for(size_t i=0;i<loop.size()-1;i++){
      if(loop[i]>bounds[2*i+1]){
	loop[i+1]+=step;
	loop[i]=bounds[2*i];
      }
    }
    for(size_t i=0;i<loop.size();i++) str=str+" "+to_string(loop[i]);
    str="("+id+" "+str+")";
    integration+=parse_evaluate(str);
  }
  return integration*pow(step,loop.size());
}
