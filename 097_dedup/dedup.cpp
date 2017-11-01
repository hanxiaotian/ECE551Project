#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <list>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <cstring>
#include <functional>
#include <streambuf>
#include <algorithm>
#include <unistd.h>
#include <limits.h>

using namespace std;

class HashTable{
private:
  vector<vector<string> > table;
  hash<string> hasher;
public:
  HashTable(size_t len){table.resize(len);};
  void add(string key,string value){
    unsigned int h=hasher(key);
    h=h%table.size();
    table[h].push_back(value);
  };
  list<pair<string,string> > SimilarPairs(){
    list<pair<string,string> > pairs;
    for(auto it=table.begin();it!=table.end(); it++){
      if((*it).size()>1){
	for(size_t i=0;i<(*it).size()-1;i++){
	  for(size_t j=i+1;j<(*it).size();j++){
	    pair<string,string> p((*it)[i],(*it)[j]);
	    pairs.push_back(p);
	  }
	}
      }
    }
    return pairs;
  };
};

void check_valid(int argc, char* argv[]){
  if(argc<2){
    cerr<<"no directory input!"<<endl;
    exit(1);
  }
  for(int i=1;i<argc;i++){
    struct stat sb;
    if(!(stat(argv[i],&sb)==0 && S_ISDIR(sb.st_mode))){
      cerr<<"invalid directory path:"<<argv[i]<<endl;
      exit(1);
    }
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

void finddup(HashTable ht,ostream &shell){
  //ofstream shell("dedup.sh");
  shell<<"#!/bin/bash"<<endl;
  list<pair<string,string> > pairs=ht.SimilarPairs();
  for(auto iter=pairs.begin();iter!=pairs.end(); iter++){
    ifstream ifs1((*iter).first);
    ifstream ifs2((*iter).second);
    string s1;
    string s2;
    getline(ifs1,s1,(char)ifs1.eof());
    getline(ifs2,s2,(char)ifs2.eof());
    if(!s1.compare(s2)){
      shell<<"#Removing "<<(*iter).second<<" (duplicate of "<<(*iter).first<<")."<<endl;
      shell<<"rm "<<(*iter).second<<endl;
      auto iter1=iter;
      iter1++;
      for(;iter1!=pairs.end();iter1++){
	if((*iter1).first==(*iter).second || (*iter1).second==(*iter).second){
	  iter1=pairs.erase(iter1);
	}
      }
    }
  }
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
  for(auto iter=filenames.begin();iter!=filenames.end(); iter++){
    ifstream ifs(*iter);
    string s;
    getline(ifs,s,(char)ifs.eof());
    ht.add(s,*iter);
  }
  finddup(ht,cout);
  return EXIT_SUCCESS;
}
