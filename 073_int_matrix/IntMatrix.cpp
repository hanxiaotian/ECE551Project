#include "IntMatrix.h"

IntMatrix::IntMatrix():numRows(0), numColumns(0),rows(NULL){
}
IntMatrix::IntMatrix(int r, int c):numRows(r), numColumns(c){
  rows=new IntArray*[r];
  for(int i=0;i<r;i++){
    rows[i]=new IntArray(c);
    for(int j=0;j<c;j++){
      (*rows[i])[j]=0;
    }
  }
}
IntMatrix::IntMatrix(const IntMatrix & rhs)  {
  numRows=rhs.numRows;
  numColumns=rhs.numColumns;
  rows=new IntArray*[numRows];
  for(int i=0;i<numRows;i++){
    rows[i]=new IntArray(numColumns);
    for(int j=0;j<numColumns;j++){
      (*rows[i])[j]=(*rhs.rows[i])[j];
    }
  }
}
IntMatrix::~IntMatrix() {
  for(int i=0;i<numRows;i++){
    delete rows[i];
  }
  delete[] rows;
}
IntMatrix &IntMatrix::operator=(const IntMatrix & rhs) {
  if(this!=&rhs){
    for(int i=0;i<numRows;i++){
      delete rows[i];
    }
    delete[] rows;
    numRows=rhs.numRows;
    numColumns=rhs.numColumns;
    rows=new IntArray*[numRows];
    for(int i=0;i<numRows;i++){
      rows[i]=new IntArray(numColumns);
      for(int j=0;j<numColumns;j++){
	(*rows[i])[j]=(*rhs.rows[i])[j];
      }
    }
  }
  return *this;
}
int IntMatrix::getRows() const {
  return numRows;
}
int IntMatrix::getColumns() const {
  return numColumns;
}
const IntArray & IntMatrix::operator[](int index) const {
  assert(numRows!=0);
  assert(numColumns!=0);
  assert(index>=0);
  assert(index<numRows);
  return *rows[index];
}
IntArray & IntMatrix::operator[](int index){
  assert(numRows!=0);
  assert(numColumns!=0);
  assert(index>=0);
  assert(index<numRows);
  return *rows[index];
}



bool IntMatrix::operator==(const IntMatrix & rhs) const {
  if(numRows!=rhs.numRows||numColumns!=rhs.numColumns) return false;
  for(int i=0;i<numRows;i++){
    for(int j=0;j<numColumns;j++){
      if((*rows[i])[j]!=(*rhs.rows[i])[j]) return false;
    }
  }
  return true;
}

IntMatrix IntMatrix::operator+(const IntMatrix & rhs) const {
  assert(numRows==rhs.numRows);
  assert(numColumns==rhs.numColumns);
  IntMatrix result(numRows,numColumns);
  for(int i=0;i<numRows;i++){
    for(int j=0;j<numColumns;j++){
      ((*result.rows[i])[j])=(*rows[i])[j]+(*rhs.rows[i])[j];
    }
  }
  return result;
}

std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs) {
  s<<"[ ";
  if(rhs.numRows!=0 && rhs.numColumns!=0){
    for(int i=0;i<rhs.numRows-1;i++){
      s<<"{";
      for(int j=0;j<rhs.numColumns-1;j++){
	s<<(*rhs.rows[i])[j]<<", ";
      }
      s<<(*rhs.rows[i])[rhs.numColumns-1];
      s<<"},\n";
    }
    for(int j=0;j<rhs.numColumns-1;j++){
      s<<(*rhs.rows[rhs.numRows-1])[j]<<", ";
    }
    s<<(*rhs.rows[rhs.numRows-1])[rhs.numColumns-1]<<"}";
  }
  s<<" ]";
  return s;
}
