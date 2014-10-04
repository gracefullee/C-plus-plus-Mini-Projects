#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>
#include <vector>
#include <stdexcept>
#include "msort.h"

using namespace std;

struct studentScore{
	public:
		string name;
		int rawScore;
		int curveScore;
};

struct intComp{
	bool operator()(const int lhs, const int rhs)
	{
		return lhs < rhs;
	}
};

void gradingCurve (vector<int> &grades, studentScore* &student);
int binSearch(vector<int> mylist, int  k, int start, int end);

int main(int argc, char* argv[])
{
	if(argc<3){
		cout << "Usage: ./grading input.txt output.txt" << endl;
		return -1;
	}
	
	//RUNTIME: O(n) - reading files from input.txt
	vector<int> gradingScore;
	vector<studentScore*> students;
	ifstream ifile;
	ifile.open(argv[1]);
	int num;
	string empty;
	ifile >> num;
	if(ifile.fail()){
		cout << "Please Check Input File" << endl;
		return -1;
	}
	ifile.ignore(80,'\n');
	for(int i=0; i<num; i++){
		string line;
		getline(ifile,line);
		string name;
		int score;
		stringstream ln;
		ln << line;
		ln >> name >> score;
		studentScore *st = new studentScore;
		st->rawScore = score;
		st->name = name;
		students.push_back(st);
	}
	for(int i=0; i<num; i++){
		string line;
		getline(ifile,line);
		int score;
		stringstream s;
		s << line;
		s >> score;
		gradingScore.push_back(score);
	}

	intComp comp1;
	//RUNTIME: O(n log n) - merge sort
	mergeSort(gradingScore, comp1);
	
	//RUNTIME: O(n log n)- binary search of sorted list through n
	for(unsigned int i=0; i< students.size(); i++){
		try{
			gradingCurve(gradingScore, students[i]);
			
		}
		catch(logic_error &e){
			cout << e.what() << endl;
			return -1;
		}
	}

	ofstream ofile(argv[2]);
	
	//RUNTIME: O(n) - print out each student (size of n)
	for(unsigned int i=0; i< students.size(); i++){
		ofile << students[i]->name << " " << students[i]->curveScore << endl;
	}
	
	//RUNTIME: O(n) - delete dynamically allocated memory (size of n)
	for(unsigned int i=0; i < students.size(); i++){
		delete students[i];
	}
	
	return 0;
}

//RUNTIME: O(log n) - binary search of sorted list
int binSearch (vector<int> mylist, int k, int start, int end)
{
	int position;
	if(end-start == 1){
		return 0;
	}
	while(start < end){
		int mid = (start + end)/2;
		if(k == mylist[mid])
			return mid;
		else if(k < mylist[mid]){
			end = mid;
			position = mid;
		}
		else{
			start = mid+1;
			position = mid+1;
		}
	}
	return position;
}

//RUNTIME: O(log n) - binary search of sorted list
void gradingCurve (vector<int> &grades, studentScore* &student)
{
	int num;
	if(grades.empty()){
		throw logic_error("IMPOSSIBLE RESULT: Please reenter valid grades for grading");
	}
	num = binSearch(grades, student->rawScore, 0, grades.size());
	if(grades[num]<student->rawScore){
		throw logic_error("IMPOSSIBLE RESULT: Please reenter valid grades for grading");
	}
	student->curveScore = grades[num];
	grades.erase(grades.begin()+num);
}