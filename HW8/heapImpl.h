#ifndef HEAPIMPL_H
#define HEAPIMPL_H

#include <iostream>
#include <algorithm>
#include <stdexcept>

template <class T, class Comparator>
MaxHeap<T,Comparator>::MaxHeap(int d, Comparator comp)
{
	this->comp = comp;
	if(d<2){
		this->d = d;
	}
	else{
		this->d = d;
	}
}

template <class T, class Comparator>
MaxHeap<T,Comparator>::~MaxHeap()
{
	
}

template <class T, class Comparator>
void MaxHeap<T,Comparator>::add (const T & item)
{
	Heap.push_back(item);
	if(Heap.size()>1){
		int index = Heap.size()-1;
		int parent = (index-1)/d;
		while(parent >= 0 && comp(Heap[parent],Heap[index])){
			std::swap(Heap[index],Heap[parent]);
			index = parent;
			parent = (index-1)/d;
		}
	}
}

template <class T, class Comparator>
const T & MaxHeap<T,Comparator>::peek () const
{
	if(Heap.size()==0)
		throw std::out_of_range("Heap is Empty");
	else{
		return Heap[0];
	}
}

template <class T, class Comparator>
void MaxHeap<T,Comparator>::remove()
{
	Heap[0] = Heap.back();
	Heap.pop_back();
	heapify(0);
}

template <class T, class Comparator>
bool MaxHeap<T,Comparator>::isEmpty()
{
	return (Heap.size()==0);
}

template <class T, class Comparator>
void MaxHeap<T,Comparator>::heapify(int index)
{
	int leftChild = (d*(index+1))-(d-1);
	if(leftChild > (Heap.size()-1))
		return;
	int largerChild = (d*(index+1))-(d-1);
	int nextChild = largerChild+1;
	if(nextChild < Heap.size()){
		for(int i=0; i<d-1; i++){
			if(nextChild < Heap.size()){
				if(comp(Heap[largerChild],Heap[nextChild]))
					largerChild = nextChild;
				nextChild++;
			}
		}
	}
	if(comp(Heap[index],Heap[largerChild])){
		std::swap(Heap[index],Heap[largerChild]);
		heapify(largerChild);
	}
}

#endif