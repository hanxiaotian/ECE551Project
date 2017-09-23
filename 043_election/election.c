#include "election.h"
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
//include any other headers you need here...

state_t parseLine(const char * line) {
  //STEP 1: write me
  if(strlen(line)==0){
    fprintf(stderr,"invalid input");
    exit(EXIT_FAILURE);
  }
  char * line1=malloc(strlen(line)*sizeof(char)+1);
  strcpy(line1,line);
  state_t state;
  strcpy(state.name,strtok(line1,":"));
  for(int i=0;state.name[i]!='\0';i++){
    if(!isalpha(state.name[i])&&(state.name[i]!=' ')){
      fprintf(stderr,"invalid state name");
      exit(EXIT_FAILURE);
    }
  }
  char * ptr;
  state.population=strtoul(strtok(NULL,":"),&ptr,10);
  if(state.population<=0){
    fprintf(stderr,"invalid state population");
    exit(EXIT_FAILURE);
  }
  state.electoralVotes=strtoul(strtok(NULL,":"),&ptr,10);
  if(state.electoralVotes<=0){
    fprintf(stderr,"invalid state electoralVotes");
    exit(EXIT_FAILURE);
  }
  free(line1);
  return state;
}
unsigned int countElectoralVotes(state_t * stateData, 
				 uint64_t * voteCounts, 
				 size_t nStates) {
  //STEP 2: write me
  unsigned int count=0;
  for(int i=0;i<nStates;i++){
    if(voteCounts[i]*1.0/stateData[i].population>0.5){
      count+=stateData[i].electoralVotes;
    }
  }
  return count;
}

void printRecounts(state_t * stateData, 
		   uint64_t * voteCounts, 
		   size_t nStates) {
  //STEP 3: write me
}
void printLargestWin(state_t * stateData, 
		     uint64_t * voteCounts, 
		     size_t nStates) {
  //STEP 4: write me
}
