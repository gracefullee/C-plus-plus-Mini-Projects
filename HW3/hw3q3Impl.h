#ifndef HW3Q3IMPL_H
#define HW3Q3IMPL_H

#include <iostream>
#include <stdexcept>


using namespace std;

template <class T>
List<T>::List()
{
	head = NULL;
	tail = NULL;
}

template <class T>
List<T>::~List()
{
	while(head!=NULL){
		Item<T> *current = head;
		head = head->next;
		delete current;
	}
	tail = NULL;
}

template <class T>
int List<T>::size() const
{
	int count = 0;
	if(head==NULL && tail==NULL){
		return 0;
	}
	Item<T> *current = head;
	while(current!=NULL){
		current = current->next;
		count++;
	}
	return count;
}

template <class T>
void List<T>::insert(int position, const T & val)
{
	if(position>size()||position<0){
		throw out_of_range ("Please Enter a Valid Position");
	}
	if(position==0){
		Item<T> *newItem = new Item<T>;
		newItem->prev = NULL;
		newItem->value = val;
		if(head==NULL && tail==NULL){
			newItem->next = NULL;
			head = newItem;
			tail = newItem;
		}
		else{
			Item<T> *current = head;
			newItem->next = current;
			current->prev = newItem;
			head = newItem;
		}
	}
	else if(position > 0 && position < (size())){
		int count = 0;
		Item<T> *current = head;
		while(count!=position){
			current = current->next;
			count++;
		}
		Item<T> *newItem = new Item<T>;
		newItem->prev = current->prev;
		newItem->value = val;
		newItem->next = current;
		current->prev = newItem;
	}
	else if(size()>0 && position == (size())){
		Item<T> *current = tail;
		Item<T> *newItem = new Item<T>;
		newItem->prev = tail;
		newItem->value = val;
		newItem->next = NULL;
		current->next = newItem;
		tail = newItem;
	}
}

template <class T>
void List<T>::remove (int position)
{
	if(position>size()||position<0){
		throw out_of_range ("Please Enter a Valid Position");
	}
	if(position==0){
		Item<T> *current = head;
		head = head->next;
		if(head==NULL){
			tail = NULL;
		}
		delete current;
	}
	else if(position>0 && position<(size()-1)){
		int count = 0;
		Item<T> *current = head;
		while(count!=position){
			current = current->next;
			count++;
		}
		current->prev->next = current->next;
		current->next->prev = current->prev;
		delete current;
	}
	else if(position==(size()-1)){
		Item<T> *current = tail;
		tail = tail->prev;
		if(tail==NULL){
			head = NULL;
		}
		delete current;
	}
}

template <class T>
void List<T>::set(int position,const T & val)
{
	if(position>size()||position<0){
		throw out_of_range ("Please Enter a Valid Position");
	}
	int count = 0;
	Item<T> *current = head;
	while(count!=position){
		current = current->next;
		count++;
	}
	current->value = val;
}

template <class T>
T& List<T>::get(int position) const
{
	if(position>size()||position<0){
		throw out_of_range ("Please Enter a Valid Position");
	}
	int count = 0;
	Item<T> *current = head;
	while(count!=position){
		current = current->next;
		count++;
	}
	return current->value;
}

#endif
