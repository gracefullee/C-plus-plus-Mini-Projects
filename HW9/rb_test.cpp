/*
 * rb_test.cpp
 *
 *  Created on: Apr 14, 2014
 *      Author: kempe
 */

#include <iostream>
#include <exception>
#include <cstdlib>
#include "rbbst.h"

/* -----------------------------------------------------
 * main for testing
 ------------------------------------------------------*/

int main (void)
{
  int a[100];

  // Put the numbers 0..99 in the array in a random order
  for (int i = 0; i < 100; i ++) a[i] = i;
  for (int i = 99; i > 0; i --)
  { 
    int j = rand () % (i+1);
    int b = a[i]; a[i] = a[j]; a[j] = b;
  }

  RedBlackTree<int, int> *T = new RedBlackTree<int, int> ();
  // Put the numbers (and their squares) into the tree in random order.
  for (int i = 0; i < 100; i ++){
      T->add (a[i], a[i]*a[i]);
  }
  
  T->print (); // could help with debugging

  // Test to make sure the iterator prints the items in correct order
  for( RedBlackTree<int, int>::iterator it = T->begin(); it != T->end(); ++it)
     {
        std::cout << "(" << it->first << "," << it->second << ") " ;
     }
  std::cout << std::endl;

  // Make sure that lookup works correctly by looking for all items.
  for (int i = 99; i >= 0; i --) 
      std::cout << T->lookup (i) << "\n";

  delete T;
  return 0;
}
