#include <iostream>
#include <cstdlib>
#include "bstset.h"
#include "set.h"
#include <string>

using namespace std;

int main(){
  BstSet<int> map;
  map.add(2);		   
  map.add(4);
  map.add(1);
  map.add(7);
  map.add(3);
  map.add(9);
  map.add(-1);
  map.add(88);
  map.add(17);
  map.add(-23);
  map.add(16);
  map.add(44);
  map.add(77);
  map.add(4);
  map.remove(2);
  map.remove(16);
  map.remove(-1);
  cout<<map.contains(4)<<endl;
  cout<<map.contains(14)<<endl;
  map.print();
  cout<<endl;
  BstSet<int> map2(map);
  map2.remove(88);
  map2.print();
  cout<<endl;
  BstSet<int> map3(map);
  map3.print();
  cout<<endl;
  map3=map2;
  map3.print();
  return EXIT_SUCCESS;
}
