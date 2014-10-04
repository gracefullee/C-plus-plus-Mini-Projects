#ifndef STACK_IMPL_H
#define STACK_IMPL_H

#include <iostream>

template <class T>
Stack<T>::Stack ()
{
	
}

template <class T>
Stack<T>::~Stack ()
{
	
}

template <class T>
bool Stack<T>::isEmpty () const
{
	if(ArrayList<T>::size()==0){
		return true;
	}
	return false;
}

template <class T>
void Stack<T>::push (const T& val)
{
	ArrayList<T>::insert(ArrayList<T>::size(), val);
}

template <class T>
void Stack<T>::pop ()
{
	if(!isEmpty()){
		ArrayList<T>::remove(ArrayList<T>::size()-1);
	}
}

template <class T>
T const & Stack<T>::top () const
{
	if(!isEmpty())
		return ArrayList<T>::get(ArrayList<T>::size()-1);
	else{
		return NULL;
	}
}

#endif