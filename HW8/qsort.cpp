#include <iostream>
#include <ctime>
#include <vector>
#include "qsort.h"

using namespace std;

int list_size = 10000;

struct IntComp{
	bool operator()(const int lhs, const int rhs)
	{
		return lhs < rhs;
	}
};

double MeasureBackPivotTime(int *list)
{
	clock_t start, finish;
	double time = 0.0;
	
	// time measurement code goes here
	start = clock();
	IntComp comp;
	qsortBack(list, comp, 0, list_size-1);
	finish = clock();
	time = (double)(finish-start);
	time /= CLOCKS_PER_SEC;
	return time;
}

double MeasureRandPivotTime(int *list)
{
	clock_t start, finish;
    double time = 0.0;
    
    // time measurement code goes here
    start = clock();
    IntComp comp;
    qsortRand(list, comp, 0, (list_size)-1);
    finish = clock();
    time = (double)(finish-start);
    time /= CLOCKS_PER_SEC;
    return time;
}

int main()
{
	vector<double> RandTime;
	vector<double> BackTime;
	for(int i=0; i<10; i++){
		RandTime.push_back(0.0);
		BackTime.push_back(0.0);
	}
	
	for(int k=0; k<20; k++){
		double backTime = 0.0, randTime = 0.0;
		int **lists = new int*[10];
		
		for(int i=0; i<10; i++){
			int* myList = new int[list_size];
			lists[i] = myList;
			for(int j=0; j<10000; j++){
				lists[i][j] = j;
			}
		}
		
		int copy[list_size];
		for (int i = 0; i < 10; i++){
			int list[list_size];
			for(int a=0; a<list_size; a++){
				list[a] = lists[i][a];
			}
			if(i==0){
				for(int j =0; j<list_size; j++){
					copy[j] = list[j];
				}
				backTime = MeasureBackPivotTime(list);
				randTime = MeasureRandPivotTime(copy);
				RandTime[i] += randTime;
				BackTime[i] += backTime;
			}
			else if(i==1){
				for(int j=0; j<50; j++){
					swap(list[rand()%(list_size)],list[rand()%(list_size)]);
				}
				for(int k =0; k<list_size; k++){
					copy[k] = list[k];
				}
				backTime = MeasureBackPivotTime(list);
				randTime = MeasureRandPivotTime(copy);
				RandTime[i] += randTime;
				BackTime[i] += backTime;
			}
			else if(i==2){
				for(int j=0; j<100; j++){
					swap(list[rand()%(list_size)],list[rand()%(list_size)]);
				}
				for(int k =0; k<list_size; k++){
					copy[k] = list[k];
				}
				backTime = MeasureBackPivotTime(list);
				randTime = MeasureRandPivotTime(copy);
				RandTime[i] += randTime;
				BackTime[i] += backTime;
			}
			else if(i==3){
				for(int j=0; j<300; j++){
					swap(list[rand()%(list_size)],list[rand()%(list_size)]);
				}
				for(int k =0; k<list_size; k++){
					copy[k] = list[k];
				}
				backTime = MeasureBackPivotTime(list);
				randTime = MeasureRandPivotTime(copy);
				RandTime[i] += randTime;
				BackTime[i] += backTime;
			}
			else if(i==4){
				for(int j=0; j<500; j++){
					swap(list[rand()%(list_size)],list[rand()%(list_size)]);
				}
				for(int k =0; k<list_size; k++){
					copy[k] = list[k];
				}
				backTime = MeasureBackPivotTime(list);
				randTime = MeasureRandPivotTime(copy);
				RandTime[i] += randTime;
				BackTime[i] += backTime;
			}
			else if(i==5){
				for(int j=0; j<1000; j++){
					swap(list[rand()%(list_size)],list[rand()%(list_size)]);
				}
				for(int k =0; k<list_size; k++){
					copy[k] = list[k];
				}
				backTime = MeasureBackPivotTime(list);
				randTime = MeasureRandPivotTime(copy);
				RandTime[i] += randTime;
				BackTime[i] += backTime;
			}
			else if(i==6){
				for(int j=0; j<2000; j++){
					swap(list[rand()%(list_size)],list[rand()%(list_size)]);
				}
				for(int k =0; k<list_size; k++){
					copy[k] = list[k];
				}
				backTime = MeasureBackPivotTime(list);
				randTime = MeasureRandPivotTime(copy);
				RandTime[i] += randTime;
				BackTime[i] += backTime;
			}   
			else if(i==7){
				for(int j=0; j<5000; j++){
					swap(list[rand()%(list_size)],list[rand()%(list_size)]);
				}
				for(int k =0; k<list_size; k++){
					copy[k] = list[k];
				}
				backTime = MeasureBackPivotTime(list);
				randTime = MeasureRandPivotTime(copy);
				RandTime[i] += randTime;
				BackTime[i] += backTime;
			}
			else if(i==8){
				for(int j=0; j<10000; j++){
					swap(list[rand()%(list_size)],list[rand()%(list_size)]);
				}
				for(int k =0; k<list_size; k++){
					copy[k] = list[k];
				}
				backTime = MeasureBackPivotTime(list);
				randTime = MeasureRandPivotTime(copy);
				RandTime[i] += randTime;
				BackTime[i] += backTime;
			}
			else if(i==9){
				for(int j=0; j<20000; j++){
					swap(list[rand()%(list_size)],list[rand()%(list_size)]);
				}
				for(int k =0; k<list_size; k++){
					copy[k] = list[k];
				}
				backTime = MeasureBackPivotTime(list);
				randTime = MeasureRandPivotTime(copy);
				RandTime[i] += randTime;
				BackTime[i] += backTime;
			}
		}
   	
		for(int i=0; i<10; i++){
			delete lists[i];
		}
		
		delete [] lists;
	}
	
	for(int i=0; i<10; i++){
		cout << "i = " << i << endl;
		RandTime[i] = RandTime[i]/20;
		BackTime[i] = BackTime[i]/20;
		cout << "  Back: " << BackTime[i] << endl;
		cout << "  Rand: " << RandTime[i] << endl;
	}

	return 0; 
}