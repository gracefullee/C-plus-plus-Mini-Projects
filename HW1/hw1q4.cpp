#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

int main(int argc, char *argv[])
{
  
  ifstream ifile(argv[1]);
  if(ifile.fail()){
    cout << "Couldn't open file." << endl;
    return -1;
  }
  
  int numLines;
  ifile >> numLines;
  
  int *numWords = new int[numLines];
  for(int i=0; i<numLines; i++){
    numWords[i] = 0;
  }
  
  
  for(int i=0; i<numLines+1; i++){
    char words[80];
    ifile.getline(words,80);
    stringstream n;
    n << words;
    int count = 0;
    string word;
    while(n >> word){
      count++;
    }
    numWords[i]=count;
  }
  
  for(int i=0; i<numLines; i++){
    cout << numWords[numLines-i] << endl;
  }
  
  ifile.close();
  delete [] numWords;
  return 0;
  
}

