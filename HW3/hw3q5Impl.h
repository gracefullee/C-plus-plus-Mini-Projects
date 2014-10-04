#ifndef HW3Q5IMPL_H
#define HW3Q5IMPL_H

#include <iostream>
#include <stdexcept>

using namespace std;

template <class keyType, class valueType>
Map<keyType, valueType>::Map()
{

}

template <class keyType, class valueType>
Map<keyType, valueType>::~Map()
{

}

template <class keyType, class valueType>
int Map<keyType, valueType>::size() const
{
	int size = internalStorage.size();
	return size;
}

template <class keyType, class valueType>
void Map<keyType, valueType>::add (const keyType & key, const valueType & value)
{
	if(!check(key)){
		Pair<keyType, valueType> newPair;
		newPair.key = key;
		newPair.value = value;
		try{
			internalStorage.insert(size(),newPair);
		}
		catch(out_of_range & e){
			cout << e.what() << endl;
		}
	}
	else{
		throw invalid_argument ("Key already exists in the database.");
	}

}

template <class keyType, class valueType>
void Map<keyType, valueType>::remove (const keyType & key)
{
	if(check(key)){
		int position = find(key);
		try{
			internalStorage.remove(position);
		}
		catch(out_of_range & e){
			cout << e.what() << endl;
		}
	}
	else{
		throw invalid_argument ("Key does not exist in the database.");
	}
}

template <class keyType, class valueType>
valueType& Map<keyType, valueType>::get (const keyType & key) const
{
	if(check(key)){
		int position = find(key);
		try{
			Pair<keyType, valueType> *current = &(internalStorage.get(position));
			return current->value;
		}
		catch(out_of_range & e){
			cout << e.what() << endl;
		}
	}
		throw invalid_argument ("Key does not exist in the database.");

}

template <class keyType, class valueType>
int Map<keyType, valueType>::find (const keyType & key) const
{
	for(int i=0; i<size(); i++){
		Pair<keyType, valueType> *current = &(internalStorage.get(i));
		if(current->key == key){
			return i;
		}
	}

	return -1;
}

template <class keyType, class valueType>
bool Map<keyType, valueType>::check(const keyType & key) const
{
	if(find(key)!=-1){
		return true;
	}
	return false;
}

#endif
