#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "outname.h"

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  char * b=malloc((strlen(inputName)+8)*sizeof(char));
  strcpy(b,inputName);
  strcat(b,".counts");
  return b;
}
