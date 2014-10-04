#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

int numC;


bool mapColor(int num, int c, vector< vector<int> > &adj, int *color);
bool checkColor(vector< vector<int> > &adj, int *color, int num, int c);

int main(int argc, char *argv[]){
  
  if(argc<2){
    cout << "Please enter a filename" << endl;
    return -1;
  }

  ifstream ifile(argv[1]);
  if(ifile.fail()){
    cout << "Couldn't open file" << endl;
    return -1;
  }
  
  int rows, cols;
  
  ifile >> numC >> rows >> cols;
  if(ifile.fail()){
    cout << "Couldn't locate integers" << endl;
  }

  //vector of vectors to store adjacencies
  vector< vector<int> > adj(numC,vector<int>(0));
  int *color = new int[numC];
  for(int i=0; i<numC; i++){
    color[i]=0;
  }

  //read all integers and convert char to int
  ifile.ignore(2,'\n');
  int **grid = new int*[rows];
  for(int i=0; i<rows; i++){
    grid[i] = new int[cols];
    char alph[80];
    ifile.getline(alph, 80);
    stringstream n;
    n << alph;
    char country;
    for(int j=0; n >> country ; j++){
      for(int k=0; k<numC; k++){
	if(country=='A'+k){
	  grid[i][j] = k;
	}
      }
    }
  }

  //Create a list of adjacencies for each country
  for(int i=0; i<rows; i++){
    for(int j=0; j<cols; j++){
      //vertical adjacencies
      if(i<(rows-1) && grid[i][j]!=grid[i+1][j]){
	adj[grid[i][j]].push_back(grid[i+1][j]);
      }
      if(i>0 && grid[i][j]!=grid[i-1][j]){
	adj[grid[i][j]].push_back(grid[i-1][j]);
      }
      //horizontal adjacencies
      if(j<(cols-1) && grid[i][j]!=grid[i][j+1]){
	adj[grid[i][j]].push_back(grid[i][j+1]);
      }
      if(j>0 && grid[i][j]!=grid[i][j-1]){
	adj[grid[i][j]].push_back(grid[i][j-1]);
      }
    }
  }

  //Erase duplicate adjacencies
  for(int i=0; i<numC; i++){
    sort(adj[i].begin(), adj[i].end());
    adj[i].erase( unique(adj[i].begin(), adj[i].end()), adj[i].end());
  }

  //Choose color
  mapColor(0,1,adj,color);
  for(int i=0; i<numC; i++){
    char letter = 'A'+i;
    cout << letter << " " << color[i] << endl;
  }

  //delete all dynamically allocated variables
  for(int i=0; i<rows; i++){
    delete [] grid[i];
  }
  delete [] grid;
  delete [] color;
  return 0;
}

 

bool mapColor(int num, int c, vector< vector<int> > &adj, int *color){
  if(num==numC){
    return true;
  }
  if(checkColor(adj,color,num,c)){
    color[num] = c;
    for(int j=1; j<=4; j++){
      if(mapColor(num+1, j, adj, color)){
    	  return true;
      }
    }
  }
  color[num]=0;
  return false;
}



bool checkColor(vector< vector<int> > &adj, int *color, int num, int c){
  for(unsigned int i=0; i<adj[num].size(); i++){
    int neighbor = adj[num].at(i);
    if(c==color[neighbor]){
      return false;
    }
  }
  return true;
}


  
