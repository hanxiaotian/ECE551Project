#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int readfile(FILE *f,char mat[][10]){
  char vector[11];
  int num=0;
  for(int i=0;i<10;i++){
    num=fread(vector,sizeof(char),11,f);
    if(num!=11){
      fprintf(stderr,"invalid input\n");
      return EXIT_FAILURE;
    }
    if(strchr(vector,'\n')!=&vector[10]){
      fprintf(stderr,"invalid input\n");
      return EXIT_FAILURE;
    }
    for(int j=0;j<10;j++){
      mat[i][j]=vector[j];
    }
  }
  return 0;
}

int rotate(char mat[][10]){
  char temp[10][10];
  for(int i=0;i<10;i++){
    for(int j=0;j<10;j++){
      temp[j][9-i]=mat[i][j];
    }
  }
  for(int i=0;i<10;i++){
    for(int j=0;j<10;j++){
      mat[i][j]=temp[i][j];
    }
  }
  return 0;
}

int printmat(char mat[][10]){
  for(int i=0;i<10;i++){
    for(int j=0;j<10;j++){
      printf("%c",mat[i][j]);
    }
    printf("\n");
  }
  return 0;
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr,"Usage: inputFileName\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  char mat[10][10];
  readfile(f,mat);
  rotate(mat);
  printmat(mat);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
