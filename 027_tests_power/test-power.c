#include <stdio.h>
#include <stdlib.h>

unsigned int power (unsigned int x, unsigned int y);

unsigned int ipow(unsigned  int base, unsigned  int exp )
{
  unsigned int result = 1;
  while( exp )
    {
      if ( exp & 1 )
	{
	  result *= base;
	}
      exp >>= 1;
      base *= base;
    }
  return result;
}

void run_helper(unsigned int x, unsigned int y){
  if(power(x,y)!= ipow(x,y)){
    printf("x:%d,y:%d,wrong_answer:%d,right_answer:%d\n",x,y,power(x,y),ipow(x,y));
    exit(EXIT_FAILURE);
  }
  printf("x:%d,y:%d,wrong_answer:%d,right_answer:%d\n",x,y,power(x,y),ipow(x,\
									   y));
}

int main(){
  run_helper(1,2);
  run_helper(-1,2);
  run_helper('a',2);
  // run_helper(-1,-2);
  // run_helper(1,-2);
  //  run_helper(1,'b');
  //  run_helper('a','b');
  run_helper(0,0);
  run_helper(1,0);
  run_helper(1.0,0);
  run_helper(0.5,0);
  run_helper(222222222222222,2);
  //  run_helper('avb',1);
  // run_helper(1,'adc');
  // run_helper('adv','rty');
  return EXIT_SUCCESS;
}
