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
  cout<<map.lookup(4)<<endl;
  map.remove(5);
  try{
    cout<<map.lookup(4)<<endl;
  }
  catch(invalid_argument & ia){
    cerr<<ia.what()<<endl;
    exit(0);
  }
  return EXIT_SUCCESS;
}
