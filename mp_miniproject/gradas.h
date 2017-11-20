#include "global.h"
#include <string>
#include <iterator>

using namespace std;

string vectostr(vector<double> vec){
  ostringstream oss;
  copy(vec.begin(), vec.end()-1,ostream_iterator<double>(oss, " "));
  oss << vec.back();
  return oss.str();
}

vector<double> gradient(string f, vector<double> point){
  double step=0.005;
  vector<double> grad,up,down;
  for(size_t i=0;i<point.size();i++){
    up=point;
    down=point;
    up[i]+=step;
    down[i]-=step;
    string str1="("+f+" "+vectostr(up)+")";
    string str2="("+f+" "+vectostr(down)+")";
    grad.push_back((parse_evaluate(str1)-parse_evaluate(str2))/(2*step));
  }
  return grad;
}

double distance(vector<double> vec1,vector<double> vec2){
  double sum=0;
  for(size_t i =0;i<vec1.size();i++){
    sum+=pow(vec1[i]-vec2[i],2);
  }
  return sqrt(sum);
}

string parse_gradas(string & line){
  string id=gettoken(line);
  if(findfunc(id)==-1){
    cerr<<"wrong function name"<<endl;
    exit(0);
  }
  Function * ptr=functionlist[findfunc(id)];
  double gamma=stod(gettoken(line));
  double convergedDistance=stod(gettoken(line));
  vector<double> start;
  vector<double> newp;
  for(int i=0;i<ptr->variablenum();i++){
    start.push_back(stod(gettoken(line)));
  }
  int maxStep=stoi(gettoken(line));
  for(int i=0;i<maxStep;i++){
    vector<double> grad=gradient(id,start);
    vector<double> newp;
    for(size_t j=0;j<grad.size();j++){
      newp.push_back(start[j]+gamma*grad[j]);
    }
    if(distance(newp,start)<convergedDistance) return vectostr(newp);
    start=newp;
  }
  return "not converge";
}
