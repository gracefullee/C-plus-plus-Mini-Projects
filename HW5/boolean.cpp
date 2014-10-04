#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <cctype>
#include <cstdlib>
#include <iomanip>

#include "stack.h"
#include "arraylist.h"
#include "Map/Map.h"

using namespace std;

//global variable
Map<int,bool> boolean;


//additional functions
bool checkParen (string boolex);
bool convertBool (string val);

int main (int argc, char* argv[])
{
	
	if(argc<3){
		cout << "Usage: ./boolean filename1.txt filename2.txt" << endl;
		return -1;
	}
	
	//file of boolean expressions
	ifstream expressionFile(argv[1]);
	if(expressionFile.fail()){
		cout << "Couldn't open file." << endl;
		return -1;
	}
	
	ArrayList<string> exp;
	
	while(!expressionFile.fail()){
		string expression;
		getline(expressionFile,expression);
		if(!expression.empty()){
			exp.insert(exp.size(),expression);
		}
		expression.clear();
	}
	expressionFile.close();
	
	//boolean assignment for integers file
	ifstream booleanFile(argv[2]);
	if(booleanFile.fail()){
		cout << "Couldn't open file." << endl;
		return -1;
	}
	
	unsigned long long int num;
	char val;
	bool TF;
	
	while(!booleanFile.fail()){
		booleanFile >> num >> val;
		
		if(booleanFile.fail()){
			break;
		}
		if(val=='T')
			TF = true;
		else if(val=='F')
			TF = false;
		boolean.add(num,TF);
	}
	booleanFile.close();
	
	
	
	//Make a Stack for each expression and Parse!
	
	string expression, substring;
	Map<string,string> results;
	string result;
	for(int i=0; i<exp.size(); i++){
		stringstream ex;
		expression = exp.get(i);
		if(checkParen(expression)){
			Stack<string> exp2;
			for(unsigned int i=0; i<expression.size()-1; i++){
				string p1, operand, setOperand, p2;
				bool TF1, TF2;
				if(isblank(expression[i]))
					continue;
				if(expression[i]==')'){
					int operOccur = 0;
					//Parsing
					while(exp2.top()!="("){
						p1 = exp2.top();
						try{
							TF1 = convertBool(p1);
						}
						catch(invalid_argument & e){
							result = "Malformed";
							break;
						}
						exp2.pop();
						if(exp2.top()!="~"){
							if(operOccur==0){
								setOperand = exp2.top();
							}
							operand = exp2.top();
							if(setOperand!=operand){
								result = "Malformed";
								break;
							}
							operOccur++;
							exp2.pop();
						}
						else if(exp2.top()=="~"){
							TF1 = !TF1;
							exp2.pop();
							while(exp2.top()=="~"){
								TF1 = !TF1;
								exp2.pop();
							}
							operand = exp2.top();
							exp2.pop();
						}
						p2 = exp2.top();
						if(exp2.top()=="("){
							result = "Malformed";
							break;
						}
						try{
							TF2 = convertBool(p2);
						}
						catch(invalid_argument & e){
							result = "Malformed";
							break;
						}
						exp2.pop();
						if(exp2.top()=="~"){
							TF2 = !TF2;
							exp2.pop();
							while(exp2.top()=="~"){
								TF2 = !TF2;
								exp2.pop();
							}
						}
						//EVALUATE EXPRESSSIONS
						//check for mixing operators
						if(operand=="&")
							TF1 = (TF1 && TF2);
						else if(operand=="|")
							TF1 = (TF1 || TF2);
						if(exp2.top()!="("){
							if(TF1==true)
								exp2.push("T");
							if(TF1==false)
								exp2.push("F");
						}
					}
					operOccur=0;
					//remove opening parentheses and replace with result 
					exp2.pop();
					if(TF1==true)
						exp2.push("T");
					if(TF1==false)
						exp2.push("F");
				}
				else if(!isdigit(expression[i]) && !isblank(expression[i])){
					string sub1 = expression.substr(i,1);
					exp2.push(sub1);
				}
				else if(i>0 && isdigit(expression[i]) && !isdigit(expression[i-1])){ 
					int begIndx = i;
					++i;
					while(isdigit(expression[i])){
						++i;
					}
					int endIndx = i; //this index is not a digit
					i--;
					int len = endIndx - begIndx;
					string sub2 = expression.substr(begIndx,len);
					exp2.push(sub2);
				}
		}
		if(result!="Malformed"){
			result = exp2.top();
			exp2.pop();
			if(!exp2.isEmpty()){
				string top, oper;
				bool TF;
				exp2.push(result);
				while(!exp2.isEmpty()){
					top = exp2.top();
					try{
						TF = convertBool(top);
					}
					catch(invalid_argument & e){
						result = "Malformed";
						break;
					}
					exp2.pop();
					if(exp2.isEmpty()){
						exp2.push(top);
						break;
					}
					oper = exp2.top();
					if(oper=="~")
						TF = !TF;
					else{
						result = "Malformed";
						break;
					}
					exp2.pop();
					if(TF==true)
						exp2.push("T");
					else if(TF==false)
						exp2.push("F");
					result = exp2.top();
				}
				
			}
		}
	}
	else{
		result = "Malformed";
	}
	try{
		results.add(expression,result);
		result.clear();
	}
	catch(invalid_argument & e){
		
	}
	
}

	//print results
	cout << left << setw(15) << "Results" << setw(40) << "Expressions" << endl;
	cout << setfill('-') << setw(60) << "-" << endl;
	cout << setfill(' ');
	for(int i=0; i<exp.size(); i++){
		cout << left << setw(15) << results.get(exp.get(i)) << exp.get(i) << endl;
	}
	return 0;
}

bool checkParen (string boolex)
{
	//Check if parenthesized correctly
	Stack<string> paren;
	int parenOccur = 0;
	for(unsigned int i=0; i<boolex.size(); i++){
		if(boolex[i]=='('){
			paren.push("(");
			parenOccur++;
		}
		if(boolex[i]==')'){
			//if more closing parentheses than opening
			if(paren.isEmpty()){
				return false;
			}
			paren.pop();
		}
	}
	//if parentheses never occur
	if(parenOccur==0){
		return false;
	}
	//if more opening parentheses than closing
	if(!paren.isEmpty()){
		return false;
	}


	return true;
}


bool convertBool (string val)
{
	if(isdigit(val[0])){
		int num1 = atoi(val.c_str());
		try{
			return boolean.get(num1);
		}
		catch(invalid_argument & e){
			cout << "> Couldn't locate boolean assignment for " << num1 << "!" << endl;
			throw invalid_argument("Boolean Assignment");
		}
	}
	if(val=="T")
		return true;
	else if(val=="F")
		return false;
	else{
		return NULL;
	}
}
