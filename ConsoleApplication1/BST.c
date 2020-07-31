#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "node.h"
#include "BST.h"
#include "value.h"
#include <string.h>

BSTNode *insert(BSTNode *b, char *name, Value *value)
{
	if (b == NULL)	
	{
		BSTNode *temp;
		temp = (BSTNode *)malloc(sizeof(BSTNode));
		temp->name = name;
		temp->v = value;
		temp->left = temp->right = NULL;
		return temp;
	}

	if (strcmp(name, b->name) < 0)
		b->left = insert(b->left, name, value);
	if (strcmp(name, b->name) > 0)
		b->right = insert(b->right, name, value);
	if (strcmp(name, b->name) == 0) //if already in tree just update tree
	{
		b->v = value;
	}

	return b;

}

void Inorder(BSTNode *b)
{
	if (b == NULL)
		return;

	Inorder(b->left);
	printf(" %s ", b->name);
	displayValue(b->v);
	Inorder(b->right);

	//else
		//printf("SOMETHING IS WRONG");
}

Value *search(BSTNode *b, char *nme)
{
	Value *u = newValueS("Tree is empty");
	if (b == NULL)
	{
		//return NULL;
		return u;
		displayValue(u);
	}

	if (strcmp(b->name, nme) > 0)
	{
		printf("QQQQ");
		return (search(b->left, nme));	
	}
		
	if (strcmp(b->name, nme) < 0)
	{
		printf("OOOO");
		return (search(b->right, nme));
	}

	if (strcmp(b->name, nme) == 0)
	{
		printf("DDDD");
		printf("%s ", b->name);
		displayValue(b->v);
		return (b->v);
	}

	//else
	//{
		//printf("DDDD");
		//return (b->v);
		//displayValue(b->v);
	//}

}