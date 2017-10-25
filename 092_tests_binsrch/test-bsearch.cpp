#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include "function.h"

using namespace std;

class CountedIntFn : public Function<int,int>{
protected:
  unsigned remaining;
  Function<int,int> * f;
  const char * mesg;
public:
  CountedIntFn(unsigned n, Function<int,int> * fn, const char * m): remaining(n),f(fn),mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr,"Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
};

class SinFunction : public Function<int, int> {
public:
  virtual int invoke(int arg) {
    return 10000000 * (sin(arg/100000.0) - 0.5);
  }
};

class XFunction : public Function<int, int> {
public:
  virtual int invoke(int arg) {
    return arg;
  }
};

int binarySearchForZero(Function<int, int> * f, int low, int high);

void check(Function<int,int> * f,int low,int high,int expected_ans,const char * mesg){
  CountedIntFn *cif=new CountedIntFn(log2(high-low)+1,f,mesg);
  if(binarySearchForZero(cif,low,high)!=expected_ans){
    fprintf(stderr,"Wrong Answer in %s\n", mesg);
    exit(EXIT_FAILURE);
  }
  delete cif;
}

int main(){
  SinFunction *mysin=new SinFunction;
  XFunction *myx=new XFunction;
  check(mysin,0,150000,52359,"the range [0,150000)");
  check(mysin,0,52358,52357,"the range [0,52358)");
  check(mysin,52360,150000,52360,"the range [52360,150000)");
  check(mysin,150000,150000,150000,"the range [150000,150000)");
  check(mysin,52359,52359,52359,"the range [52359,52359)");
  check(mysin,0,52359,52358,"the range [0,52359)");
  check(mysin,52359,150000,52359,"the range [52359,150000)");
  check(mysin,0,0,0,"the range [0,0)");
  check(mysin,52358,150000,52359,"the range [52358,150000)");
  check(mysin,0,52360,52359,"the range [0,52360)");
  check(myx,-1000000,1000007,0,"the range [-1,0)");
  check(myx,-1,1000007,0,"the range [-1,1000070)");
  delete mysin;
  delete myx;
  return EXIT_SUCCESS;
}
