#ifndef __EXPR_H___
#define __EXPR_H___

#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <cmath>
#include "global.h"

using namespace std;

vector<Function*> functionlist; //declear global vector

//virtual class which you write in assignment 81
class Expression{
 public:
  virtual ~Expression(){};
  virtual double evaluate() const=0;
};

//function declearation
Expression* makeExpr(string op,vector<Expression *>& idlist);
bool isValidId(string id);
Expression* parseId(string &strp,Function* fptr=NULL);
Expression* __parse(string &strp,Function* fptr=NULL);
bool is_number(string str);
string gettoken(string &line);
void skipSpace(string & line);
int findfunc(string name);

//variable class, used to store variable in function
//with a string member to store name of the variable and a double member to store value 
class Variable: public Expression{
 private:
  string vname;
  double value;
 public:
 Variable(string n):vname(n),value(0){};
  string name(){return vname;};          //return variable name
  void setvalue(double val){             //set variable value
    value=val;
  };
  virtual ~Variable(){};
  virtual double evaluate() const{       //calculate variable value in syntax tree
    return value;
  };
};

//number class, used to store number
class NumExpression: public Expression{
 private:
  double num;
 public:
 NumExpression(double val):num(val){};
  virtual ~NumExpression(){};
  virtual double evaluate() const{
    return num;
  };
};

//below are some build in computation operator classes
class PlusExpression: public Expression{
 private:
  Expression * lhs;
  Expression * rhs;
 public:
 PlusExpression(Expression *lhs, Expression *rhs):lhs(lhs),rhs(rhs){};
  virtual ~PlusExpression(){
    delete lhs;
    delete rhs;
  };
  virtual double evaluate() const{
    return lhs->evaluate()+rhs->evaluate();
  };
};
class MinusExpression: public Expression{
 private:
  Expression * lhs;
  Expression * rhs;
 public:
 MinusExpression(Expression *lhs, Expression *rhs):lhs(lhs),rhs(rhs){};
  virtual ~MinusExpression(){
    delete lhs;
    delete rhs;
  };
  virtual double evaluate() const{
    return lhs->evaluate()-rhs->evaluate();
  };
};
class TimesExpression: public Expression{
 private:
  Expression * lhs;
  Expression * rhs;
 public:
 TimesExpression(Expression *lhs, Expression *rhs):lhs(lhs),rhs(rhs){};
  virtual ~TimesExpression(){
    delete lhs;
    delete rhs;
  };
  virtual double evaluate() const{
    return lhs->evaluate()*rhs->evaluate();
  };
};
class DivExpression: public Expression{
 private:
  Expression * lhs;
  Expression * rhs;
 public:
 DivExpression(Expression *lhs, Expression *rhs):lhs(lhs),rhs(rhs){};
  virtual ~DivExpression(){
    delete lhs;
    delete rhs;
  };
  virtual double evaluate() const{
    return lhs->evaluate()/rhs->evaluate();
  };
};
class ModExpression: public Expression{
 private:
  Expression * lhs;
  Expression * rhs;
 public:
 ModExpression(Expression *lhs, Expression *rhs):lhs(lhs),rhs(rhs){};
  virtual ~ModExpression(){
    delete lhs;
    delete rhs;
  };
  virtual double evaluate() const{
    return fmod(lhs->evaluate(),rhs->evaluate());
  };
};
class Sin: public Expression{
 private:
  Expression * lhs;
 public:
 Sin(Expression *lhs):lhs(lhs){};
  virtual ~Sin(){
    delete lhs;
  };
  virtual double evaluate() const{
    return sin(lhs->evaluate());
  };
};
class Cos: public Expression{
 private:
  Expression * lhs;
 public:
 Cos(Expression *lhs):lhs(lhs){};
  virtual ~Cos(){
    delete lhs;
  };
  virtual double evaluate() const{
    return cos(lhs->evaluate());
  };
};
class Sqrt: public Expression{
 private:
  Expression * lhs;
 public:
 Sqrt(Expression *lhs):lhs(lhs){};
  virtual ~Sqrt(){
    delete lhs;
  };
  virtual double evaluate() const{
    return sqrt(lhs->evaluate());
  };
};
class Log: public Expression{
 private:
  Expression * lhs;
 public:
 Log(Expression *lhs):lhs(lhs){};
  virtual ~Log(){
    delete lhs;
  };
  virtual double evaluate() const{
    return log(lhs->evaluate());
  };
};
class Pow: public Expression{
 private:
  Expression * lhs;
  Expression * rhs;
 public:
 Pow(Expression *lhs,Expression * rhs):lhs(lhs),rhs(rhs){};
  virtual ~Pow(){
    delete lhs;
  };
  virtual double evaluate() const{
    return pow(lhs->evaluate(),rhs->evaluate());
  };
};


//function class, store function name, variables list and function definition
class Function{
 private:
  string funcname;
  vector<Variable> variables;
  string definition;
 public:
  //friend function declaration
  friend Expression * parseId(string &strp);
  friend Expression * __parse(string &strp);
  //set function name
  void setname(string name){
    funcname=name;
  };
  //store function definition
  void setdefinition(string line){
    definition=line;
  };
  //return function name
  string returnname() const{
    return funcname;
  };
  //check if name already in function's variable list
  bool check_exist(string name){
    for(auto iter=variables.begin();iter<variables.end();iter++){
      if(name==iter->name()) return true;
    }
    return false;
  }
  //add a variable to the function and set its initial value to 0
  void add_variables(string name){
    if(check_exist(name)){         //if variable has alreay exits, print a error message and exits
      cerr<<"repeat variables"<<endl;
      exit(0);
    }
    Variable v(name);
    variables.push_back(v);
  };
  //return the number of variables in this function
  int variablenum(){return variables.size();};
  //set variable value, the argument is the ith variable(decided when function define) and its value
  void setvalue(int num, Expression * value){
    if(num>variablenum()){      //if the order of variable exceed number of variable in list, error and exit
      cerr<<"wrong number of variables"<<endl;
      exit(0);
    }
    variables[num].setvalue(value->evaluate());
  };
  //return the value of variable with sperific name 
  double ReturnVariable(string name){
    if(!check_exist(name)){    //if no such name in variable list, error and exit
      cerr<<"variable name not mathc"<<endl;
      exit(0);
    }
    for(auto iter=variables.begin();iter<variables.end();iter++){
      if(name==iter->name()) return iter->evaluate();
    }
    return 0;
  };
  //produce a syntax tree using definition stored in function and return tree root node
  Expression* parse(){
    string def=this->definition;
    return __parse(def,this);
  };
};


//one of the syntax tree parsing function
Expression * makeExpr(string op,vector<Expression *> & idlist){
  if(op=="+") return new PlusExpression(idlist[0],idlist[1]);
  else if(op== "-") return new MinusExpression(idlist[0],idlist[1]);
  else if(op=="*") return new TimesExpression(idlist[0],idlist[1]);
  else if(op=="/") return new DivExpression(idlist[0],idlist[1]);
  else if(op=="%") return new ModExpression(idlist[0],idlist[1]);
  else if(op=="sin") return new Sin(idlist[0]);
  else if(op=="cos") return new Cos(idlist[0]);
  else if(op=="log") return new Log(idlist[0]);
  else if(op=="pow") return new Pow(idlist[0],idlist[1]);
  else if(op=="sqrt") return new Sqrt(idlist[0]);
  else{
    Function * ptr=functionlist[findfunc(op)];
    for(int i=0;i<ptr->variablenum();i++){
      ptr->setvalue(i,idlist[i]);
    }
    for(auto iter=idlist.begin();iter!=idlist.end();iter++){
      delete *iter;
    }
    Expression * tree=ptr->parse();
    return tree;
  }
}

//judge if id is a valid operator or function 
bool isValidId(string id) {
  string str1="+-*/%";             //single character valid symbol
  string str2="pow log sin cos";   //three characters valid symbol
  string str3="sqrt";              //four characters valid symbol
  if(findfunc(id)!=-1) return true;  //if id in functionlist, it is still valid
  else if(id.size()==1 && str1.find(id)!=string::npos) return true;
  else if(id.size()==3 && str2.find(id)!=string::npos) return true;
  else if(id.size()==4 && str2==id) return true;
  else return false;
}

//next two function can parse a string into expression syntax tree
Expression * parseId(string & strp,Function * fptr) {
  skipSpace(strp);
  string id=gettoken(strp);
  if(!isValidId(id)){
    std::cerr << "Invalid id: "<< id<< "\n";
    return NULL;
  }
  vector<Expression *> idlist;
  if(fptr==NULL && findfunc(id)!=-1) fptr=functionlist[findfunc(id)];
  while(strp.substr(0,1)!=")"){
    idlist.push_back(__parse(strp,fptr));
    skipSpace(strp);
  }
  skipSpace(strp);
  if(strp.substr(0,1)==")"){
    gettoken(strp);
    return makeExpr(id,idlist);
  }
  std::cerr <<"Expected ) but found " << strp << "\n";
  return NULL;
}
//the main interface of series of parsing function, which takes to arguments, one is definition string, the other is function pointer which first parameter belongs to
Expression * __parse(string & strp,Function * fptr){
  skipSpace(strp);
  if(strp.empty()){
    std::cerr << "End of line found mid expression!\n";
    return NULL;
  }
  string id=gettoken(strp);
  if(id=="("){
    return parseId(strp,fptr);
  }
  else{
    if(is_number(id)) return new NumExpression(stod(id));
    else if(fptr->check_exist(id)) return new NumExpression(fptr->ReturnVariable(id));
    else{
      cerr<<"invalid id"<<endl;
      exit(0);
    }
  }
}

//judge whether a string is a number
bool is_number(string str){
  stringstream sin(str);
  double d;
  char c;
  if(!(sin >> d)){
    return false;
  }
  if (sin >> c){
    return false;
  }
  return true;
}

//return first token from line
string gettoken(string & line){
  string str="+*/%() ";         //some basic operators "+*/%" and seperator "()" and " "
  string returnstr;
  skipSpace(line);
  if(str.find(*line.begin())!=string::npos){ //when encounter above symbols, return directly
    returnstr=*line.begin();
    line=line.substr(1);
    return returnstr;
  }
  else{
    while(str.find(*line.begin())==string::npos && line.begin()!=line.end()){ //read charator by character, until
      returnstr=returnstr+*line.begin();                                     //encounter " " or "()", return
      line=line.substr(1);
    }
    skipSpace(line);
    return returnstr;
  }
}

//remove white space at both ends of the string
void skipSpace(string & line) {
  while(!line.empty() && isspace(*line.begin()))
    line.erase(line.begin());
  while(!line.empty() && isspace(*line.rbegin()))
    line.erase(--((line.rbegin()).base()));
}

//find function in function list. if exists, return its order in funtionlist. else return -1
int findfunc(string name){
  for(size_t i=0;i<functionlist.size();i++){
    if(functionlist[i]->returnname()==name) return i;
  }
  return -1;
}

//parsing define command line
void parse_define(string &line){
  Function *func=new Function();    //create a new function object
  skipSpace(line);
  cout<<"defined ";                 //output
  if(line.empty()){                 //if command is invalid, error and exit
    cerr<<"wrong command line"<<endl;
    exit(0);
  }
  string format=line.substr(0, line.find("="));   //split line into two part based on "=", the first
  string definition=line.substr(line.find("=")+1);// part store format of the function and second part store
  cout<<format<<endl;                             // function's definition
  gettoken(format);                               //jump through "("
  func->setname(gettoken(format));                //the first token behind "(" is function name
  for(string token=gettoken(format);token!=")";token=gettoken(format)){
    func->add_variables(token);                   //the next several tokens are variable
  }
  func->setdefinition(definition);                //store function definition 
  functionlist.push_back(func);                   //add this function to funtionlist
}

//parsing evaluate command line and calculate the result of the function, return it
double parse_evaluate(string &line){
  skipSpace(line);
  if(line.empty()){         //if invalid command, error and exit
    cerr<<"wrong command line"<<endl;
    exit(0);
  }
  Expression * tree=__parse(line);   //store tree returnd by __parse function 
  double result=tree->evaluate();    //store value of the expression
  delete tree;
  return result;
}

#endif
