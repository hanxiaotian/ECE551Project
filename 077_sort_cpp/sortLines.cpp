#include <iostream>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>

using namespace std;

std::ostream & operator<<(std::ostream & s, const std::vector<string> & v) {
  for (size_t i = 0; i < v.size(); i++) {
    s << v[i]<<'\n';
  }
  return s;
}

int screenread(){
  string temp;
  vector<string> myVector;
  while(1){
    getline(cin,temp);
    if(cin.eof()) break;
    myVector.push_back(temp);
  }
  sort(myVector.begin(),myVector.end());
  cout<<myVector;
  return EXIT_SUCCESS;
}

int fileread(const char * filename){
  ifstream infile;
  vector<string> myVector;
  infile.open(filename);
  if(!infile){
    cerr<<"file open error"<<endl;
    perror("file open error");
    exit(EXIT_FAILURE);  
  }
  string str;
  while(1){
    getline(infile,str);
    if(infile.eof()) break;
    myVector.push_back(str);
  }
  infile.close();
  sort(myVector.begin(),myVector.end());
  cout<<myVector;
  return EXIT_SUCCESS;
}

int main(int argc, char **argv){
  if(argc==1){
    screenread();
  }
  else{
    for(int i=1;i<argc;i++){
      fileread(argv[i]);
    }
  }
  return EXIT_SUCCESS;
}
