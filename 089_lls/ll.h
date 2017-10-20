#ifndef _LL_H_
#define _LL_H_
#include <cstdlib>
#include <exception>
#include <assert.h>
#include <cstdio>

class My_Exception:public std::exception{
 public:
  virtual const char * what() const throw(){
    return "index out of range.\n";
  }
};

template<typename T>
class LinkedList{
 private:
  
  class Node{
  public:
    T data;
    Node * next;
    Node * previous;
  Node(const T& d):data(d),next(NULL),previous(NULL){}
  Node(const T& d, Node * n, Node * p):data(d),next(n),previous(p){}
  };
  
  /*  class My_Exception:public std::exception{
  public:
    virtual const char * what() const throw(){
      return "index out of range.\n";
    }
    };*/
  
  Node * head;
  Node * tail;
  
 public:
  
 LinkedList():head(NULL),tail(NULL){};
  
 LinkedList(const LinkedList &rhs):head(NULL),tail(NULL){
    for(Node * it=rhs.head;it!=NULL;it=it->next){
      addBack(it->data);
    }
  };

  LinkedList& operator=(const LinkedList &rhs){
    if(this!=&rhs){
      destory();
      for(Node * it=rhs.head;it!=NULL;it=it->next){
	addBack(it->data);
      }
    }
    return *this;
  };

  T& operator[](int index){
    My_Exception e;
    if(index<0 || index>getSize()){
      throw e;
    }
    Node * it=head;
    for(int i=0;i<index;i++){
      it=it->next;
    }
    return it->data;
  };

  const T& operator[](int index) const{
    My_Exception e;
    if(index<0 || index>getSize()){
      throw e;
    }
    Node * it=head;
    for(int i=0;i<index;i++){
      it=it->next;
    }
    return it->data;
  };
    
  void destory(){
    Node * it=NULL;
    while(head!=NULL){
      it=head;
      head=head->next;
      delete it;
    }
  };

  ~LinkedList(){
    destory();
  };
  
  void addFront(const T &item){
    Node * temp=new Node(item);
    temp->next=head;
    if(head!=NULL) head->previous=temp;
    else tail=temp;
    head=temp;
  };
  
  void addBack(const T &item){
    Node * temp=new Node(item);
    temp->previous=tail;
    if(tail!=NULL) tail->next=temp;
    else head=temp;
    tail=temp;
  };
  
  Node * remove_helper(const T &data,Node * current, bool &find){
    if(current==NULL){
      return NULL;
    }
    if(data==current->data){
      find=true;
      Node * ans=current->next;
      if(ans!=NULL) ans->previous=current->previous;
      delete current;
      return ans;
    }
    current->next=remove_helper(data,current->next,find);
    return current;
  };
  
  bool remove(const T &item){
    bool find=false;
    head=remove_helper(item,head,find);
    return find;
  };
  
  int find(const T &item) const{
    int index=-1;
    Node * it=head;
    for(int i=0;it!=NULL;it=it->next){
      if(it->data==item){
	index=i;
	return index;
      }
      i++;
    }
    return index;
  };
  
  int getSize() const{
    int size=0;
    for(Node * it=head;it!=NULL;it=it->next){
      size+=1;
    }
    return size;
  };
  
};


#endif
