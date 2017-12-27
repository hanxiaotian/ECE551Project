#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"

int strsplit(char* temp,char** key,char** value){
  char p[strlen(temp)];
  strcpy(p,temp);
  int i=0;
  while(p[i]!='='){
    i++;
  }
  p[i]='\0';
  char *q=&p[i+1];
  *key=malloc((i+1)*sizeof(char));
  memset(*key,0,(i+1)*sizeof(char));
  *value=malloc((strlen(temp)-i-1)*sizeof(char));
  memset(*value,0,(strlen(temp)-i-1)*sizeof(char));
  strcpy(*key,p);
  strncpy(*value,q,strlen(q)-1);
  return EXIT_SUCCESS;
}

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE * f=fopen(fname,"r");
  kvarray_t * pairs=malloc(sizeof(kvarray_t));
  pairs->array=NULL;
  pairs->length=0;
  size_t stringlength=0;
  char * temp=NULL;
  while(!feof(f)){
    getline(&temp,&stringlength,f);
    if(feof(f)) break;
    (pairs->length)++;
    pairs->array=realloc(pairs->array,pairs->length*sizeof(kvpair_t *));
    pairs->array[pairs->length-1]=malloc(sizeof(kvpair_t));
    strsplit(temp,&(pairs->array[pairs->length-1]->key),&(pairs->array[pairs->length-1]->value));
  }
  free(temp);
  fclose(f);
  return pairs;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  for(int i=0;i<pairs->length;i++){
    free(pairs->array[i]->key);
    free(pairs->array[i]->value);
    free(pairs->array[i]);
  }
  free(pairs->array);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for(int i=0;i<pairs->length;i++){
    printf("key = '%s' value = '%s'\n",pairs->array[i]->key,pairs->array[i]->value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  for(int i=0;i<pairs->length;i++){
    if(strcmp(key,pairs->array[i]->key)==0) return pairs->array[i]->value;
  }
  return NULL;
}
