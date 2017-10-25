#ifndef __SEARCH__
#define __SEARCH__

int binarySearchForZero(Function<int, int> * f, int low, int high);

int binarySearchForZero(Function<int, int> * f, int low, int high){
  if(low==high || high-low==1) return low;
  int mid=(low+high)/2;
  int midvalue=f->invoke(mid);
  if(midvalue<0) return binarySearchForZero(f,mid,high);
  if(midvalue>0) return binarySearchForZero(f,low,mid);
  return mid;
}

#endif
