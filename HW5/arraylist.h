#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <iostream>
#include "ilist.h"

template <class T>
class ArrayList : public IList<T>
{
public:
	ArrayList ();
	
	ArrayList (int cap);
	
	~ArrayList ();
	
	int size () const;
	
	void insert (int position, const T & val);
	
	void remove (int position);
	
	void set (int position, const T & val);
	
	T& get (int position);

	T const & get (int position) const;

	int capacity () const;

protected:
	T* _data;
	int _size;
	int _capacity;
	virtual void resize ();
};

template <class T>
class DoublingArrayList : public ArrayList<T>
{
public:
	void resize ();
};

template <class T>
class PlusOneArrayList : public ArrayList<T>
{
public:
	void resize ();
};

template <class T>
class PlusTenArrayList : public ArrayList<T>
{
public:
	void resize ();
};

#include "arraylistImpl.h"

#endif
