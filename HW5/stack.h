#ifndef STACK_H
#define STACK_H

#include "arraylist.h"

template <class  T>
class Stack : private ArrayList<T>
{
 public:
  // add appropriate constructors and destructors
  Stack();
  ~Stack();

  bool isEmpty() const;
  /* returns whether the stack contains any elements */

  void push(const T& val);
  /* adds a value to the top of the stack */

  void pop();
  /* deletes the top value from the stack */

  T const & top() const;
  /* returns the top value on the stack */
};

#include "stackImpl.h"

#endif
