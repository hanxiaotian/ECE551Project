#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <sys/types.h>
#include <dirent.h>
#include <cstring>
#include <functional>
#include <algorithm>
#include <limits.h>

using namespace std;

class HashTable{
private:
  vector<vector<string> > table;
  hash<string> hasher;
public:
  HashTable(size_t len){table.resize(len);};
  string isintable(string file,unsigned int h){
    string str;
    for(auto iter=table[h].begin();iter!=table[h].end();iter++){
      if(comparefile(*iter,file)){
	str=(*iter);
	return str;
      }
    }
    return str;
  };
  bool comparefile(string file1,string file2){
    string str1=readfile(file1);
    string str2=readfile(file2);
    return str1==str2;
  };
  string readfile(string file){
    ifstream ifs(file,ios::binary | ios::in);
    std::string str((istreambuf_iterator<char>(ifs)),(istreambuf_iterator<char>()));
    ifs.close();
    return str;
  };
  void output(vector<string> &filenames,ostream &shell){
    shell<<"#!/bin/bash"<<endl;
    for(auto iter=filenames.begin();iter!=filenames.end(); iter++){
      string s=readfile(*iter);
      unsigned int h=hasher(s);
      h=h%table.size();
      if(table[h].size()==0){
	table[h].push_back(*iter);
      }
      else{
	string str=isintable(*iter,h);
	if(str.length()!=0){
	  shell<<"#Removing "<<*iter<<" (duplicate of "<<str<<")."<<endl;
	  shell<<"rm "<<*iter<<endl;
	}
	else{
	  table[h].push_back(*iter);
	}
      }
      //      if(*iter=="/var/dedup/d001/acccacab") break;
    }
  };
};

void check_valid(int argc, char* argv[]){
  if(argc<2){
    cerr<<"no directory input!"<<endl;
    exit(1);
  }
}

void read_directory(vector<string> &filenames, string path){
  DIR *dir;
  struct dirent *ptr=NULL;
  if((dir=opendir(path.c_str()))==NULL){
    cout<<path.c_str();
    perror("Open dri error...");
    exit(1);
  }
  while((ptr=readdir(dir))!=NULL){
    if(strcmp(ptr->d_name,".")==0||strcmp(ptr->d_name,"..")==0)
      continue;
    else if(ptr->d_type==DT_REG){
      filenames.push_back(path+'/'+ptr->d_name);
    }
    else if(ptr->d_type==DT_DIR){
      read_directory(filenames,path+'/'+ptr->d_name);
    }
    else continue;
  }
  closedir(dir);
}

int main(int argc, char * argv[]){
  check_valid(argc,argv);
  vector<string> filenames;
  for(int i=1;i<argc;i++){
    char resolved_path[PATH_MAX];
    realpath(argv[i],resolved_path);
    string path=resolved_path;
    read_directory(filenames,path);
  }
  HashTable ht(filenames.size()); 
  ht.output(filenames,cout);
  return EXIT_SUCCESS;
}
