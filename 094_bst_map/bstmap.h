#ifndef __BST__
#define __BST__
#include <iostream>
#include <exception>
#include <cstdlib>
#include "map.h"

template<typename K, typename V>
class BstMap: public Map<K,V>{
 private:
  class Node{
  public:
    Node *left;
    Node *right;
    K k;
    V v;
  Node():left(NULL),right(NULL){};
  Node(K key,V value):left(NULL),right(NULL),k(key),v(value){};
  };
  Node * root;
  
 public:
 BstMap():root(NULL){};

  void copy(Node * &current, const Node* rcurrent){
    if(rcurrent!=NULL){
      current=new Node(rcurrent->k,rcurrent->v);
      if(rcurrent->left!=NULL) copy(current->left,rcurrent->left);
      if(rcurrent->right!=NULL) copy(current->right,rcurrent->right);
    }
  };
 BstMap(const BstMap &rhs):root(NULL){
    copy(root,rhs.root);
  };
  BstMap & operator=(const BstMap &rhs){
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
  ~BstMap(){
    destory(root);
  };

  void insert(Node * & current,const K & key, const V & value){
    if(current==NULL) current=new Node(key,value);
    else if(current->k==key) current->v=value;
    else if(key>current->k){
      if(current->right) insert(current->right,key,value);
      else current->right=new Node(key,value);
    }
    else if(key<current->k){
      if(current->left) insert(current->left,key,value);
      else current->left=new Node(key,value);
    }
  };
  virtual void add(const K & key, const V & value){
    insert(root,key,value);
  };

  const V & find(Node * current,const K & key) const{
    if(key>current->k){
      if(current->right==NULL){
	throw std::invalid_argument("invalide key!");
      }
      return find(current->right,key);
    }
    else if(key<current->k){
      if(current->left==NULL){
	throw std::invalid_argument("invalide key!");
      }
      return find(current->left,key);
    }
    else return current->v;
  };
  virtual const V & lookup(const K & key) const throw (std::invalid_argument){
    if(root==NULL) throw std::invalid_argument("invalide key!");
    return find(root,key);
  };

  Node * FinMin(Node * current){
    if(current->left!=NULL) return FinMin(current->left);
    else return current;
  }
  Node* del(Node * & current,const K & key){
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
	current->v=temp->v;
	current->right=del(current->right,temp->k);
      }
    }
    return current;
  };
  virtual void remove(const K& key){
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
