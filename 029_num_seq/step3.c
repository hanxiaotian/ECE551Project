//This file is for Step 3.
//You should do 
//  Step 3 (A): write seq3
//  Step 3 (B): write main to test seq3
//  Step 3 (C): write countEvenInSeq3Range
//  Step 3 (D): add test cases to main to test countEvenInSeq3Range
// 
// Be sure to #include any header files you need!
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int seq3(int x, int y){
  return 6+(x+2)*(y-3);
}

int countEvenInSeq3Range(int xLow, int xHi, int yLow, int yHi){
  int count=0;
  if((xLow<xHi)&&(yLow<yHi)){
    for(int i=xLow;i<xHi;i++){
      for(int j=yLow;j<yHi;j++){
	if(seq3(i,j)%2==0) count++;
      }
    }
  }
  return count;
}


int main(){
  printf("seq3(%d,%d)=%d\n",-4,-5,seq3(-4,-5));
  printf("seq3(%d,%d)=%d\n",8,12,seq3(8,12));
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",0,2,0,3,countEvenInSeq3Range(0,2,0,3));
}
