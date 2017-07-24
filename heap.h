#include <string.h>

class Heap {
	int n;
	int nmax;
	ArrayDictionaryNode **array;
public:
	Heap(int maxSize);
	void insert(int key);
	int removeMin();
	~Heap();
}


#define left_child(i) (2*i+1)
#define right_child(i) (2*i+2)
#define iparent(i) ((i-1)/2)
