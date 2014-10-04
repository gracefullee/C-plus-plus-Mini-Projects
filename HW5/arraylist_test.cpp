#include <iostream>
#include "arraylist.h"
#include "LinkedList.h"

using namespace std;

int main(){
	
	ArrayList<int> num(5);
	cout << "capacity: " << num.capacity() << endl;
	for(int i=0; i<8; i++)
		num.insert(0,i);
	cout << "Added 8 items to the front" << endl;
	cout << '\t' << "size: " << num.size() << endl;
	cout << '\t' << "capacity: " << num.capacity() << endl;
	num.remove(3);
	cout << "Removed an item at position 3" << endl;
	cout << '\t' << "size: " << num.size() << endl;
	cout << '\t' << "capacity: " << num.capacity() << endl;
	num.set(0,-64);
	cout << "Item at 0: " << num.get(0) << endl;

	return 0;
}
