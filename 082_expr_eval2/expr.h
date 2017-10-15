#ifndef __EXPR_H___
#define __EXPR_H___

#include <string>
#include <iostream>
#include <cstdlib>
#include <sstream>

class Expression{
 public:
  virtual std::string toString() const=0;
  virtual ~Expression(){};
};

class NumExpression: public Expression{
 private:
  long int num;
 public:
 NumExpression(long int val):num(val){};
  virtual std::string toString() const{
    std::stringstream ss;
    ss<<num;
    return ss.str();
  };
  virtual ~NumExpression(){};
};

class PlusExpression: public Expression{
 private:
  Expression * lhs;
  Expression * rhs;
 public:
 PlusExpression(Expression *lhs, Expression *rhs):lhs(lhs),rhs(rhs){};
  virtual std::string toString() const{
    return "("+lhs->toString()+" + "+rhs->toString()+")";
  };
  virtual ~PlusExpression(){
    delete lhs;
    delete rhs;
  };
};

class MinusExpression: public Expression{
 private:
  Expression * lhs;
  Expression * rhs;
 public:
 MinusExpression(Expression *lhs, Expression *rhs):lhs(lhs),rhs(rhs){};
  virtual std::string toString() const{
    return "("+lhs->toString()+" - "+rhs->toString()+")";
  };
  virtual ~MinusExpression(){
    delete lhs;
    delete rhs;
  };
};

class TimesExpression: public Expression{
 private:
  Expression * lhs;
  Expression * rhs;
 public:
 TimesExpression(Expression *lhs, Expression *rhs):lhs(lhs),rhs(rhs){};
  virtual std::string toString() const{
    return "("+lhs->toString()+" * "+rhs->toString()+")";
  };
  virtual ~TimesExpression(){
    delete lhs;
    delete rhs;
  };
};

class DivExpression: public Expression{
 private:
  Expression * lhs;
  Expression * rhs;
 public:
 DivExpression(Expression *lhs, Expression *rhs):lhs(lhs),rhs(rhs){};
  virtual std::string toString() const{
    return "("+lhs->toString()+" / "+rhs->toString()+")";
  };
  virtual ~DivExpression(){
    delete lhs;
    delete rhs;
  };
};

#endif
