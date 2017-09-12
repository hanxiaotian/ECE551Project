#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int  arrayMax(int * array, int n) {
  int flag1=0;
  int max1;
  if(n==0)
    return 0;
  else{
    max1=array[0];
    for(int i=0;i<n;i++){
      if(array[i]>max1){
	max1=array[i];
	flag1=i;
      }
    }
  }
  int flag2=0;
  int max2;
  max2=array[n-1];
  for(int i=n-1;i>=0;i--){
    if(array[i]>max1){
      max2=array[i];
      flag2=i;
    }
  }
  if(flag1==flag2) return flag1;
  else {
    fprintf(stderr,"Cannot break\n");
    return EXIT_FAILURE;
  }
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

