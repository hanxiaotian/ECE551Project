#include <stdio.h>
#include <stdlib.h>

size_t  maxSeq(int * array, size_t n);

size_t ImaxSeq(int * array, size_t n){
  int size=0;
  int count=0;
  if(n==0) return size;
  else{
    for(int i=0;i<n;i++){
      count=1;
      int j=i+1;
      while(j<n){
	if(array[j]>array[j-1]){
	  count++;
	  j++;
	}
	else break;
      }
      if(count>size) size=count;
    }
  }
  return size;
}

void run_helper(int * array, size_t n){
  if(maxSeq(array,n)!=ImaxSeq(array,n)){
    printf("wrong_answer:%lu,right_answer:%lu\n",maxSeq(array,n),ImaxSeq(array,n));
    exit(EXIT_FAILURE);
  }
  printf("test_answer:%lu,right_answer:%lu\n",maxSeq(array,n),ImaxSeq(array,n)\
	 );
}

void run_helper2(int * array, size_t n, size_t ans){
  if(maxSeq(array,n)!=ans){
    printf("wrong_answer:%lu,right_answer:%lu\n",maxSeq(array,n),ans);
    exit(EXIT_FAILURE);
  }
  printf("test_answer:%lu,right_answer:%lu\n",maxSeq(array,n),ans);
}


int main(){
  int array1[5]={1,2,3,5,3};
  int array2[1]={1.0};
  int array3[2]={2,1.9};
  run_helper2(array1,5,4);
  run_helper2(array2,1,1);
  run_helper2(array3,2,1);
  int array4[6]={1,2,3,2,3,4};
  run_helper2(array4,6,3);
  int array5[6]={1,2,3,3,4,5};
  run_helper2(array5,6,3);
  int array6[7]={1,2,3,3,4,5,6};
  run_helper2(array6,7,4);
  int array7[0];
  run_helper2(array7,0,0);
  int array8[]={1,2,1,3,5,7,2,4,6,9};
  run_helper2(array8,10,4);
  int array9[]={1.0,1.0,1.0,1,1};
  run_helper2(array9,5,1);
  int array10=0;
  run_helper2(&array10,1,1);
  //  int array11[]={'1','2',"11",'6'};
  //run_helper2(array11,4,3);
  //int array12[]={'1','2',"71",'6'};
  //run_helper2(array12,5,3);
  int array13[]={0,1};
  run_helper2(array13,5,2);
  return EXIT_SUCCESS;
}
