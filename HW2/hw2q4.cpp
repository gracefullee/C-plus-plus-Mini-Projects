#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>

using namespace std;

struct Item{
  int val;
  Item* next;
};

bool isEven(int n);
bool isSquare(int n);
bool isPrime(int n);
Item *filter(Item *head, bool(*f)(int) );

Item *newHead = NULL;

int main(int argc, char *argv[]){

	if(argc<3){
		cout << "Please enter a filename followed by A, B, or C" << endl;
		return -1;
	}

  ifstream ifile(argv[1]);
  if(ifile.fail()){
    cout << "Couldn't open file." << endl;
    return -1;
  }


  int num;
  Item *head = NULL;
  Item *tail = NULL;

  while(!ifile.eof()){
    ifile >> num;
    Item *newItem = new Item;
    if(tail != NULL){
      Item *currentItem = tail;
      currentItem->next = newItem;
    }
    if(head == NULL && tail == NULL){
      head = newItem;
    }
    newItem->val = num;
    newItem->next = NULL;
    tail = newItem;
  }


  string func = argv[2];
  
  if(func[0]!='A' && func[0]!='B' && func[0]!='C'){
    cout << "Please enter A, B, or C" << endl;
    return -1;
  }
  
  Item *I;

  if(func[0]=='A'){
    I = filter(head,isEven);
    if(newHead == NULL){
      cout << "No element in the list is even" << endl;
    }
    else{
      if(I->next==NULL){
    	cout << I->val << endl;
      }
      else{
    	  while(I!=NULL){
    		  cout << I->val << endl;
    		  I = I->next;
    	  }
      }
    }
  }

  if(func[0]=='B'){
    I = filter(head,isSquare);
    if(newHead==NULL){
      cout << "No element in the list is a Square" << endl;

    }
    else{
      if(I->next==NULL){
    	  cout << I->val << endl;
      }
      else{
    	  while(I!=NULL){
    		  cout << I->val << endl;
    		  I = I->next;
    	  }
      }
    }
  }

  if(func[0]=='C'){
    I = filter(head,isPrime);
    if(newHead==NULL){
      cout << "No element in the list is a prime number" << endl;
    }
    else{
      if(I->next==NULL){
    	  cout << I->val << endl;
      }
      else{
    	  while(I!=NULL){
    		  cout << I->val << endl;
    		  I = I->next;
    	  }
      }
    }
  }

  //delete all lists
  Item *current;
  while(I!=NULL){
    current = I;
    I = I->next;
    delete I;
  }
  while(head!=NULL){
    current = head;
    head = head->next;
    delete current;
  }
  head = NULL;
  tail = NULL;

  return 0;

}



bool isEven(int n){
  return ((n%2)==0);
}



bool isSquare(int n){
  if(n<0){
    return false;
  }
  double dnum = sqrt(n);
  int inum = dnum;
  if(dnum == inum){
    return true;
  }
  else{
    return false;
  }
}



bool isPrime(int n){
  if(n==0 || n==1){
    return false;
  }
  if(n<0){
    return false;
  }
  if(n==2){
    return true;
  }
  for(int i=3; i <= sqrt(n); i++){
    if(n%i==0){
      return false;
    }
  }
  return true;
}



Item *filter(Item *head, bool(*f)(int)){
  bool result = f(head->val);
  if(head->next==NULL){
    if(!result){
      return newHead;
    }
    else if(result){
      Item* newList = new Item;
      newList->val = head->val;
      newList->next = head->next;
      newHead = newList;
      return newHead;
    }
  }
  else{
    filter(head->next, f);
    if(!result){
      return newHead;
    }
    else if(result){
      Item *newList = new Item;
      if(newHead==NULL){
	 newList->val = head->val;
	 newHead = newList;
	 newList->next = NULL;
	 return newHead;
      }
      else{
	newList->val = head->val;
	newList->next = newHead;
	newHead = newList;
	return newHead;
      }
    }
  }
  return 0;
}
