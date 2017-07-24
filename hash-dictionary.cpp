
// Implementation of a dictionary using a hash table

#include <stdlib.h>
#include <string.h>
#include "hash-dictionary.h"

// Constructor
HashDictionary::HashDictionary()
{
  buckets = new HashNode*[MaxBuckets];
  for(int i=0;i<MaxBuckets;i++) {
  	buckets[i] = NULL;
  }
  nElements =0;
  maxElements=MaxBuckets;
}

int
HashDictionary::hash(KeyType key) {
  // Add your code here
  int sum = 0;
  int len = strlen(key);
  for (int i = 0; i < len; i++) {
		sum += i*key[i];
  }
  return sum%MaxBuckets;
}

// Add a record to the dictionary. Returns false if key already exists
bool
HashDictionary::addRecord( KeyType key, DataType record)
{
  if(nElements==maxElements){
  	int osize = MaxBuckets;
  	maxElements *= 2;
  	HashNode ** nTable=(HashNode **) malloc(MaxBuckets * sizeof(HashNode *));
  	
  	for(int i=0;i<osize;i++) {
  		HashNode *e = buckets[i];
  		while(e!=NULL) {
  			HashNode *n = e->next;
  			int h =hash(e->key);
  			e->next = nTable[h];
  			nTable[h] = e;
  			e=n;
  		}
  	}
  	free(buckets);
  	buckets = nTable;
  }
  int h = hash(key);
  HashNode *e = buckets[h];
  while (e != NULL)
  {
    if(strcmp(key,e->key)==0)
    {
      e->data = record;
      return true;
    }
    e = e->next;
  }
  e = new HashNode();
  e->key = strdup(key);
  e->data = record;
	e->next = buckets[h];
  buckets[h] = e;
  nElements++;
  return false;
}

// Find a key in the dictionary and return corresponding record or NULL
DataType
HashDictionary::findRecord( KeyType key)
{
	int h = hash(key);
  HashNode *e = buckets[h];
  while(e != NULL)
  {
    if(strcmp(key,e->key)==0)
    {
      return e->data;
    }
    e = e->next;
  }
  return NULL;
}

// Removes one element from the table
bool
HashDictionary::removeElement(KeyType key)
{
  int h = hash(key);
  HashNode *e = buckets[h];
  while(e != NULL)
  {
    if(strcmp(key,e->key)==0)
    {
      buckets[h] = e->next;
      delete e->key;
      delete e;
      nElements--;
      return true;
    }
    e = e->next;
  }
  return false;
}

// Returns all the elements in the table as an array of strings.
// *n is the size of the table and it is returned by reference
KeyType *
HashDictionary::keys(int * n)
{
	KeyType * a = (KeyType *) malloc(nElements * sizeof(KeyType));

	*n = nElements;
	int i = 0;
	for (int h = 0; h < MaxBuckets; h++) {
		HashNode * n = buckets[h];
		while (n!=NULL) {
			a[i] = n->key;
			i++;
			n = n->next;
		}
	}
	*n = nElements;
	return a;
}

