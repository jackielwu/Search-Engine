#include "heap.h"

Heap::Heap(int maxSize)
{
	n=0;
	nmax=maxSize;
	array=(ArrayDictionaryNode **) malloc(nmax * sizeof(ArrayDictionaryNode *));
}
Heap::~Heap()
{
	for(int i=0;i<n;i++){
		delete array[i]->key;
		delete array[i];
	}
	delete [] array;
}
void Heap::insert(ArrayDictionaryNode *e)
{
	assert(n<nmax);
	array[n]->key=strdup(e->key);
	n++;
	int child = n-1;p arr
	int parent=iparent(child);
	while(child>0) {
		if(strcmp(array[child]->key,array[parent]->key)>0) {
			break;
		}
		ArrayDictionaryNode *tmp=array[child];
		array[child]=array[parent];
		array[parent]=tmp;
		child=parent;
		parent=iparent(child);
	}
}
ArrayDictionaryNode * Heap::removeMin()
{
	assert(n>0);
	ArrayDictionaryNode *minKey=array[0];
	n--;
	if(n==0) {
		return minKey;
	}
	array[0]=array[n];
	int parent=0;
	int left=left_child(parent);
	int right=right_child(parent);
	while(left<n) {
		int minChild=left;
		if(right<n && strcmp(array[right]->key,array[left]->key)<0) {
			minChild=left;
		}
		if(strcmp(array[parent]->key,array[minChild]->key)<0) {
			break;
		}
		ArrayDictionaryNode *tmp=array[minChild];
		array[minChild]=array[parent];
		array[parent]=tmp;
		parent=minChild;
		left=left_child(parent);
		right=right_child(parent);
	}
	return minKey;
}
