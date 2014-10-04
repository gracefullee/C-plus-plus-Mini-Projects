/*
 * rbbst.h
 *
 *  Created on: Apr 14, 2014
 *      Author: kempe
 */

#include <iostream>
#include <exception>
#include <cstdlib>
#include "bst.h"

/* -----------------------------------------------------
 * Red-Black Nodes 
 ------------------------------------------------------*/

enum Color {red, black};

template <class KeyType, class ValueType>
class RedBlackNode : public Node<KeyType, ValueType>
{
public:
	RedBlackNode (KeyType k, ValueType v, RedBlackNode<KeyType, ValueType> *p)
	: Node<KeyType, ValueType> (k, v, p)
	  { color = red; }

	virtual ~RedBlackNode () {}

	Color getColor () const
	{ return color; }

	void setColor (Color c)
	{ color = c; }

        /* The type casting allows us to treat getParent, getLeft, getRight
           as returning RedBlackNode instead of Node */
	virtual RedBlackNode<KeyType, ValueType> *getParent () const
	{ return (RedBlackNode<KeyType,ValueType>*) this->_parent; }

	virtual RedBlackNode<KeyType, ValueType> *getLeft () const
	{ return (RedBlackNode<KeyType,ValueType>*) this->_left; }

	virtual RedBlackNode<KeyType, ValueType> *getRight () const
	{ return (RedBlackNode<KeyType,ValueType>*) this->_right; }

protected:
	Color color;
};

/* -----------------------------------------------------
 * Red-Black Search Tree
 ------------------------------------------------------*/

template <class KeyType, class ValueType>
class RedBlackTree : public BinarySearchTree<KeyType, ValueType>
{
public:
  void add (KeyType key, ValueType value)
  {
	  if(this->root == NULL){
		  RedBlackNode<KeyType, ValueType>* newItem = new RedBlackNode<KeyType, ValueType>(key,value,NULL);
		  this->root = newItem;
		  ((RedBlackNode<KeyType,ValueType>*)(this->root))->setColor(black);

	  }
	  else{
		  RedBlackNode<KeyType,ValueType>* current = (RedBlackNode<KeyType,ValueType>*)(this->root);
		  current->setColor(black);
		  while(current!=NULL){
			  if(key < current->getKey()){
				  if(current->getLeft()==NULL){
					  RedBlackNode<KeyType, ValueType>* newItem = new RedBlackNode<KeyType, ValueType>(key,value,current);
					  current->setLeft(newItem);
					  if(newItem->getParent()->getColor()!=black)
						  fixTree(newItem);
					  break;
				  }
				  else{
					  current = current->getLeft();
				  }
			  }
			  else if(key > current->getKey()){
				  if(current->getRight()==NULL){
					  RedBlackNode<KeyType, ValueType>* newItem = new RedBlackNode<KeyType, ValueType>(key,value,current);
					  current->setRight(newItem);
					  if(newItem->getParent()->getColor()!=black)
						  fixTree(newItem);
					  break;
				  }
				  else{
					  current = current->getRight();
				  }
			  }
			  else{
				  current->setValue(value);
			  }
		  }
	  }
  }
  /* This one is yours to implement.
     It should add the (key, value) pair to the tree, 
     making sure that it remains a valid Red-Black Tree.
     If the key is already in the tree (with a possibly different associated value),
     then it should overwrite the value with the new one.
     We strongly recommend defining suitable (private) helper functions. */
  
private:
  void fixTree (RedBlackNode<KeyType, ValueType>* curr)
  {
	  if(findUncle(curr)==red){
		  recolor(curr);
		  
	  }
	  else if(findUncle(curr)==black && 
			  (curr->getParent()->getLeft()==curr && curr->getParent()->getParent()->getLeft()==curr->getParent()))
	  {	
		  rightRotate(curr->getParent());
		  recolor(curr);
	  }
	  else if(findUncle(curr)==black && 
			  (curr->getParent()->getRight()==curr && curr->getParent()->getParent()->getRight()==curr->getParent()))
	  {
		  leftRotate(curr->getParent());
		  recolor(curr);
	  }
	  else if(findUncle(curr)==black && (curr->getParent()->getRight()==curr &&
			  curr->getParent()->getParent()->getLeft()==curr->getParent()))
	  {
		  leftRotate(curr->getParent());
		  rightRotate(curr->getParent());
		  recolor(curr->getLeft());
	  }
	  else if(findUncle(curr)==black && (curr->getParent()->getLeft()==curr &&
			  curr->getParent()->getParent()->getRight()==curr->getParent()))
	  {
		  rightRotate(curr->getParent());
		  leftRotate(curr->getParent());
		  recolor(curr->getRight());
	  }
	  
  }
  
  Color findUncle (RedBlackNode<KeyType, ValueType>* curr)
  {
	  RedBlackNode<KeyType, ValueType>* me = curr;
	  if(curr->getParent()!=NULL){
		  curr = curr->getParent();
		  if(curr->getParent()!=NULL){
		  	curr = curr->getParent();
		  	if(curr->getRight()!=NULL && curr->getRight()!=me->getParent())
		  		return curr->getRight()->getColor();
		  	else if(curr->getLeft()!=NULL && curr->getLeft()!=me->getParent())
		  		return curr->getLeft()->getColor();
		  	else{
		  		return black;
		  	}
		  }
		  else{
			  return black;
		  }
	  }
	  else{
		  return black;
	  }
  }
  
  void leftRotate (RedBlackNode<KeyType, ValueType>* curr)
  {
	  RedBlackNode<KeyType, ValueType>* temp = curr->getRight();
	  curr->setRight(temp->getLeft());
	  if(temp->getLeft()!=NULL){
		  temp->getLeft()->setParent(curr);
	  }
	  temp->setParent(curr->getParent());
	  if(curr->getParent()==NULL){
		  this->root = temp;
	  }
	  else{
		  if(curr->getParent()->getLeft()==curr){
			  curr->getParent()->setLeft(temp);
		  }
		  else{
			  curr->getParent()->setRight(temp);
		  }
	  }
	  temp->setLeft(curr);
	  curr->setParent(temp);
  }
  	  
  void rightRotate (RedBlackNode<KeyType, ValueType>* curr)
  {
	  //Curr - y temp - x
	  RedBlackNode<KeyType, ValueType>* temp = curr->getLeft();
	  curr->setLeft(temp->getRight());
	  if(temp->getRight()!=NULL)
		  temp->getRight()->setParent(curr);
	  temp->setParent(curr->getParent());
	  if(curr->getParent()==NULL)
		  this->root = temp;
	  else{
		  if(curr->getParent()->getRight()==curr)
			  curr->getParent()->setRight(temp);
		  else{
			  curr->getParent()->setLeft(temp);
		  }
	  }
	  temp->setRight(curr);
	  curr->setParent(temp);
  }
  
  void recolor (RedBlackNode<KeyType, ValueType>* curr)
  {
	  if(curr->getParent()==NULL && curr->getColor()==red){
		  curr->setColor(black);
	  }
	  while(curr->getColor()==red && curr->getParent()->getColor()==red){
		  curr->getParent()->setColor(black);
		  if(curr->getParent()->getParent()->getLeft() == curr->getParent() && curr->getParent()->getParent()->getRight()!=NULL)
			  curr->getParent()->getParent()->getRight()->setColor(black);
		  if(curr->getParent()->getParent()->getRight() == curr->getParent() && curr->getParent()->getParent()->getLeft()!=NULL)
			  curr->getParent()->getParent()->getLeft()->setColor(black);
		  curr = curr->getParent();
	  }
  }
};

