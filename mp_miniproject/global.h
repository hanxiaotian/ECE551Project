#ifndef __GLOBAL__
#define __GLOBAL__

#include <vector>

using namespace std;

class Function;
extern vector<Function*> functionlist;
//Since once function is defined, it will be stored and should be accessed by every part of the program, for convenient, I use a global vector to store them. 

#endif
