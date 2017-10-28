#ifndef __BST__
#define __BST__
#include <iostream>
#include <exception>
#include <cstdlib>
#include "set.h"

template<typename T>
class BstSet: public Set<T>{
 private:
  class Node{
  public:
    Node *left;
    Node *right;
    T k;
  Node():left(NULL),right(NULL){};
  Node(T key):left(NULL),right(NULL),k(key){};
  };
  Node * root;
  
 public:
 BstSet():root(NULL){};

  void copy(Node * &current, const Node* rcurrent){
    if(rcurrent!=NULL){
      current=new Node(rcurrent->k);
      if(rcurrent->left!=NULL) copy(current->left,rcurrent->left);
      if(rcurrent->right!=NULL) copy(current->right,rcurrent->right);
    }
  };
 BstSet(const BstSet &rhs):root(NULL){
    copy(root,rhs.root);
  };
  BstSet & operator=(const BstSet &rhs){
    if(this!=&rhs){
      destory(root);
      copy(root,rhs.root);
    }
    return *this;
  };
  
  void destory(Node * & current){
    if(current!=NULL){
      destory(current->left);
      destory(current->right);
      delete current;
      current=NULL;
    }
  };
  ~BstSet(){
    destory(root);
  };

  void insert(Node * & current,const T & key){
    if(current==NULL) current=new Node(key);
    else if(key>current->k){
      if(current->right) insert(current->right,key);
      else current->right=new Node(key);
    }
    else if(key<current->k){
      if(current->left) insert(current->left,key);
      else current->left=new Node(key);
    }
  };
  virtual void add(const T & key){
    insert(root,key);
  };

  bool find(Node * current,const T & key) const{
    if(key>current->k){
      if(current->right==NULL){
	return false;
      }
      return find(current->right,key);
    }
    else if(key<current->k){
      if(current->left==NULL){
	return false;
      }
      return find(current->left,key);
    }
    else return true;
  };
  virtual bool contains(const T & key) const{
    if(root==NULL) return false;
    return find(root,key);
  };

  Node * FinMin(Node * current){
    if(current->left!=NULL) return FinMin(current->left);
    else return current;
  }
  Node* del(Node * & current,const T & key){
    if(current==NULL){
      return NULL;
    }
    if(key<current->k) {
      current->left=del(current->left, key);
    }
    else if(key>current->k){
      current->right=del(current->right, key);
    }
    else{
      if(current->left == NULL && current->right == NULL) {
	delete current;
	current = NULL;
      }
      else if(current->left == NULL) {
	Node *temp = current;
	current = current->right;
	delete temp;
      }
      else if(current->right == NULL) {
	Node *temp = current;
	current=current->left;
	delete temp;
      }
      else{
	Node *temp = FinMin(current->right);
	current->k=temp->k;
	current->right=del(current->right,temp->k);
      }
    }
    return current;
  };
  virtual void remove(const T& key){
    root=del(root,key);
  };

  void traverse(Node* current){
    if(current!=NULL){
      traverse(current->left);
      std::cout<<current->k<<" ";
      traverse(current->right);
      //std::cout<<current->k<<" ";
    }
  };
  void print(){
    traverse(root);
  };
};

#endif
