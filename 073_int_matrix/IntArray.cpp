#include "IntArray.h"
#include <cassert>
#include <ostream>

IntArray::IntArray():data(NULL),numElements(0) {}

IntArray::IntArray(int n):data(new int[n]()),numElements(n) {}

IntArray::IntArray(const IntArray & rhs):data(new int[rhs.numElements]()),numElements(rhs.numElements)  {
  for(int i=0;i<rhs.numElements;i++){
    data[i]=rhs.data[i];
  }
  if(numElements==0){
    delete[] data;
    data=NULL;
  }
}

IntArray::~IntArray() {
  delete[] data;
}

IntArray & IntArray::operator=(const IntArray & rhs) {
  if(this!=&rhs){
    delete[] data;
    data=new int[rhs.numElements]();
    for(int i=0;i<rhs.numElements;i++){
      data[i]=rhs.data[i];
    }
    numElements=rhs.numElements;
    if(numElements==0){
      delete[] data;
      data=NULL;
    }
  }
  return *this;
}

const int & IntArray::operator[](int index) const {
  assert((index<numElements)&&(index>=0));
  assert(numElements!=0);
  return data[index];
}
int & IntArray::operator[](int index) {
  assert((index<numElements)&&(index>=0));
  assert(numElements!=0);
  return data[index];
}

int IntArray::size() const {
  return numElements;
}

bool IntArray::operator==(const IntArray & rhs) const {
  if(numElements!=rhs.numElements) return false;
  for(int i=0;i<numElements;i++){
    if(data[i]!=rhs.data[i]) return false;
  }
  return true;
}

bool IntArray::operator!=(const IntArray & rhs) const {
  return !(*this==rhs);
}

std::ostream & operator<<(std::ostream & s, const IntArray & rhs) {
  s<<"{";
  if(rhs.numElements>0){
    for(int i=0;i<rhs.numElements-1;i++){
    s<<rhs.data[i]<<", ";
    }
    s<<rhs.data[rhs.numElements-1];
  }
  s<<"}";
  return s;
}
