#include <stddef.h>

size_t maxSeq(int * array, size_t n){
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
