#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  FILE * f=fopen(filename,"r");
  char ** array=NULL;
  size_t arraylength=0;
  char * temp=NULL;
  char * rtemp=NULL;
  size_t stringlength=0;
  while(!feof(f)){
    getline(&temp,&stringlength,f);
    if(feof(f)) break;
    rtemp=realloc(rtemp,strlen(temp)*sizeof(char));
    memset(rtemp,0,strlen(temp)*sizeof(char));
    strncpy(rtemp,temp,strlen(temp)-1);
    (arraylength)++;
    array=realloc(array,arraylength*sizeof(*array));
    array[arraylength-1]=lookupValue(kvPairs,rtemp);
  }
  free(rtemp);
  free(temp);
  counts_t *c=createCounts();
  for(int i =0; i < arraylength; i++) {
    addCount(c,array[i]);
  }
  free(array);
  return c;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
 //read the key/value pairs from the file named by argv[1] (call the result kv)
  if (argc<4) {
    fprintf(stderr,"Wrong input");
    return EXIT_FAILURE;
  }
  kvarray_t * kv=readKVs(argv[1]);
 //count from 2 to argc (call the number you count i)
  for(int i=2;i<argc;i++){
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t * c=countFile(argv[i],kv);

    //compute the output file name from argv[i] (call this outName)
    char * outName=computeOutputFileName(argv[i]);

    //open the file named by outName (call that f)
    FILE * f=fopen(outName,"w");
    //print the counts from c into the FILE f
    printCounts(c,f);
    //close f
    fclose(f);
    //free the memory for outName and c
    freeCounts(c);
    free(outName);
  }


 //free the memory for kv
  freeKVs(kv);
  return EXIT_SUCCESS;
}
