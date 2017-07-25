#include <string.h>
#include <assert.h>
#include "array-dictionary.h"
#include <stdlib.h>
#include <stdio.h>

class Heap {
	int n;
	int nmax;
	ArrayDictionaryNode **array;
public:
	Heap(int maxSize);
	void insert(ArrayDictionaryNode *e);
	ArrayDictionaryNode* removeMin();
	~Heap();
};


#define left_child(i) (2*i+1)
#define right_child(i) (2*i+2)
#define iparent(i) ((i-1)/2)
