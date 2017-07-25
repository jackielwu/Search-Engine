
// Implementation of a dictionary using an AVL tree
// AVL Trees are balanced binary trees 

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

#include "avl-dictionary.h"

bool debug = false;

// Constructor
AVLDictionary::AVLDictionary()
{
	root = NULL;
	nElements = 0;
}

// Add a record to the dictionary. Returns false if key already exists
bool
AVLDictionary::addRecord( KeyType key, DataType record)
{
	if ( debug) {
		printf("------------------------------------\n");
		printf("addRecord(\"%s\",%ld)\n",  key, (long) record);
		printf("---------- Before -----------------\n");
		printNode("", root, 0);
	}
	
	// Add your implementation here
	AVLNode *current = root;
	AVLNode *previous = NULL;
	while(current!=NULL) {
		previous = current;
		if(strcmp(key,current->key)==0) {
			current->data = record;
			return false;
		}
		else if(strcmp(key,current->key)<0) {
			current = current->left;
		}
		else {
			current = current->right;
		}
	}
	AVLNode *n = new AVLNode();
	n->key=strdup(key);
	n->data=record;
	n->left = NULL;
	n->right=NULL;
	n->parent= NULL;
	n->height=1;
	if(previous == NULL) {
		root = n;
		return false;
	}
	if(strcmp(key,previous->key)<0) {
		previous->left = n;
	}
	else {
		previous->right=n;
	}
	n->parent=previous;
	AVLNode *m=n->parent;
	while(m!=NULL) {
		int maxheight=0;
		if(m->left!=NULL) {
			maxheight=m->left->height;
		}
		if(m->right!=NULL && m->right->height>maxheight) {
			maxheight=m->right->height;
		}
		m->height= maxheight+1;
		m=m->parent;
	}
	
	
	//Find node to insert into 
	//Node does not exist. Create it.
	//Height might not be valid anymore.
	//We need to restructure .

	if ( debug) {
		printf("---------- Before Restructure -----------------\n");
		printNode("", root, 0);
	}
	
	// Call restructure
	restructure(n);
	if (debug) {
		checkRecursive(root);
		
		printf("---------- After Restructure -----------------\n");
		printNode("", root, 0);
	}
	return true;
}

void
AVLDictionary::restructure(AVLNode * n) {
	//Balance the tree starting at n 
	AVLNode *z=n->parent;
	while(z!=NULL) {
		int hleft=0;
		if(z->left!=NULL) {
			hleft=z->left->height;
		}
		int hright=0;
		if(z->right!=NULL) {
			hright=z->right->height;
		}
		int hdiff=hright-hleft;
		if(hdiff<0) {
			hdiff=-hdiff;
		}
		if(hdiff<=1) {
			z=z->parent;
			continue;
		}
		AVLNode *y=NULL;
		int maxh=0;
		if(z->left!=NULL) {
			y=z->left;
			maxh=z->left->height;
		}
		if(z->right!=NULL && maxh<z->right->height) {
			y=z->right;
		}
		assert(y!=NULL);
		AVLNode *x=NULL;
		maxh=0;
		if(y->left!=NULL) {
			x=y->left;
			maxh=y->left->height;
		}
		if(y->right!=NULL && maxh<y->right->height) {
			x=y->right;
		}
		assert(x!=NULL);
		
		AVLNode *a,*b,*c,*t0,*t1,*t2,*t3;
		if(z->right ==y) {
			if(y->right==x) {
				a=z;
				b=y;
				c=x;
				t0=z->left;
				t1=y->left;
				t2=x->left;
				t3=x->right;
			}
			else {
				a=z;
				c=y;
				b=x;
				t0=z->left;
				t1=x->left;
				t2=x->right;
				t3=y->right;
			}
		}
		else {
			if(y->left==x) {
				a=x;
				b=y;
				c=z;
				t0=x->left;
				t1=x->right;
				t2=y->right;
				t3=z->right;
			}
			else {
				a=y;
				b=x;
				c=z;
				t0=y->left;
				t1=x->left;
				t2=x->right;
				t3=z->right;
			}
		}
		AVLNode *p=z->parent;
		if(p!=NULL) {
			if(p->left==z) {
				p->left=b;
			}
			else {
				p->right=b;
			}
		}
		else {
		 root=b;
		}
		b->parent=p;
		b->left=a;
		b->right=c;
		a->parent=b;
		a->left=t0;
		a->right=t1;
		c->parent=b;
		c->left=t2;
		c->right=t3;
		if(t0!=NULL) {
			t0->parent=a;
		}
		if(t1!=NULL) {
			t1->parent=a;
		}
		if(t2!=NULL) {
			t2->parent=c;
		}
		if(t3!=NULL) {
			t3->parent=c;
		}
		int maxheight=0;
		if(a->left!=NULL) {
			maxheight=a->left->height;
		}
		if(a->right!=NULL && maxheight<a->right->height) {
			maxheight=a->right->height;
		}
		a->height=maxheight+1;
		maxheight=0;
		if(c->left!=NULL) {
			maxheight=c->left->height;
		}
		if(c->right!=NULL && maxheight<c->right->height) {
			maxheight=c->right->height;
		}
		c->height=maxheight+1;
		maxheight=0;
		if(b->left!=NULL) {
			maxheight=b->left->height;
		}
		if(b->right!=NULL && maxheight<b->right->height) {
			maxheight=b->right->height;
		}
		b->height=maxheight+1;
		
		z=z->parent;
	}
	//Go upwards until root is found

        // See class notes

	// Add your implementation here
}

// Find a key in the dictionary and return corresponding record or NULL
DataType
AVLDictionary::findRecord( KeyType key)
{
        // Add your implementation here
	AVLNode *e;
	if(root!=NULL) {
		e=root;
		while(e!=NULL) {
			if(strcmp(key,e->key)<0) {
				e=e->left;
			}
			else if(strcmp(key,e->key)>0) {
				e=e->right;
			}
			else {
				return e->data;
			}
		}
	}
	return NULL;
}

// Removes one element from the dictionary
bool
AVLDictionary::removeElement(KeyType key)
{
	if (debug) {
		printf("------------------------------------\n");
		printf("removeElement(\"%s\")\n",  key);
		printf("---------- Before -----------------\n");
		printNode("", root, 0);
	}


	AVLNode *e;
	if(root!=NULL) {
		e=root;
		while(e!=NULL) {
			if(strcmp(key,e->key)<0) {
				e=e->left;
			}
			else if(strcmp(key,e->key)>0) {
				e=e->right;
			}
			else {
				AVLNode *z = e->parent;
				int maxh=0;
				AVLNode *y=NULL;
				if(z->left!=NULL) {
					y=z->left;
					maxh=z->left->height;
				}
				if(z->right!=NULL && maxh<z->right->height) {
					y=z->right;
				}
				assert(y!=NULL);
				
				return e->data;
			}
		}
	}
	
	if (debug) {
		printf("---------- After -----------------\n");
		printNode("", root, 0);

		checkRecursive(root);
	}
	
	return true;
}

// Returns all the elements in the table as an array of strings.
// *n is the size of the table and it is returned by reference
KeyType *
AVLDictionary::keys(int * n)
{
	KeyType * a = (KeyType *) malloc(nElements * sizeof(KeyType));
	*n = 0;
	addKeysRecursive(root, a, n);

	return a;
}

// Add keys recursively
void
AVLDictionary::addKeysRecursive(AVLNode * node, KeyType * a, int * n) {
	if (node==NULL) {
		return;
	}
	
	a[*n] = node->key;
	(*n)++;
	addKeysRecursive(node->left, a, n);
	addKeysRecursive(node->right, a, n);
}

