#ifndef QSORT_H
#define QSORT_H

#include <iostream>
#include <cstdlib>
#include <algorithm>

template <class T, class Comparator>
int partition (T *myArray, Comparator comp, int start, int end, int p)
{
	T pivot = myArray[p];
	std::swap(myArray[p], myArray[end]);
	int left = start; int right = end-1;
	while(left < right){
		while(myArray[left] <= pivot && left < right)
			left++;
		while(myArray[right] >= pivot && left < right)
			right--;
		if(left < right)
			std::swap(myArray[left], myArray[right]);
	}
	std::swap(myArray[right],myArray[end]);
	return right;
}

template <class T, class Comparator>
void qsortBack (T* myArray, Comparator comp, int start, int end)
{
	if(start >= end)
		return;
	int p = end;
	int loc = partition(myArray, comp, start, end, p);
	qsortBack(myArray, comp, start, loc);
	qsortBack(myArray, comp, loc+1, end);
}

template <class T, class Comparator>
void qsortRand (T* myArray, Comparator comp, int start, int end)
{
	if(start >= end)
		return;
	int p = rand() % (end);
	int loc = partition(myArray, comp, start, end, p);
	qsortBack(myArray, comp, start, loc);
	qsortBack(myArray, comp, loc+1, end);
}



#endif