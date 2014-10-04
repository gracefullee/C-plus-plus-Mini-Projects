#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <set>
#include <map>
#include <deque>
#include <vector>
#include <utility>
#include <stdexcept>
#include <unordered_map>

using namespace std;

int main(int argc, char* argv[])
{
	if(argc<2){
		cout << "Usage: ./grading input.txt" << endl;
		return -1;
	}
	
	long int uniformScore = 0;
	unordered_map<int,string> Members;
	set<int> Scores;
	vector<string> Order;
	deque<int> orderedScores;
	unordered_map<string,string> Pairs;

	ifstream ifile;
	ifile.open(argv[1]);
	int num;
	ifile >> num;
	if(ifile.fail()){
		cout << "> Please check input file." << endl;
		return -1;
	}
	if(num%2==1){
		cout << "> Please enter an even number of students for pairing." << endl;
		return -1;
	}
	ifile.ignore(80,'\n');
	

	//Reading members and their skill to a map & set - O(n)
	for(int i=0; i<num; i++){
		string line;
		getline(ifile,line);
		string fname;
		long int score;
		stringstream ln;
		ln << line;
		ln >> fname >> score;
		Members.insert(pair<int,string> (score,fname));
		Pairs.insert(pair<string,string> (fname,"NONE"));
		Order.push_back(fname);
		Scores.insert(score);
	}
	
	//Reading ordered Scores from set and moving to deque - O(n)
	//Since it iterates through the set once - O(n) and push_back for deque - O(1)
	for(set<int>::iterator it=Scores.begin(); it!=Scores.end(); ++it){
		orderedScores.push_back(*it);
	}
	
	uniformScore = (orderedScores.back())+(orderedScores.front());
	
	//Pairing each end of ordered deque of Scores together - O(n)
	//While loop iterates n/2 times - O(n) and find for unordered_map runs O(1)
	//due to implementations of HASH TABLES
	//pop() for deque also runs at O(1)
	while(!orderedScores.empty()){
		if(uniformScore == (orderedScores.back())+(orderedScores.front())){
			Pairs[Members[orderedScores.front()]] = Members[orderedScores.back()];
			Pairs[Members[orderedScores.back()]] = Members[orderedScores.front()];
			orderedScores.pop_front();
			orderedScores.pop_back();
		}
		else{
			throw logic_error("IMPOSSIBLE RESULT: Please reenter valid skill levels for pairing");
		}
	}
	
	//Printing out results from Pairs - O(n)
	for(vector<string>::iterator it=Order.begin(); it!=Order.end(); ++it){
		cout << *it << " " << Pairs[*it] << endl;
	}
}

