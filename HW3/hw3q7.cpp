#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include "hw3q5.h"
#include "hw3q3.h"

using namespace std;

int main(int argc, char *argv[])
{
	if(argc < 2){
		cout << "Please enter a filename." << endl;
		return -1;
	}
	
	ifstream ifile(argv[1]);
	if(ifile.fail()){
		cout << "Couldn't open file." << endl;
		return -1;
	}
	
	string n, name, email;
	Map<string,string> dictionary;
	
	while(!ifile.eof()){
		char entry[150];
		ifile.getline(entry, 150);
		stringstream e;
		e << entry;
		e >> email;
		while(e>>n){
			name.append(n);
			name.append(" ");
		}
		try{
			dictionary.add(email,name);
			name.clear();
		}

		catch(invalid_argument & e){
			cout << e.what() << endl;
		}
	}

	string address;
	while(address!="."){
		cout <<  "Please enter an email address to look up: ";
		cin >> address;
		if(address=="."){
			return 0;
		}

		if(dictionary.check(address)){
			try{
				string name = dictionary.get(address);
				cout << '\t' << "Name: " << name << endl;
			}
			catch(invalid_argument & e){
				cout << e.what() << endl;
			}
		}
		else{
			cout << '\t' << "This email address does not exist in the database." << endl;
		}
	}



	return 0;
		
}
