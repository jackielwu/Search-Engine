
// Implementation of a dictionary using an array and sequential search
// The array will be dynamically resized if necessary

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "array-dictionary.h"

// Constructor
ArrayDictionary::ArrayDictionary()
{
	maxNumber = 100;
  array = (ArrayDictionaryNode **) malloc(maxNumber * sizeof(ArrayDictionaryNode *));
  currentNumber =0;
}

// Add a record to the dictionary. Returns false if key already exists
bool
ArrayDictionary::addRecord( KeyType key, DataType record)
{
	if(key==NULL) {
		fprintf(stderr,"Null");
	}
	if(currentNumber==maxNumber) {
		int omax = maxNumber;
		maxNumber = 2 * maxNumber;
		ArrayDictionaryNode ** narray = (ArrayDictionaryNode **) malloc(maxNumber * sizeof(ArrayDictionaryNode *));
		for(int i=0;i<omax;i++) {
			narray[i]=array[i];
		}
		free(array);
		array = narray;
	}
	for(int i=0;i<currentNumber;i++) {
		//printf("array-dict: %s\n", array[i]->key);
		if(strcmp(key,array[i]->key)==0) {
			array[i]->data = record;
			return false;
		}
	}
	ArrayDictionaryNode *e = new ArrayDictionaryNode();
	e->key = strdup(key);
	e->data = record;
	array[currentNumber] = e;
	currentNumber++;
	return true;
}

// Find a key in the dictionary and return corresponding record or NULL
DataType
ArrayDictionary::findRecord( KeyType key)
{
	if(key==NULL) {
		fprintf(stderr,"ArrayDict findRecord null key");
		return NULL;
	}
  for(int i=0;i<currentNumber;i++) {
		if(strcmp(key,array[i]->key)==0) {
			return array[i]->data;
		}
	}
	return NULL;
}

// Removes one element from the table
bool
ArrayDictionary::removeElement(KeyType key)
{
	for(int i=0;i<currentNumber;i++) {
		if(strcmp(key,array[i]->key)==0) {
			delete array[i]->key;
			for(int j=i+1;j<currentNumber;j++) {
				array[i]=array[j];
				i++;
			}
			currentNumber--;
			return true;
		}
	}
	return false;
	
}

// Returns all the elements in the table as an array of strings.
// *n is the size of the table and it is returned by reference
KeyType *
ArrayDictionary::keys(int * n)
{
  KeyType * a = (KeyType *) malloc(currentNumber * sizeof(KeyType));

	*n = currentNumber;
	for (int i = 0; i < currentNumber; i++) {
		ArrayDictionaryNode * n = array[i];
		a[i] = n->key;
	}
	*n = currentNumber;
	return a;
}
