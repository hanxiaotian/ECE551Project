#include "global.h"
#include <string>

using namespace std;

//this function parse the command of numerical integration
double parse_numint(string & line){
  string id=gettoken(line);      //get first token from numint command
  if(findfunc(id)==-1){
    cerr<<"wrong function name"<<endl;
    exit(0);
  }
  Function * ptr=functionlist[findfunc(id)];
  double step=stod(gettoken(line));  //get the second argument, step
  vector<double> bounds;            //this vector used to store variable boundary read from command
  vector<double> loop;              //this vector used to store lower bound of every variable 
  for(int i=0;i<2*ptr->variablenum();i++){ //this loop read argument of variable boundary
    if(line.empty()){
      cerr<<"wrong boundary number"<<endl;
      exit(0);
    }
    string token=gettoken(line);
    if(i%2!=0) bounds.push_back(stod(token)-step/2);
    if(i%2==0){
      bounds.push_back(stod(token)+step/2);
      loop.push_back(*bounds.rbegin());
    }
  }
  if(!line.empty()){
    cerr<<"wrong boundary number"<<endl;
    exit(0);
  }
  double integration=0;             //store result
  //in this loop, because we donnot know the number of variables before command, we cannot just write nested loop,I use a vetor to simulate a counter, specifically, when a variabe reaches its upper bound, another variable increase a step and the variable turn into its lower bound again
  while(*loop.rbegin()<*bounds.rbegin()){
    loop[0]+=step;                  
    string str;
    for(size_t i=0;i<loop.size()-1;i++){
      if(loop[i]>bounds[2*i+1]){
	loop[i+1]+=step;
	loop[i]=bounds[2*i];
      }
      else break;
    }
    for(size_t i=0;i<loop.size();i++) str=str+" "+to_string(loop[i]); //here we calculate function value
    str="("+id+" "+str+")";
    integration+=parse_evaluate(str);
  }
  return integration*pow(step,loop.size());
}
