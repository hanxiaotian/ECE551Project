#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int  arrayMax(int * array, int n) {
  int flag1=0;
  int max1;
  max1=array[0];
  for(int i=0;i<n;i++){
    if(array[i]>max1){
      max1=array[i];
      flag1=i;
    }
  }
  for(int i=0;i<n;i++){
    if(array[i]==max1&&i!=flag1) return EXIT_FAILURE;
  }
    return flag1;
}

void frequencycount(FILE *f,int alphabet[]){
  int c;
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      c = tolower(c);
      alphabet[c-'a']++;
    }
  }  
}

void decrypt(FILE * f){
  int alphabet[26]={0};
  frequencycount(f,alphabet);
  int shifting=arrayMax(alphabet,26)+'a'-'e';
  printf("%d\n",shifting);
  
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr,"Usage: encrypt key inputFileName\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
}
  decrypt(f);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

