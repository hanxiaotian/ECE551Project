#include "global.h"
#include <string>
#include <time.h>

using namespace std;

double dRand(double fMin, double fMax)  //this function returns a random number between fMin and fMax
{
  double f=(double)rand()/RAND_MAX;
  return fMin+f*(fMax-fMin);
}

//this function parse monte carlo integration command and return result
double parse_mcint(string & line){
  srand(time(NULL));                   //set random number generator seed 
  string id=gettoken(line);            //get funtion name
  if(findfunc(id)==-1){
    cerr<<"wrong function name"<<endl;
    exit(0);
  }
  Function * ptr=functionlist[findfunc(id)];  //find function in funtion list
  int N=stoi(gettoken(line));          //get the number of simulation
  vector<double> bounds;               //store variable boundary
  for(int i=0;i<2*ptr->variablenum();i++){
    if(line.empty()){
      cerr<<"wrong boundary number"<<endl;
      exit(0);
    }
    bounds.push_back(stod(gettoken(line)));
  }
  if(!line.empty()){
    cerr<<"wrong boundary number"<<endl;
    exit(0);
  }
  double integration=0;    //store result
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
