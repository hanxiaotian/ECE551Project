#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"
counts_t * createCounts(void) {
  //WRITE ME
  counts_t * count=malloc(sizeof(counts_t));
  count->item=NULL;
  count->length=0;
  return count;
}

void addCount(counts_t * c, const char * name) {
  //WRITE ME
  int flag=0;
  if(name==NULL){
    for(int i=0;i<c->length;i++){
      if(c->item[i]->str==NULL){
	c->item[i]->times++;
	flag=1;
      }
    }
    if(flag==0){
      c->length++;
      c->item=realloc(c->item,c->length*sizeof(*(c->item)));
      c->item[c->length-1]=malloc(sizeof(one_count_t));
      c->item[c->length-1]->str=NULL;
      c->item[c->length-1]->times=1;
    }
  }
  else{
    for(int i=0;i<c->length;i++){
      if(c->item[i]->str==NULL) continue;
      if(strcmp(c->item[i]->str,name)==0){
	c->item[i]->times++;
	flag=1;
      }
    }
    if(flag==0){
      c->length++;
      c->item=realloc(c->item,c->length*sizeof(*(c->item)));
      c->item[c->length-1]=malloc(sizeof(one_count_t));
      c->item[c->length-1]->str=malloc((strlen(name)+1)*sizeof(char));
      strcpy(c->item[c->length-1]->str,name);
      c->item[c->length-1]->times=1;
    }
  }
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  int flag=-1;
  for(int i=0;i<c->length;i++){
    if(c->item[i]->str==NULL){
      flag=i;
      continue;
    }
    fprintf(outFile,"%s: %d\n",c->item[i]->str,c->item[i]->times);
  }
  if((flag!=-1)&&(c->item[flag]->times!=0)) fprintf(outFile,"<unknown> : %d\n",c->item[flag]->times);
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for(int i=0;i<c->length;i++){
    if(c->item[i]->str!=NULL) free(c->item[i]->str);
    free(c->item[i]);
  }
  free(c->item);
  free(c);
}
