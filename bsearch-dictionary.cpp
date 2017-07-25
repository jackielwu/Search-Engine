
// Implementation of a dictionary using an array and binary search
// It will inherit from the ArrayDictionary

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "bsearch-dictionary.h"
#include "heap.cpp"

// Constructor
BinarySearchDictionary::BinarySearchDictionary()
{
	sorted = false;
}

bool
BinarySearchDictionary::addRecord( KeyType key, DataType record) {
	sorted = false;
	bool result = ArrayDictionary::addRecord(key,record);
	return result;
}

// Find a key in the dictionary and return corresponding record or NULL
DataType
BinarySearchDictionary::findRecord( KeyType key)
{
	if (!sorted) {
		sort();
		sorted = true;
	}
	int low =0;
	int high = currentNumber-1;
	while(high>=low) {
		int mid = (high+low)/2;
		int result = strcmp(key, array[mid]->key);
		if(result>0) {
			low = mid+1;
		}
		else if (result<0) {
			high=mid+1;
		}
		else {
			return array[mid]->data;
		}
	}
	// Use binary search

	// Add your implementation here

	return NULL;
}


// Sort array using heap sort
void
BinarySearchDictionary::sort()
{
	Heap heap(currentNumber);
	for(int i=0;i<currentNumber;i++) {
		heap.insert(array[i]);
	}
	for(int i=0;i<currentNumber;i++) {
		array[i]=heap.removeMin();
	}
	//printf("Before\n");
	//for (int i = 0; i < currentNumber; i++) {
	//	printf("%s\n", array[i].key);
	//}

        // Add your code here

	//printf("After\n");
	//for (int i = 0; i < currentNumber; i++) {
	//	printf("%s\n", array[i].key);
	//}
}




