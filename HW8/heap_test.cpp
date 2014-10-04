#include <iostream>
#include <ctime>
#include <algorithm>
#include "heap.h"

using namespace std;

struct IntComp{
	bool operator()(const int lhs, const int rhs)
	{
		return lhs < rhs;
	}
};

double MeasureInsertTime(MaxHeap<int,IntComp> *heap, vector<int>* list)
{
	clock_t start, finish;
	double time = 0.0;
	
	// time measurement code goes here
	start = clock();
	vector<int> intList = *list;
	for(unsigned int i=0; i<10000; i++){
		heap->add(intList[i]);
	}
	finish = clock();
	time = (double)(finish-start);
	time /= CLOCKS_PER_SEC;
	return time;
}

double MeasureRemoveTime(MaxHeap<int,IntComp> *heap)
{
	clock_t start, finish;
	double time = 0.0;
	// time measurement code goes here
	start = clock();

	for(int i=0; i<10000; i++){
		heap->remove();
	}
	finish = clock();
	time = (double)(finish-start);
	time /= CLOCKS_PER_SEC;
	return time;
}

int main()
{

	//Created 10 Random Sequences of 10000 integers
	vector<int> **lists = new vector<int>*[10];
	
	for(int i=0; i<10; i++){
		vector<int>* myList = new vector<int>;
		lists[i] = myList;
		for(int j=0; j<10000; j++){
			lists[i]->push_back(j);
		}
		for(int j=0; j<10000; j++){
			vector<int> list = *lists[i];
			swap(list[rand()%(list.size())],list[rand()%(list.size())]);
		}
	}

	
	//Insert into D-ary MaxHeap
	IntComp comp;
	vector<double> heapInsertTime;
	vector<double> heapRemoveTime;
	for(int i=0; i<7; i++){
		heapInsertTime.push_back(0.0);
		heapRemoveTime.push_back(0.0);
	}
	vector<MaxHeap<int,IntComp>*> heaps;
	MaxHeap<int,IntComp> MaxHeap2(2,comp);
	MaxHeap<int,IntComp> MaxHeap3(3,comp);
	MaxHeap<int,IntComp> MaxHeap4(4,comp);
	MaxHeap<int,IntComp> MaxHeap10(10,comp);
	MaxHeap<int,IntComp> MaxHeap20(20,comp);
	MaxHeap<int,IntComp> MaxHeap50(50,comp);
	MaxHeap<int,IntComp> MaxHeap100(100,comp);
	

	heaps.push_back(&MaxHeap2);
	heaps.push_back(&MaxHeap3);
	heaps.push_back(&MaxHeap4);
	heaps.push_back(&MaxHeap10);
	heaps.push_back(&MaxHeap20);
	heaps.push_back(&MaxHeap50);
	heaps.push_back(&MaxHeap100);
	
	for(int i=0; i<7; i++){
		for(int j=0; j<10; j++){
			heapInsertTime[i] += MeasureInsertTime(heaps[i],lists[j]);
			heapRemoveTime[i] += MeasureRemoveTime(heaps[i]);
		}
	}

	for(int i=0; i<7; i++){
		double avgInsert = heapInsertTime[i]/10;
		double avgRemove = heapRemoveTime[i]/10;
		if(i==0) cout << "D = 2" << endl;
		else if(i==1) cout << "D = 3" << endl;
		else if(i==2) cout << "D = 4" << endl;
		else if(i==3) cout << "D = 10" << endl;
		else if(i==4) cout << "D = 20" << endl;
		else if(i==5) cout << "D = 50" << endl;
		else if(i==6) cout << "D = 100" << endl;
		cout << "  Insert: " << avgInsert << endl;
		cout << "  Remove: " << avgRemove << endl;
	}

	return 0;
	
}