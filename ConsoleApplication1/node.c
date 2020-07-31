//node.c

#include "node.h"
#include "value.h"

Node *newEmptyNode(void)
{
	Node *p = malloc(sizeof(Node));     
	p->v = NULL;                     
	p->next = NULL;
	//p->left = 0;
	//p->right = 0;

	return p;
}

Node *newNode(Value *v, Node *n)
{
	Node *p = malloc(sizeof(Node));     
	p->v = v;
	p->next = n;
	return p;
}


