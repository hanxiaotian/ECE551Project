//This file is for Step 2.
//You should do 
//  Step 2 (A): write seq2
//  Step 2 (B): write main to test seq2
//  Step 2 (C): write sumSeq2
//  Step 2 (D): add test cases to main to test sumSeq2
// 
// Be sure to #include any header files you need!
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

int seq2(int x){
  if(x>0){
    //    if(x>sqrt(INT_MAX-x)-1) exit(EXIT_FAILURE);
  }
  else{
    //    if(abs(x)>sqrt(INT_MAX)) exit(EXIT_FAILURE);
  }
  return (x+1)*(x+1)+x;
}

int sumSeq2(int low,int high){
  int sum=0;
  if(low<high){
    for(int i=low;i<high;i++){
      if(sum>INT_MAX-seq2(i)) exit(EXIT_FAILURE);
      sum+=seq2(i);
    }
  }
  return sum;
}


int main(){
  printf("seq2(%d)=%d\n",0,seq2(0));
  printf("seq2(%d)=%d\n",-1,seq2(-1));
  printf("sumSeq2(%d,%d)=%d\n",0,2,sumSeq2(0,2));
  printf("sumSeq2(%d,%d)=%d\n",0,2,sumSeq2(0,2));
  printf("sumSeq2(%d,%d)=%d\n",3,6,sumSeq2(3,6));
  printf("sumSeq2(%d,%d)=%d\n",9,7,sumSeq2(9,7));
}
