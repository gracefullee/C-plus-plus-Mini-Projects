#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstdlib>

using namespace std;

int recursion(int, int, string, string, int);

int main(int argc, char *argv[])
{

  int len, count, index;
  string n, s;

  if(argc < 3){
    cout << "Please enter characters followed by the length of string" << endl;
    return 0;
  }
  
  index = 0;
  len = atoi(argv[2]);
  n = argv[1];
  count = n.size();
  for(int i=0; i<len; i++){
    s.push_back(n.at(0));
  }
  recursion(len, count, s, n, index);
  
  return 0;
  
}


int recursion(int len, int m, string s, string n, int index)
{
  //base case
  if(index==len){
    return 1;
  }
  //recursive case
  else{
    for(int i=0; i<m; i++){
      s.at(index)= n.at(i);
      if(index==(len-1)){
	cout << s << endl;
      }
      recursion(len, m, s, n, index+1);
    }
  }
}
