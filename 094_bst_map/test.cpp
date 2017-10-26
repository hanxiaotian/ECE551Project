#include <iostream>
#include <cstdlib>
#include "bstmap.h"
#include "map.h"
#include <string>

using namespace std;

int main(){
  BstMap<int,string> map;
  map.add(5,"a");
  map.add(4,"b");
  map.add(6,"c");
  map.add(3,"x");
  map.remove(5);
  return EXIT_SUCCESS;
}
