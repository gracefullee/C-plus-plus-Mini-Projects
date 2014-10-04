#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include <vector>

template <class T, class Comparator>

  class MaxHeap {
     public:
       MaxHeap (int d, Comparator comp);
       /* Constructor that builds a d-ary Max Heap using the given
          comparator to compare elements and decide which one is
          larger. 
          This should work for any d >= 2,
          but doesn't have to do anything for smaller d.*/

       ~MaxHeap ();

       void add (const T & item);
         /* adds the item to the heap */

       const T & peek () const;
         /* returns the element with maximum priority.
            Throws an exception if the heap is empty. */

       void remove ();
         /* removes the element with maximum priority. */

       bool isEmpty ();
         /* returns true iff there are no elements on the heap. */
       
       void heapify (int index);
     private:
       std::vector<T> Heap;
       int d; 
       Comparator comp;
  };

#include "heapImpl.h"

#endif