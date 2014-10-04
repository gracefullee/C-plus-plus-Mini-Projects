#ifndef ARRAYLIST_IMPL_H
#define ARRAYLIST_IMPL_H

#include <iostream>
#include <stdexcept>

using namespace std;

template <class T>
ArrayList<T>::ArrayList()
{
	_size = 0;
	_capacity = 1;
	_data = new T[_capacity];
}

template <class T>
ArrayList<T>::ArrayList (int cap)
{
	_size = 0;
	_capacity = cap;
	_data = new T[cap];
}

template <class T>
ArrayList<T>::~ArrayList()
{
	delete [] _data;
}

template <class T>
int ArrayList<T>::size () const
{
	return _size;
}

template <class T>
void ArrayList<T>::insert (int position, const T & val)
{
	if(_size == _capacity){
		resize();
	}
	if(position>=0 && position<=(_size-1)){
		for(int i=_size; i>position; i--){
			_data[i] = _data[i-1];
		}
		_data[position] = val;
		_size++;
	}
	else if(position==_size){
		_data[position] = val;
		_size++;
	}
	else if(position>_size || position<0){
		throw out_of_range ("Please Enter a Valid Position");
	}
}

template <class T>
void ArrayList<T>::remove (int position)
{
	if(_size==0){
		throw invalid_argument ("The List is Empty");
	}
	if(position>=0 && position<=(_size-2)){
		for(int i=position; i<(_size-1); i++){
			_data[i] = _data[i+1];
		}
		_size--;
	}
	else if(position==(_size-1)){
		_size--;
	}
	else{
		throw out_of_range ("Please Enter a Valid Position");
	}
}

template <class T>
void ArrayList<T>::set (int position, const T & val)
{
	if(position>=0 && position<_size){
		_data[position] = val;
	}
	else{
		throw out_of_range ("Please Enter a Valid Position");
	}
}

template <class T>
T& ArrayList<T>::get (int position)
{
	if(position>=0 && position<_size){
		return _data[position];
	}
	else{
		throw out_of_range ("Please Enter a Valid Position");
	}
}

template <class T>
T const & ArrayList<T>::get (int position) const
{
	if(position>=0 && position<_size){
		return _data[position];
	}
	else{
		throw out_of_range ("Please Enter a Valid Position");
	}
}

template <class T>
int ArrayList<T>::capacity () const
{
	return _capacity;
}

template <class T>
void ArrayList<T>::resize ()
{
	T* temp = new T[2*_capacity];
	_capacity *= 2;
	for(int i=0; i<_size; i++){
		temp[i] = _data[i];
	}
	T* old = _data;
	_data = temp;
	delete [] old;
}

template <class T>
void DoublingArrayList<T>::resize ()
{
	T* temp = new T[2*ArrayList<T>::_capacity];
	ArrayList<T>::_capacity *= 2;
	for(int i=0; i<ArrayList<T>::_size; i++){
		temp[i] = ArrayList<T>::_data[i];
	}
	T* old = ArrayList<T>::_data;
	ArrayList<T>::_data = temp;
	delete [] old;
}


template <class T>
void PlusOneArrayList<T>::resize ()
{

	T* temp = new T[ArrayList<T>::_capacity+1];
	ArrayList<T>::_capacity += 1;
	for(int i=0; i<ArrayList<T>::_size; i++){
		temp[i] = ArrayList<T>::_data[i];
	}
	T* old = ArrayList<T>::_data;
	ArrayList<T>::_data = temp;
	delete [] old;

}

template <class T>
void PlusTenArrayList<T>::resize ()
{
	T* temp = new T[ArrayList<T>::_capacity+10];
	ArrayList<T>::_capacity += 10;
	for(int i=0; i<ArrayList<T>::_size; i++){
		temp[i] = ArrayList<T>::_data[i];
	}
	T* old = ArrayList<T>::_data;
	ArrayList<T>::_data = temp;
	delete [] old;
}

#endif
