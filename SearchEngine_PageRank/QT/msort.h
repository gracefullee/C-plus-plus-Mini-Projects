#ifndef MSORT_H
#define MSORT_H

#include <vector>
#include <iostream>
#include "../WebPage.h"



using namespace std;

template <class T, class Comparator>
void mergeSort (std::vector<T>& myArray, Comparator comp)
{
	mSort(myArray, 0, myArray.size()-1, comp);
	
}

template <class T, class Comparator>
void mSort (std::vector<T>& myArray, int start, int end, Comparator comp)
{
	if(start>=end){
		return;
	}
	else{
		int mid = (start+end)/2;
		mSort(myArray, start, mid, comp);
		mSort(myArray, mid+1, end, comp);
		merge(myArray, start, mid, mid+1, end, comp);
	}
}

template <class T, class Comparator>
void merge (std::vector<T>& myArray, int s1, int e1, int s2, int e2, Comparator comp)
{
	std::vector<T> left, right;
	if(s1==e1){
		left.push_back(myArray[s1]);
	}
	else{
		for(int i=s1; i<e1+1; i++){
			left.push_back(myArray[i]);
		}
	}
	if(s2==e2){
		right.push_back(myArray[s2]);
	}
	else{
		for(int i=s2; i<e2+1; i++){
			right.push_back(myArray[i]);
		}
	}
	int L = 0; int R = 0; 
	int index = s1;
	while(L < left.size() && R < right.size()){
		if(comp(left[L],right[R])==0){
			myArray[index] = right[R];
			index++; R++;
		}
		else{
			myArray[index] = left[L];
			index++; L++;
		}
	}
	//Place rest of the remaining numbers into the list
	if(L==left.size()){
		while(R < right.size()){
			myArray[index] = right[R];
			index++; R++;
		}
	}
	else if(R==right.size()){
		while(L < left.size()){
			myArray[index] = left[L];
			index++; L++;
		}
	}
}

#endif
