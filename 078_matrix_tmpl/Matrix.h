#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

template<typename T>
class Matrix {
 private:
  int numRows;
  int numColumns;
  vector<vector<T> > mat;
 public:
 Matrix():numRows(0),numColumns(0){};
 Matrix(int r, int c):numRows(r),numColumns(c),mat(r,vector<T>(c)){};
 Matrix(const Matrix & rhs):numRows(rhs.numRows),numColumns(rhs.numColumns),mat(rhs.mat){};
 ~Matrix(){};
 Matrix & operator=(const Matrix & rhs){
   if(this!=&rhs){
     numRows=rhs.numRows;
     numColumns=rhs.numColumns;
     mat=rhs.mat;
   }
   return *this;
 };
 int getRows() const{return numRows;};
 int getColumns() const{return numColumns;};
 bool operator==(const Matrix & rhs) const{
   return mat==rhs.mat;
 };
 const vector<T> & operator[](int index) const{
   assert(numRows!=0);
   assert(numColumns!=0);
   assert(index>=0);
   assert(index<numRows);
   return mat[index];
 };
 vector<T> & operator[](int index){
   assert(numRows!=0);
   assert(numColumns!=0);
   assert(index>=0);
   assert(index<numRows);
   return mat[index];
 };
 Matrix operator+(const Matrix & rhs) const{
   assert(numRows==rhs.numRows);
   assert(numColumns==rhs.numColumns);
   Matrix result(numRows,numColumns);
   for(int i=0;i<numRows;i++){
     for(int j=0;j<numColumns;j++){
       result.mat[i][j]=mat[i][j]+rhs.mat[i][j];
     }
   }
   return result;
 };
 friend std::ostream & operator<<(std::ostream & s, const Matrix & rhs){
   s<<"[ ";
   for(int i=0;i<rhs.numRows;i++){
     s<<"{";
     for(int j=0;j<rhs.numColumns;j++){
       s<<rhs.mat[i][j];
       if(j!=rhs.numColumns-1){
	 s<<", ";
       }
     }
     s<<"}";
     if(i!=rhs.numRows-1){
       s<<",\n";
     }
   }
   s<<" ]";
   return s;
 };

};



#endif
